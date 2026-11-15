#ifndef EMPACOTADOR_HPP
#define EMPACOTADOR_HPP

#include <vector>
#include "grid.h"

struct Componente {
    int id_molde;
    Grid grid;
    int area_retangulo;
};

bool colide_retangulo(const Grid& folha, const Grid& peca, int pos_x, int pos_y);
bool colide_poligono(const Grid& folha, const Grid& peca, int pos_x, int pos_y);
void fixar_peca(Grid& folha, const Grid& peca, int pos_x, int pos_y, int id_molde);
void remover_peca(Grid& folha, const Grid& peca, int pos_x, int pos_y);
int calcular_comprimento_ocupado(const Grid& folha);
int limite_inferior_trivial(const std::vector<Componente>& componentes, int largura_folha);
void branch_and_bound_simples(Grid& folha, const std::vector<Componente>& componentes, int nivel,
    int& melhor_comprimento, Grid& melhor_folha, int limite_inferior);

#endif // EMPACOTADOR_HPP