#include "determinarLimiarParticao.h"
#include <stdio.h>
#include <time.h>

int determinaLimiarParticao(int *V, int tam, int limiarCusto, struct Estatistica *est, struct Entrada *entrada)
{

    int minMPS = 2;
    int maxMPS = tam;
    int passoMPS = (maxMPS - minMPS) / 5;
    int limParticao;
    struct custos custos[9];
    int iter = 0;
    struct particaoDeMenorCustoEntreTodasTestadas pmenorCusto;
    pmenorCusto.custo = 10000000000;
    pmenorCusto.particao = 0;
    float diffCusto;
    diffCusto = limiarCusto + 1;
    int numMPS = 6;

    while ((diffCusto > limiarCusto) && (numMPS >= 5))
    {

        printf("iter %d\n", iter);

        numMPS = 0;

        for (int t = minMPS; t <= maxMPS; t += passoMPS)
        {
            int X[tam];
            for (int i = 0; i < tam; i++)
            {
                X[i] = V[i];
            }

            est->cmp = 0;
            est->move = 0;
            est->calls = 0;

            clock_t start = clock();
            ordernadorUniversal(X, tam, t, 0, est);
            clock_t end = clock();
            double elapsed = (double)(end - start) / CLOCKS_PER_SEC;

            custos[numMPS].custo = calculaCusto(entrada, est);
            custos[numMPS].particao = t;
            printf("mps %d cost %.9f cmp %d move %d calls %d\n", t, custos[numMPS].custo, est->cmp, est->move, est->calls);

            // Write results to results.txt
            FILE *fout = fopen("results.txt", "a");
            if (fout)
            {
                fprintf(fout, "mps,%d,calls,%d,cmp,%d,move,%d,time,%.9f\n", t, est->calls, est->cmp, est->move, elapsed);
                fclose(fout);
            }

            numMPS++;
        }

        double menorCusto = 100000000;
        int minIndex = 0;
        int minParticaoValue = custos[0].particao;

        for (int i = 0; i < numMPS; i++)
        {
            if (custos[i].custo < menorCusto)
            {
                menorCusto = custos[i].custo;
                minIndex = i;
                minParticaoValue = custos[i].particao;
            }
        }
        limParticao = minParticaoValue;
        if (menorCusto < pmenorCusto.custo)
        {
            pmenorCusto.custo = menorCusto;
            pmenorCusto.particao = minParticaoValue;
        }
        calculaNovaFaixa(minIndex, &minMPS, &maxMPS, &passoMPS, numMPS, custos);

        int indexMin = -1, indexMax = -1;
        for (int i = 0; i < numMPS; i++)
        {
            if (custos[i].particao == minMPS)
                indexMin = i;
            if (custos[i].particao == maxMPS)
                indexMax = i;
        }
        diffCusto = fabs(custos[indexMin].custo - custos[indexMax].custo);
        printf("nummps %d limParticao %d mpsdiff %.6f", numMPS, limParticao, diffCusto);
        printf("\n\n");
        iter++;
    }

    return pmenorCusto.particao;
};

void calculaNovaFaixa(int limParticao, int *minMPS, int *maxMPS, int *passoMPS, int numMPS, struct custos *custos)
{
    int newMin;
    int newMax;

    if (limParticao == 0)
    {
        newMin = 0;
        newMax = 2;
    }
    else if (limParticao == numMPS - 1)
    {
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    }
    else
    {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }
    *minMPS = custos[newMin].particao;
    *maxMPS = custos[newMax].particao;

    *passoMPS = (int)(*maxMPS - *minMPS) / 5;
    if (*passoMPS == 0)
        (*passoMPS)++;
}
