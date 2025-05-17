#include "quickSort.h"
#include <stdio.h>

static void swap(int *a, int *b, struct Estatistica *est) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    est->move += 3;
}

static int median(int a, int b, int c)
{
    if ((a <= b) && (b <= c))
        return b;
    if ((a <= c) && (c <= b))
        return c;
    if ((b <= a) && (a <= c))
        return a;
    if ((b <= c) && (c <= a))
        return c;
    if ((c <= a) && (a <= b))
        return a;
    return b;
}

static void partition3(int *V, int l, int r, int *i, int *j, struct Estatistica *est) {
    est->calls++;

    *i = l;
    *j = r;

    int pivot = median(V[l], V[r], V[(*i + *j) / 2]);

    do {
        while (V[*i] < pivot) {
            est->cmp++;
            (*i)++;
        }
        est->cmp++;

        while (V[*j] > pivot) {
            est->cmp++;
            (*j)--;
        }
        est->cmp++;

        if (*i <= *j) {
            swap(&V[*i], &V[*j], est);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

static void quickSort3Ins(int *V, int l, int r, int minTamParticao, struct Estatistica *est) {
    est->calls++;
    if (l >= r)
        return;

    int i = 0, j = 0;
    partition3(V, l, r, &i, &j, est);

    if (l < j) {
        if ((j - l) < minTamParticao) {
            insertionSort(V, l, j, est);
        } else {
            quickSort3Ins(V, l, j, minTamParticao, est);
        }
    }

    if (i < r) {
        if ((r - i) < minTamParticao) {
            insertionSort(V, i, r, est);
        } else {
            quickSort3Ins(V, i, r, minTamParticao, est);
        }
    }
}

void quickSort(int *V, int tam, int minTamParticao, struct Estatistica *est) {
    quickSort3Ins(V, 0, tam - 1, minTamParticao, est);
}

void printArray(int *V, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", V[i]);
    printf("\n");
}
