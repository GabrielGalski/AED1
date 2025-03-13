#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSortWithSteps(int arr[], int low, int high, int depth) {
    if (low < high) {
        int pi = partition(arr, low, high);

        printf("Ciclo %d:\n", depth);
        printArray(arr, high + 1);

        quickSortWithSteps(arr, low, pi - 1, depth + 1);
        quickSortWithSteps(arr, pi + 1, high, depth + 1);
    }
}

int main() {
    int vet[] = {5, 13, 60, 33, 32, 24, 48, 8};
    int size = sizeof(vet) / sizeof(vet[0]);

    printf("Array antes da ordenacao:\n");
    printArray(vet, size);

    printf("\nExecutando Quick Sort com visualizacao dos ciclos:\n");
    quickSortWithSteps(vet, 0, size - 1, 1);

    printf("Array depois da ordenacao:\n");
    printArray(vet, size);

    return 0;
}