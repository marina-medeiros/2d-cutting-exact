#include "empacotador.h"
#include <algorithm>

// primeiro estagio: verificar retangulo envolvente da peça. era usado na primeiro estagio da heuristica
// bool colide_retangulo(const Grid& folha, const Grid& peca, int pos_x, int pos_y) {
//     if (pos_x < 0 || pos_y < 0 ||
//         pos_x + peca.get_largura() > folha.get_largura() ||
//         pos_y + peca.get_comprimento() > folha.get_comprimento()) {
//         return true;
//     }

//     for (int i = 0; i < peca.get_comprimento(); ++i) {
//         for (int j = 0; j < peca.get_largura(); ++j) {
//             if (folha.get_valor(pos_x + j, pos_y + i)) return true;
//         }
//     }
//     return false;
// }

// verifica se colide com outro retangulo. ainda pode ser usado no exato 
bool colide_poligono(const Grid& folha, const Grid& peca, int pos_x, int pos_y) {
    if (pos_x < 0 || pos_y < 0 ||
        pos_x + peca.get_largura() > folha.get_largura() ||
        pos_y + peca.get_comprimento() > folha.get_comprimento()) {
        return true;
    }

    for (int i = 0; i < peca.get_comprimento(); ++i) {
        for (int j = 0; j < peca.get_largura(); ++j) {
            if (peca.get_valor(j, i) != 0 && folha.get_valor(pos_x + j, pos_y + i)) return true;
        }
    }
    return false;
}

// também pode manter 
void fixar_peca(Grid& folha, const Grid& peca, int pos_x, int pos_y, int id_molde) {
    for (int i = 0; i < peca.get_comprimento(); ++i) {
        for (int j = 0; j < peca.get_largura(); ++j) {
            if (peca.get_valor(j, i) != 0) {
                folha.set_valor(pos_x + j, pos_y + i, id_molde + 1);
            }
        }
    }
}

void remover_peca(Grid& folha, const Grid& peca, int pos_x, int pos_y){
    // fazer o oposto da funão fixar_peca, zerando o valor 
    for (int i = 0; i < peca.get_comprimento(); ++i) {
        for (int j = 0; j < peca.get_largura(); ++j) {
            if (peca.get_valor(j, i) != 0) {
                folha.set_valor(pos_x + j, pos_y + i, 0);
            }
        }
    }
}

int calcular_comprimento_ocupado(const Grid& folha){
    // essa função será usada para avaliar se a solução atual é 
    // melhor do que a melhor já encontrada
    // varre a folha até a primeira celula que encontrar ( o pico)
    for (int y = folha.get_comprimento() - 1; y >= 0; --y) {
        for (int x = 0; x < folha.get_largura(); ++x) {
            if (folha.get_valor(x, y) != 0) {
                return y + 1; // altura máxima alcançada
            }
        }
    }
    return 0;
}


int limite_inferior_trivial(const std::vector<Componente>& componentes, int largura_folha) {
    long long area = 0;
    int maior = 0;
    for (const auto& comp : componentes) {
        for (int y = 0; y < comp.grid.get_comprimento(); ++y) {
            for (int x = 0; x < comp.grid.get_largura(); ++x) {
                if (comp.grid.get_valor(x, y) != 0) area++;
            }
        }
        maior = std::max(maior, calcular_comprimento_ocupado(comp.grid));
    }
    int por_area = static_cast<int>((area + largura_folha - 1) / largura_folha);
    return std::max(por_area, maior);
}

void branch_and_bound_simples(Grid& folha, const std::vector<Componente>& componentes, int nivel,
    int& melhor_comprimento, Grid& melhor_folha, int limite_inferior) {

    if (melhor_comprimento <= limite_inferior) return;

    // caso base
    if (nivel == static_cast<int>(componentes.size())){
        int comprimento_atual = calcular_comprimento_ocupado(folha);
        // ver se é melhor do  que o melhor comprimento global
        if (comprimento_atual < melhor_comprimento){
            melhor_comprimento = comprimento_atual;
            melhor_folha = folha;
        }
        return;
    }

    const Componente& comp = componentes[nivel];
    int comprimento_peca = comp.grid.get_comprimento();
    int larg_peca = comp.grid.get_largura();

    // pecorrer as soluções possiveis 
    for (int pos_y = 0; pos_y <= folha.get_comprimento() - comprimento_peca; ++pos_y){
        // caso de poda
        if (pos_y + comprimento_peca >= melhor_comprimento){
            break;
        }

        // tentar as proximas opções
        for (int pos_x = 0; pos_x <= folha.get_largura()- larg_peca; ++pos_x){
            if (!colide_poligono(folha, comp.grid, pos_x, pos_y)){
                // branch
                fixar_peca(folha, comp.grid, pos_x, pos_y, comp.id_molde);

                // proxima peça 
                branch_and_bound_simples(folha, componentes, nivel + 1, melhor_comprimento, melhor_folha,
                                         limite_inferior);

                // backtrack
                remover_peca(folha, comp.grid, pos_x, pos_y);

                if (melhor_comprimento <= limite_inferior) return;
            }
        }
    }
}