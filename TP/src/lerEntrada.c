#include <stdio.h>
#include <stdlib.h>
#include "lerEntrada.h"

struct Entrada *lerEntrada(const char *filename)
{
    // printf("Trying to open file: %s\n", filename); // Debug print
    struct Entrada *entrada = malloc(sizeof(struct Entrada));
    if (!entrada)
        return NULL;

    FILE *f = fopen(filename, "r");
    if (!f)
    {
        free(entrada);
        return NULL;
    }

    fscanf(f, "%d", &entrada->seed);         // 1
    fscanf(f, "%lf", &entrada->limiarCusto); // 10.000000
    fscanf(f, "%lf", &entrada->a);           // 0.012156
    fscanf(f, "%lf", &entrada->b);           // -0.006378
    fscanf(f, "%lf", &entrada->c);           // 0.0172897
    fscanf(f, "%d", &entrada->tam);          // 1000

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