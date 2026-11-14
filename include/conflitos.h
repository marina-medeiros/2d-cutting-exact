#ifndef CONFLITOS_HPP
#define CONFLITOS_HPP

#include <vector>
#include "bitset_din.h"
#include "grid.h"
#include "instancia_db.h"
#include "variaveis.h"

struct Deslocamento {
    int dx = 0;
    int dy = 0;
};

std::vector<Deslocamento> nfp_discreto(const Grid& fixa, const Grid& movel);
std::vector<BitsetDin> construir_matriz_compatibilidade(const InstanciaDB& inst, const Variaveis& vars);
void quebrar_simetria(std::vector<BitsetDin>& pi, const Variaveis& vars, int num_tipos);

#endif // CONFLITOS_HPP
