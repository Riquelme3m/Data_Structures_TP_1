#ifndef DETERMINAR_LIMIAR_QUEBRAS_H
#define DETERMINAR_LIMIAR_QUEBRAS_H

#include "calculaCusto.h"
#include "ordernadorUniversal.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct custosQuebras {
    double custoQS;
    double custoINS;
    int quebras;
};

struct limiarDeMenorCustoEntreTodasTestadas {
    double custo;
    int limiar;
};

int shuffleVector(int *vet, int size, int numShuffle);
int determinaLimiarQuebras(int *V, int tam, int limiarCusto, struct Estatistica *est, struct Entrada *entrada, int resultado);
void calculaNovaFaixaQuebras(int limQuebras, int* minLQ, int* maxLQ, int* passoLQ, int numLQ, struct custosQuebras* custos);

#endif