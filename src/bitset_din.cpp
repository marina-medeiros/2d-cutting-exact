#include "bitset_din.h"

BitsetDin::BitsetDin(int tamanho, bool valor) {
}

int BitsetDin::tamanho() const {
    return n;
}

bool BitsetDin::test(int i) const {
    return false;
}

void BitsetDin::set(int i) {
}

void BitsetDin::reset(int i) {
}

void BitsetDin::preencher(bool valor) {
}

void BitsetDin::and_de(const BitsetDin& a, const BitsetDin& b) {
}

void BitsetDin::and_com(const BitsetDin& outro) {
}

bool BitsetDin::algum_no_intervalo(int ini, int fim) const {
    return false;
}

bool BitsetDin::vazio() const {
    return true;
}
