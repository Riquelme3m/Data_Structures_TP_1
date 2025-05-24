#include "numeroDeQuebras.h"

int numeroDeQuebras(int *V, int tam){
    int counter=0;
    for(int i=1;i<tam;i++){
        if(V[i] < V[i-1]) counter++;
    }
    return counter;
}