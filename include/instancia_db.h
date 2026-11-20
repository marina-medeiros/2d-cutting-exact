#ifndef INSTANCIA_DB_HPP
#define INSTANCIA_DB_HPP

#include <string>
#include <vector>
#include "grid.h"
#include "molde.h"
#include "io.h"

struct TipoPeca {
    int id_molde = 0;
    int demanda = 0;
    int area = 0;
    std::vector<double> rotacoes;
    std::vector<Grid> mascaras;
};

struct Alocacao {
    int tipo = 0;
    int rot = 0;
    int x = 0;
    int y = 0;
};

struct InstanciaDB {
    std::string nome;
    double escala = 0.0;
    int largura = 0;
    int lb = 0;
    int ub = 0;
    std::vector<TipoPeca> tipos;
    std::vector<int> tipo_do_nivel;

    int total_pecas() const;
};

bool carregar_instancia(const std::string& caminho, const std::string& nome,
                        const ParametrosInstancia& params, InstanciaDB& inst);
int calcular_lb_trivial(const InstanciaDB& inst);
int calcular_ub_heuristica(const InstanciaDB& inst, std::vector<Alocacao>& solucao);

#endif // INSTANCIA_DB_HPP
