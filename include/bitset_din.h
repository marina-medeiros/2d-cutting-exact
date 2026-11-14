#ifndef BITSET_DIN_HPP
#define BITSET_DIN_HPP

#include <cstdint>
#include <vector>

class BitsetDin {
private:
    int n = 0;
    std::vector<uint64_t> palavras;

public:
    BitsetDin() = default;
    explicit BitsetDin(int tamanho, bool valor = false);

    int tamanho() const;
    bool test(int i) const;
    void set(int i);
    void reset(int i);
    void preencher(bool valor);

    void and_de(const BitsetDin& a, const BitsetDin& b);
    void and_com(const BitsetDin& outro);
    bool algum_no_intervalo(int ini, int fim) const;
    bool vazio() const;
};

#endif // BITSET_DIN_HPP
