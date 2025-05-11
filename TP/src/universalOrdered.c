#include"numeroDeQuebras.h"
#include"ordernadorUniversal.h"
#include<stdio.h>



void ordernadorUniversal(int* V,int tam,int minTamParticao,int limiarQuebras,struct Estatistica* est){
    int numeroQuebras = numeroDeQuebras(V,tam);

    if(numeroQuebras < limiarQuebras){
        insertionSort(V, tam, est);
    }
    else if(tam > minTamParticao){
        quickSort(V, tam, est);
    }
    else{
        insertionSort(V, tam, est);
    }
}
