#include <string>
#include <vector>

#include "conflitos.h"
#include "conversor.h"
#include "dbpb.h"
#include "dbpb_lb.h"
#include "empacotador.h"
#include "instancia_db.h"
#include "io.h"
#include "variaveis.h"

static bool exportar_solucao(const InstanciaDB& inst, const Variaveis& vars,
                             const ResultadoDBPB& res, const std::string& dir_saida) {
    return false;
}

static std::string tabela_markdown(const std::vector<InstanciaDB>& instancias,
                                   const std::vector<ResultadoDBPB>& resultados) {
    return {};
}

int main(int argc, char* argv[]) {
    return 0;
}
