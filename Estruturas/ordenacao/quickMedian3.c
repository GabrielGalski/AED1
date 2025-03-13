#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int medianOfThree(int arr[], int low, int high) {
    int mid = (low + high) / 2;

    if (arr[low] > arr[mid]) swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high]) swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high]) swap(&arr[mid], &arr[high]);

    return mid;
}

int partition(int arr[], int low, int high) {
    int pivotIndex = medianOfThree(arr, low, high);
    int pivot = arr[pivotIndex];
    swap(&arr[pivotIndex], &arr[high]);

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void print(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int vet[] = {5, 13, 60, 33, 32, 24, 48, 8};
    int size = sizeof(vet) / sizeof(vet[0]);

    printf("Array antes da ordenacao:\n");
    print(vet, size);

    quickSort(vet, 0, size - 1);

    printf("Array depois da ordenacao:\n");
    print(vet, size);

    return 0;
}
