#include "dbpb.h"

DBPB::DBPB(const InstanciaDB& inst, const Variaveis& vars, const Matriz& pi)
    : inst(inst), vars(vars), pi(pi), L_inc(0), otimo(false) {}

void DBPB::definir_limites(int lb, int ub) {
}

void DBPB::definir_incumbente(const std::vector<int>& solucao, int L) {
}

ResultadoDBPB DBPB::resolver(double limite_tempo_s) {
    return {};
}

void DBPB::ramificar(int nivel, int L_parcial, ContextoThread& ctx) {
}

bool DBPB::verificar_adiante(const uint8_t* phi, int nivel) const {
    return false;
}

void DBPB::atualizar_incumbente(const std::vector<int>& x, int L) {
}

bool DBPB::tempo_esgotado() const {
    return false;
}
