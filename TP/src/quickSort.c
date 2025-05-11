#include "quickSort.h"
#include <stdio.h>



static void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


static int medianOf3(int *V, int l, int r, struct Estatistica *est) {
    int m = l + (r - l) / 2;
    
    if (V[l] > V[m]) { swap(&V[l], &V[m]); est->cmp++; est->move+=3; }
    else est->cmp++;
    if (V[m] > V[r]) { swap(&V[m], &V[r]); est->cmp++; est->move+=3; }
    else est->cmp++;
    if (V[l] > V[m]) { swap(&V[l], &V[m]); est->cmp++; est->move+=3; }
    else est->cmp++;
    
    swap(&V[l], &V[m]); est->move+=3;
    return V[l];
}


static void partition3(int *V, int l, int r, int *i, int *j, struct Estatistica *est) {
    int pivot = medianOf3(V, l, r, est);
    *i = l; *j = r;
    int left = l + 1, right = r;
    while (left <= right) {
        while (left <= r && V[left] < pivot) { left++; est->cmp++; }
        if (left <= r) est->cmp++;
        while (right >= l && V[right] > pivot) { right--; est->cmp++; }
        if (right >= l) est->cmp++;
        if (left <= right) {
            swap(&V[left], &V[right]); est->move+=3;
            left++; right--;
        }
    }
    swap(&V[l], &V[right]); est->move+=3;
    *i = left;
    *j = right;
}


static void quickSort3Ins(int *V, int l, int r, struct Estatistica *est) {
    est->calls++; // Count every call, including the initial and all recursive calls
    int i, j;
    if (l >= r) return;
    partition3(V, l, r, &i, &j, est);

    if (j - l <= 50) {
        insertionSort(V + l, j - l + 1, est);
    } else if (l < j) {
        quickSort3Ins(V, l, j, est);
    }

    if (r - i <= 50) {
        insertionSort(V + i, r - i + 1, est);
    } else if (i < r) {
        quickSort3Ins(V, i, r, est);
    }
}


void quickSort(int *V, int tam, struct Estatistica *est) {
    est->calls=10; 
    quickSort3Ins(V, 0, tam - 1, est);
}




void printArray(int *V, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", V[i]);
    printf("\n");
}
