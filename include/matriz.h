#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <cstdint>
#include <vector>

class Matriz {
private:
    int linhas = 0;
    int colunas = 0;
    std::vector<uint8_t> dados;

public:
    Matriz() = default;
    Matriz(int linhas, int colunas, uint8_t valor = 0);

    int get_linhas() const;
    int get_colunas() const;

    uint8_t get_valor(int i, int j) const;
    void set_valor(int i, int j, uint8_t valor);

    const uint8_t* linha(int i) const;
    uint8_t* linha(int i);
};

#endif // MATRIZ_HPP
