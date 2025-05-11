#include <stdio.h>
#include <stdlib.h>
#include "lerEntrada.h"

struct Entrada *lerEntrada()
{
    struct Entrada *entrada = malloc(sizeof(struct Entrada));
    if (!entrada)
        return NULL;

    FILE *f = fopen("entrada.txt", "r");
    if (!f) {
        free(entrada);
        return NULL;
    }

    fscanf(f, "%d", &entrada->limiarCusto);
    fscanf(f, "%lf", &entrada->a);
    fscanf(f, "%lf", &entrada->b);
    fscanf(f, "%lf", &entrada->c);
    fscanf(f, "%d", &entrada->tam);

    entrada->vetor = malloc(entrada->tam * sizeof(int));
    if (!entrada->vetor)
    {
        fclose(f);
        free(entrada);
        return NULL;
    }

    for (int i = 0; i < entrada->tam; i++)
    {
        fscanf(f, "%d", &entrada->vetor[i]);
    }

    fclose(f);
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