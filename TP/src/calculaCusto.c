#include "calculaCusto.h"

double calculaCusto(struct Entrada* entrada,struct Estatistica* est){
    return (entrada->a*est->cmp + entrada->b*est->move + entrada->c*est->calls);
}