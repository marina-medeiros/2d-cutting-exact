#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <filesystem>


#include "grid.h"
#include "molde.h"
#include "empacotador.h"
#include "conversor.h"
#include "io.h"
// #include "conflitos.h"
// #include "conversor.h"
// #include "dbpb.h"
// #include "dbpb_lb.h"
// #include "instancia_db.h"
// #include "variaveis.h"

struct Resultado {
    std::string instancia;
    double escala = 0.0;
    double largura_folha_real = 0.0;
    size_t total_pecas = 0;
    int comprimento_grid = 0;
    double comprimento_real = 0.0;
    double eficiencia = 0.0;
    double tempo_ms = 0.0;
    int lb = 0;
    bool parou_no_lb = false;
};

bool executar_instancia(const std::string& caminho, const std::string& nome,
                        const ParametrosInstancia& params, const std::string& dir_saida,
                        Resultado& resultado) {
    const auto inicio = std::chrono::steady_clock::now();

    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o ficheiro: " << caminho << std::endl;
        return false;
    }

    const double ESCALA = params.escala;
    const double LARGURA_FOLHA_REAL = params.largura_folha_real;

    std::vector<Componente> lista_pecas;
    int soma_comprimentos_grid = 0;
    int area_total_ocupada_pelas_pecas = 0;

    Molde molde_atual;
    while (ler_molde(arquivo, molde_atual)) {
        Grid g = rasterizar_molde(molde_atual, ESCALA);

        int pixeis_peca = 0;
        for (int y = 0; y < g.get_comprimento(); ++y) {
            for (int x = 0; x < g.get_largura(); ++x) {
                if (g.get_valor(x, y) != 0) pixeis_peca++;
            }
        }

        for (int q = 0; q < molde_atual.quant; ++q) {
            Componente p{molde_atual.id, g, g.get_largura() * g.get_comprimento()};
            lista_pecas.push_back(p);
            soma_comprimentos_grid += g.get_comprimento();
            area_total_ocupada_pelas_pecas += pixeis_peca;
        }
    }
    arquivo.close();

    // 1. Ordenação decrescente pela área do retângulo envolvente 
    std::sort(lista_pecas.begin(), lista_pecas.end(), [](const Componente& a, const Componente& b) {
        return a.area_retangulo > b.area_retangulo;
    });

    // 2. Cria a folha de tecido vazia
    int largura_folha_grid = std::ceil(LARGURA_FOLHA_REAL * ESCALA);
    Grid folha(largura_folha_grid, soma_comprimentos_grid + 10);

    // 3. obter limite superior inicial 
    int limite_superior_trivial = 0;
    for (const auto& peca : lista_pecas) {
        limite_superior_trivial += peca.grid.get_comprimento();
    }
    std::cout << "(Trivial: " << limite_superior_trivial << ") ";

    const int lb = limite_inferior_trivial(lista_pecas, largura_folha_grid);
    std::cout << "(LB: " << lb << ") ";

    // 4. Branch-and-Bound Simples
    // Usamos o limite trivial como pior caso inicial
    int melhor_comprimento_global = limite_superior_trivial + 1;
    Grid melhor_folha = folha; // Vai guardar a solução ótima geométrica

    // Inicia a recursão exata
    branch_and_bound_simples(folha, lista_pecas, 0, melhor_comprimento_global, melhor_folha, lb);

    const auto fim = std::chrono::steady_clock::now();

    // 5. Resultados
    resultado.instancia = nome;
    resultado.escala = ESCALA;
    resultado.largura_folha_real = LARGURA_FOLHA_REAL;
    resultado.total_pecas = lista_pecas.size();
    
    // Atualiza com o valor final encontrado pelo método Exato
    resultado.comprimento_grid = melhor_comprimento_global;
    resultado.comprimento_real = melhor_comprimento_global / ESCALA;
    resultado.eficiencia = static_cast<double>(area_total_ocupada_pelas_pecas) /
                           (static_cast<double>(largura_folha_grid) * melhor_comprimento_global) * 100.0;
    resultado.tempo_ms = std::chrono::duration<double, std::milli>(fim - inicio).count();
    resultado.lb = lb;
    resultado.parou_no_lb = (melhor_comprimento_global == lb);

    // 6. Exportar layout exato
    const std::string nome_ppm = dir_saida + "/layout_exato_" + nome + ".ppm";
    if (!exportar_ppm(melhor_folha, melhor_comprimento_global, nome_ppm)) return false;
    converter_ppm_para_png(nome_ppm, dir_saida);
    return true;
}

