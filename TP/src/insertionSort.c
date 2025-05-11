#include "insertionSort.h"

void insertionSort(int *V, int tam, struct Estatistica *est)
{
    est->calls++;

    int aux, j;
    for (int i = 1; i < tam; i++)
    {
        est->move++; 
        aux = V[i];
        j = i - 1;

        while ((est->cmp++, j >= 0) && (aux < V[j]))
        {
            est->move++; 
            V[j + 1] = V[j];
            j--;
        }
        est->move++;
        V[j + 1] = aux;
    }
    return;
}
