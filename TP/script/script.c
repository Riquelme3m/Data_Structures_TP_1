#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

int main() {
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    srand((unsigned int)time(NULL));
    shuffle(arr, SIZE);

    FILE *f = fopen("file.txt", "w");
    if (!f) {
        perror("file.txt");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        fprintf(f, "%d\n", arr[i]);
    }

    fclose(f);
    return 0;
}
