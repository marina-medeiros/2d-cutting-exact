#ifndef DBPB_HPP
#define DBPB_HPP

#include <atomic>
#include <chrono>
#include <cstdint>
#include <mutex>
#include <vector>
#include "instancia_db.h"
#include "matriz.h"
#include "variaveis.h"

struct ResultadoDBPB {
    std::vector<int> solucao;
    int L = -1;
    int lb = 0;
    bool otimo = false;
    long long nos = 0;
    double tempo_s = 0.0;
    double tempo_melhor_s = 0.0;
};

struct ContextoThread {
    Matriz phi;
    std::vector<int> x;
    long long nos = 0;
};

class DBPB {
private:
    const InstanciaDB& inst;
    const Variaveis& vars;
    const Matriz& pi;

    std::vector<uint8_t> nao_dominadas;
    std::vector<int> x_inc;
    std::atomic<int> L_inc;
    std::atomic<bool> otimo;
    std::mutex mtx;
    int lb = 0;
    double limite_tempo_s = 0.0;
    std::chrono::steady_clock::time_point inicio;
    double tempo_melhor_s = 0.0;

    void ramificar(int nivel, int L_parcial, ContextoThread& ctx);
    bool verificar_adiante(const uint8_t* phi, int nivel) const;
    void atualizar_incumbente(const std::vector<int>& x, int L);
    bool tempo_esgotado() const;

public:
    DBPB(const InstanciaDB& inst, const Variaveis& vars, const Matriz& pi);

    void definir_limites(int lb, int ub);
    void definir_incumbente(const std::vector<int>& solucao, int L);
    ResultadoDBPB resolver(double limite_tempo_s);
};

#endif // DBPB_HPP
