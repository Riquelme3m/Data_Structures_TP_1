#include <stdio.h>
#include <stdlib.h>
#include "readInput.h"

struct Entrada *lerEntrada()
{

    struct Entrada *entrada = malloc(sizeof(struct Entrada));
    if (!entrada)
        return NULL;

    scanf("%d", &entrada->limiarCusto);
    scanf("%lf", &entrada->a);
    scanf("%lf", &entrada->b);
    scanf("%lf",&entrada->c);
    scanf("%d", &entrada->tam);

    entrada->vetor = malloc(entrada->tam * sizeof(int));
    if (!entrada->vetor)
    {
        free(entrada);
        return NULL;
    }

    for (int i = 0; i < entrada->tam; i++)
    {
        scanf("%d", &entrada->vetor[i]);
    }

    return entrada;
};

void liberarEntrada(struct Entrada *entrada)
{
    if (entrada)
    {
        free(entrada->vetor);
        free(entrada);
    }
}