std::string tabela_markdown(const std::vector<Resultado>& resultados) {
    std::ostringstream md;
    md << std::fixed;
    md << "| Instancia | Escala | Largura da folha | Total de pecas alocadas | Comprimento na grelha"
          " | LB | Parada | Comprimento real (C_L) | Eficiencia do layout | Tempo de execucao |\n";
    md << "|---|---:|---:|---:|---:|---:|---|---:|---:|---:|\n";
    for (const auto& r : resultados) {
        md << "| " << r.instancia
           << " | " << std::defaultfloat << std::setprecision(6) << r.escala
           << " | " << r.largura_folha_real << std::fixed
           << " | " << r.total_pecas
           << " | " << r.comprimento_grid << " celulas"
           << " | " << r.lb
           << " | " << (r.parou_no_lb ? "LB atingido" : "busca completa")
           << " | " << std::setprecision(2) << r.comprimento_real
           << " | " << std::setprecision(2) << r.eficiencia << "%"
           << " | " << std::setprecision(3) << r.tempo_ms << " ms |\n";
    }
    return md.str();
}

int main(int argc, char* argv[]) {
    const std::string caminho_config = (argc > 1) ? argv[1] : "./config/config.txt";

    Config config;
    if (!ler_config(caminho_config, config)) return 1;

    std::vector<std::filesystem::path> instancias;
    std::error_code ec;
    for (const auto& entrada : std::filesystem::directory_iterator(config.dataset, ec)) {
        if (entrada.is_regular_file() && entrada.path().extension() == ".txt") {
            instancias.push_back(entrada.path());
        }
    }
    if (ec) {
        std::cerr << "Erro ao listar " << config.dataset << ": " << ec.message() << std::endl;
        return 1;
    }
    std::sort(instancias.begin(), instancias.end());

    const std::string dir_saida = "outputs";
    std::vector<Resultado> resultados;
    bool houve_erro = false;

    for (const auto& caminho : instancias) {
        const std::string nome = caminho.stem().string();
        auto it = config.instancias.find(nome);
        if (it == config.instancias.end()) {
            std::cerr << "Instancia '" << nome << "' sem parametros em " << caminho_config
                      << " (adicione '" << nome << " = <escala> <largura_folha_real>'); ignorada" << std::endl;
            houve_erro = true;
            continue;
        }

        std::cout << "Executando " << nome << "... ";
        Resultado r;
        if (executar_instancia(caminho.string(), nome, it->second, dir_saida, r)) {
            std::cout << "Concluido em " << std::fixed << std::setprecision(2) << (r.tempo_ms / 1000.0) << "s." << std::endl;
            resultados.push_back(r);
        } else {
            std::cout << "Falha na execucao." << std::endl;
            houve_erro = true;
        }
    }

    const std::string tabela = tabela_markdown(resultados);
    std::cout << "\n=== RESULTADO DO EMPACOTAMENTO EXATO ===\n\n" << tabela << std::endl;

    const std::string caminho_md = dir_saida + "/resultados.md";
    std::filesystem::create_directories(dir_saida, ec);
    std::ofstream md(caminho_md);
    if (md.is_open()) {
        md << "# Resultados do empacotamento exato\n\n" << tabela;
        std::cout << "Tabela salva em " << caminho_md << std::endl;
    } else {
        std::cerr << "Erro ao criar " << caminho_md << std::endl;
        houve_erro = true;
    }

    return houve_erro ? 1 : 0;
}