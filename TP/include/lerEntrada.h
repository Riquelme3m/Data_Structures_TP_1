#ifndef ENTRADA_H
#define ENTRADA_H

struct Entrada
{
    int seed;
    double limiarCusto;
    double a, b, c;
    int tam;
    int *vetor;
};

struct Entrada* lerEntrada(const char *filename);
void liberarEntrada(struct Entrada* entrada);

#endif
