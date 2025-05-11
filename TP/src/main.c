#include "determinarLimiarParticao.h"

int main()
{

    struct Entrada *entrada = lerEntrada();
    
    
    struct Estatistica *est = malloc(sizeof(struct Estatistica));
    est->cmp = 0;
    est->move = 0;
    est->calls = 0;

    int resultado = determinaLimiarParticao(entrada->vetor, entrada->tam, entrada->limiarCusto, est, entrada);


    free(est);
    liberarEntrada(entrada);

    // for(int i=0;i<entrada->tam;i++){
    //     printf("%d\n",entrada->vetor[i]);
    // }

    return 0;
}
