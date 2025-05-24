#include "determinarLimiarQuebras.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int shuffleVector(int *vet, int size, int numShuffle)
{
    int p1 = 0, p2 = 0, temp;
    for (int t = 0; t < numShuffle; t++)
    {
        while (p1 == p2)
        {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }
        temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;
        p1 = p2 = 0;
    }
    return 0;
}

static void sortAscending(int *vet, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (vet[i] > vet[j]) {
                int tmp = vet[i];
                vet[i] = vet[j];
                vet[j] = tmp;
            }
        }
    }
}

int determinaLimiarQuebras(int *V, int tam, int limiarCusto, struct Estatistica *est, struct Entrada *entrada,int limiarParticao)
{
    int minLQ = 1; 
    int maxLQ = tam / 2;
    int passoLQ = (maxLQ - minLQ) / 5;
    if (passoLQ == 0) passoLQ = 1;
    int limQuebras;
    int iter = 0;
    struct limiarDeMenorCustoEntreTodasTestadas lmenorCusto;
    lmenorCusto.custo = 10000000000;
    lmenorCusto.limiar = 0;
    float diffCusto;
    diffCusto = limiarCusto + 1;
    int numLQ = 6;

    while ((diffCusto > limiarCusto) && (numLQ >= 5))
    {

        printf("iter %d\n", iter);

        numLQ = 0;
        for (int t = minLQ; t <= maxLQ; t += passoLQ) {
            numLQ++;
        }
        if (numLQ < 1) numLQ = 1;

        struct custosQuebras *custos = malloc(numLQ * sizeof(struct custosQuebras));
        if (!custos) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        int idx = 0;
        for (int t = minLQ; t <= maxLQ; t += passoLQ)
        {
            int X[tam];
            for (int i = 0; i < tam; i++){
                X[i] = V[i];
            }
            sortAscending(X, tam);
            srand48(entrada->seed);
            shuffleVector(X, tam, t);

            est->cmp = 0; est->move = 0; est->calls = 0;
            clock_t start_qs = clock();
            ordernadorUniversal(X, tam, limiarParticao, 0, est);
            clock_t end_qs = clock();
            double elapsed_qs = (double)(end_qs - start_qs) / CLOCKS_PER_SEC;

            custos[idx].custoQS = calculaCusto(entrada, est);
            printf("qs lq %d cost %.9f cmp %d move %d calls %d\n", t, custos[idx].custoQS, est->cmp, est->move, est->calls);

            FILE *fout = fopen("results.txt", "a");
            if (fout) {
                fprintf(fout, "qs_lq,%d,calls,%d,cmp,%d,move,%d,time,%.9f\n", t, est->calls, est->cmp, est->move, elapsed_qs);
                fclose(fout);
            }

            for (int i = 0; i < tam; i++)
                X[i] = V[i];
            sortAscending(X, tam);
            srand48(entrada->seed);
            shuffleVector(X, tam, t);

            est->cmp = 0; est->move = 0; est->calls = 0;
            clock_t start_in = clock();
            ordernadorUniversal(X, tam, tam, tam+1, est);
            clock_t end_in = clock();
            double elapsed_in = (double)(end_in - start_in) / CLOCKS_PER_SEC;

            custos[idx].custoINS = calculaCusto(entrada, est);
            printf("in lq %d cost %.9f cmp %d move %d calls %d\n", t, custos[idx].custoINS, est->cmp, est->move, est->calls);

            fout = fopen("results.txt", "a");
            if (fout) {
                fprintf(fout, "in_lq,%d,calls,%d,cmp,%d,move,%d,time,%.9f\n", t, est->calls, est->cmp, est->move, elapsed_in);
                fclose(fout);
            }

            custos[idx].quebras = t;
            idx++;
        }

        int menorCusto = custos[0].custoINS;
        limQuebras = 0;
        for(int i=1;i<numLQ;i++){
            if(custos[i].custoINS < menorCusto){
                menorCusto = custos[i].custoINS;
                limQuebras = i;
            }
        }
        double minDiff = fabs(custos[0].custoQS - custos[0].custoINS);
        limQuebras = 0;
        for (int i = 1; i < numLQ; i++) {
            double diff = fabs(custos[i].custoQS - custos[i].custoINS);
            if (diff < minDiff) {
                minDiff = diff;
                limQuebras = i;
            }
        }
        if(custos[limQuebras].custoINS < lmenorCusto.custo){
            lmenorCusto.custo = custos[limQuebras].custoINS;
            lmenorCusto.limiar = custos[limQuebras].quebras;
        }
        if(custos[limQuebras].custoQS < lmenorCusto.custo){
            lmenorCusto.custo = custos[limQuebras].custoQS;
            lmenorCusto.limiar = custos[limQuebras].quebras;
        }
        calculaNovaFaixaQuebras(limQuebras,&minLQ,&maxLQ,&passoLQ,numLQ,custos);

        int indexMin = -1, indexMax = -1;
        for(int i=0;i<numLQ;i++){
            if(custos[i].quebras == minLQ)
                indexMin = i;
            if(custos[i].quebras == maxLQ)
                indexMax = i;
        }
        diffCusto = fabs(custos[indexMin].custoINS - custos[indexMax].custoINS);
        printf("numlq %d limQuebras %d lqdiff %.6f", numLQ, custos[limQuebras].quebras, diffCusto);
        printf("\n\n");
        iter++;

        free(custos);
    }
    return lmenorCusto.limiar;
}

void calculaNovaFaixaQuebras(int limQuebras, int *minLQ, int *maxLQ, int *passoLQ, int numLQ, struct custosQuebras *custos)
{
    int newMin;
    int newMax;

    if (limQuebras == 0)
    {
        newMin = 0;
        newMax = 2;
    }
    else if (limQuebras == numLQ - 1)
    {
        newMin = numLQ - 3;
        newMax = numLQ - 1;
    }
    else
    {
        newMin = limQuebras - 1;
        newMax = limQuebras + 1;
    }
    *minLQ = custos[newMin].quebras;
    *maxLQ = custos[newMax].quebras;
    *passoLQ = (int)(*maxLQ - *minLQ) / 5;
    
    if (*passoLQ == 0)
        (*passoLQ)++;
}