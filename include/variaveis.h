#ifndef VARIAVEIS_HPP
#define VARIAVEIS_HPP

#include <cstdint>
#include <unordered_map>
#include <vector>
#include "instancia_db.h"

struct Variavel {
    int tipo = 0;
    int rot = 0;
    int x = 0;
    int y = 0;
    int L = 0;
};

class Variaveis {
private:
    std::vector<Variavel> vars;
    std::vector<int> L;
    std::vector<int> ini_tipo;
    std::vector<int> fim_tipo;
    std::unordered_map<int64_t, int> mapa;

public:
    void gerar(const InstanciaDB& inst);

    int total() const;
    const Variavel& operator[](int v) const;
    int inicio(int tipo) const;
    int fim(int tipo) const;
    int indice(int tipo, int rot, int x, int y) const;
    const std::vector<int>& comprimentos() const;
    std::vector<int> limites_acima_de(int lb) const;
};

#endif // VARIAVEIS_HPP
