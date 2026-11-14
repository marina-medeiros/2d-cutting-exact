#include "variaveis.h"

void Variaveis::gerar(const InstanciaDB& inst) {
}

int Variaveis::total() const {
    return static_cast<int>(vars.size());
}

const Variavel& Variaveis::operator[](int v) const {
    return vars[v];
}

int Variaveis::inicio(int tipo) const {
    return 0;
}

int Variaveis::fim(int tipo) const {
    return 0;
}

int Variaveis::indice(int tipo, int rot, int x, int y) const {
    return -1;
}

const std::vector<int>& Variaveis::comprimentos() const {
    return L;
}

std::vector<int> Variaveis::limites_acima_de(int lb) const {
    return {};
}
