#include "quickSort.h"



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
    int i, j;
    if (l >= r) return;
    partition3(V, l, r, &i, &j, est);

    if (j - l <= 50) {
        est->call++;
        insertionSort(V + l, j - l + 1, est);
    } else if (l < j) {
        est->call++;
        quickSort3Ins(V, l, j, est);
    }

    if (r - i <= 50) {
        est->call++;
        insertionSort(V + i, r - i + 1, est);
    } else if (i < r) {
        est->call++;
        quickSort3Ins(V, i, r, est);
    }
}


void quickSort(int *V, int tam, struct Estatistica *est) {
    quickSort3Ins(V, 0, tam - 1, est);
}


#include <stdio.h>

void printArray(int *V, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", V[i]);
    printf("\n");
}

int main() {
    int V[] = {5, 2, 9, 1, 5, 6, 7, 3, 8, 4, 0, -1, 10, 15, 12, 11, 14, 13};
    int n = sizeof(V) / sizeof(V[0]);
    struct Estatistica est = {0, 0, 0};

    printf("Original array:\n");
    printArray(V, n);

    quickSort(V, n, &est);

    printf("Sorted array:\n");
    printArray(V, n);

    printf("Statistics:\n");
    printf("Comparisons: %d\n", est.cmp);
    printf("Moves: %d\n", est.move);
    printf("Calls: %d\n", est.call);

    return 0;
}
