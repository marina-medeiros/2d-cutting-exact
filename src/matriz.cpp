#include "matriz.h"

Matriz::Matriz(int linhas, int colunas, uint8_t valor) {
}

int Matriz::get_linhas() const {
    return linhas;
}

int Matriz::get_colunas() const {
    return colunas;
}

uint8_t Matriz::get_valor(int i, int j) const {
    return 0;
}

void Matriz::set_valor(int i, int j, uint8_t valor) {
}

const uint8_t* Matriz::linha(int i) const {
    return nullptr;
}

uint8_t* Matriz::linha(int i) {
    return nullptr;
}
