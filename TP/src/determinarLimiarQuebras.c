#include "determinarLimiarQuebras.h"

int shuffleVector(int *vet, int size, int numShuffle)
{
    int p1 = 0, p2 = 0, temp;

    for (int t = 0; t < numShuffle; t++)
    {
        /* Gera dois índices distintos no intervalo [0..size-1] */

        while (p1 == p2)
        {
            p1 = (int)(drand48() * size);
            p2 = (int)(drand48() * size);
        }

        /*Realiza a troca para introduzir uma quebra*/

        temp = vet[p1];
        vet[p1] = vet[p2];
        vet[p2] = temp;
        p1 = p2 = 0;
    }

    return 0;
}



// Ordena o vetor de forma crescente (zero quebras)
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

int determinaLimiarQuebras(int *V, int tam, int limiarCusto, struct Estatistica *est, struct Entrada *entrada)
{
}




void calculaNovaFaixaQuebras(int limQuebras, int *minLQ, int *maxLQ, int *passoLQ, int numLQ, struct custosQuebras *custos)
{
    
}