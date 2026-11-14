#ifndef DBPB_LB_HPP
#define DBPB_LB_HPP

#include <vector>
#include "bitset_din.h"
#include "dbpb.h"
#include "instancia_db.h"
#include "variaveis.h"

ResultadoDBPB resolver_limite_inferior(const InstanciaDB& inst, const Variaveis& vars,
                                       const std::vector<BitsetDin>& pi, double limite_tempo_s);

#endif // DBPB_LB_HPP
