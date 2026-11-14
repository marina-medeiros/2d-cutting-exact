#include "instancia_db.h"
#include "empacotador.h"

int InstanciaDB::total_pecas() const {
    return 0;
}

bool carregar_instancia(const std::string& caminho, const std::string& nome,
                        const ParametrosInstancia& params, InstanciaDB& inst) {
    return false;
}

int calcular_lb_trivial(const InstanciaDB& inst) {
    return 0;
}

int calcular_ub_heuristica(const InstanciaDB& inst, std::vector<Alocacao>& solucao) {
    return 0;
}
