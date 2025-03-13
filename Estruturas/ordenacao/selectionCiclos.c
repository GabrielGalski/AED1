#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        
        printf("Iteracao %d: ", i + 1);
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int vet[] = {5, 13, 60, 33, 32, 24, 48, 8};
    int size = sizeof(vet) / sizeof(vet[0]);

    printf("Array antes da ordenacao:\n");
    printArray(vet, size);

    selectionSort(vet, size);

    printf("Array depois da ordenacao:\n");
    printArray(vet, size);

    return 0;
}
