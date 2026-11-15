#ifndef DBPB_LB_HPP
#define DBPB_LB_HPP

#include "dbpb.h"
#include "instancia_db.h"
#include "matriz.h"
#include "variaveis.h"

ResultadoDBPB resolver_limite_inferior(const InstanciaDB& inst, const Variaveis& vars,
                                       const Matriz& pi, double limite_tempo_s);

#endif // DBPB_LB_HPP
