#ifndef DETERMINAR_LIMIAR_PARTICAO_H
#define DETERMINAR_LIMIAR_PARTICAO_H

#include"ordernadorUniversal.h"
#include "calculaCusto.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>


struct custos{
    double custo;
    int particao;
};
 struct particaoDeMenorCustoEntreTodasTestadas{
    double custo;
    int particao;
};


int determinaLimiarParticao(int*V,int tam,int limiarCusto,struct Estatistica* est,struct Entrada* entrada);
void calculaNovaFaixa(int limParticao,int* minMPS,int* maxMPS,int* passoMPS,int numMPS,struct custos*custos);

#endif 