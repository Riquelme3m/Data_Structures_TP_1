#include "insertionSort.h"

void insertionSort(int *V, int l, int r, struct Estatistica *est)
{
    est->calls++;
    for (int i = l + 1; i <= r; i++) {
        int aux = V[i];
        est->move++;
        int j = i - 1;
        while (j >= l && V[j] > aux) {
            est->cmp++;
            V[j + 1] = V[j];
            est->move++;
            j--;
        }
        est->cmp++;
        // Always write back aux, even if not needed
        V[j + 1] = aux;
        est->move++;
    }
}
