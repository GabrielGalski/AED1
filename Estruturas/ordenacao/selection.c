#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int vet[] = {5, 13, 60, -1, 32, 24, 48, 8};
    int size = sizeof(vet) / sizeof(vet[0]);

    printf("Array antes da ordenacao:\n");
    printArray(vet, size);

    selectionSort(vet, size);

    printf("Array depois da ordenacao:\n");
    printArray(vet, size);

    return 0;
}
