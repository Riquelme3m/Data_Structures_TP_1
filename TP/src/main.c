#include "determinarLimiarParticao.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Uso: %s <arquivo_entrada.txt>\n", argv[0]);
        return 1;
    }

    struct Entrada *entrada = lerEntrada(argv[1]);
    if (!entrada) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }
    

    struct Estatistica *est = malloc(sizeof(struct Estatistica));
    est->cmp = 0;
    est->move = 0;
    est->calls = 0;
    int numeroQuebras = numeroDeQuebras(entrada->vetor,entrada->tam);
    printf("size %d seed %d breaks %d",entrada->tam,entrada->seed,numeroQuebras);
    printf("\n\n");
    int resultado = determinaLimiarParticao(entrada->vetor, entrada->tam, entrada->limiarCusto, est, entrada);

    printf("%d",resultado);

    free(est);
    liberarEntrada(entrada);

    return 0;
}
