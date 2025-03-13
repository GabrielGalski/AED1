#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n, const char* message) {
    printf("%s: ", message);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    printArray(L, n1, "Subarray esquerdo");
    printArray(R, n2, "Subarray direito");
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    char msg[50];
    sprintf(msg, "Array apos fusao [%d, %d]", left, right);
    printArray(&arr[left], right - left + 1, msg);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        char msg[50];
        sprintf(msg, "Dividindo [%d, %d]", left, right);
        printArray(&arr[left], right - left + 1, msg);
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

int main() {
    int vet[] = {5, 13, 60, 33, 32, 24, 48, 8};
    int size = sizeof(vet) / sizeof(vet[0]);
    
    printf("Array antes da ordenacao:\n");
    printArray(vet, size, "Original");
    
    mergeSort(vet, 0, size - 1);
    
    printf("\nArray depois da ordenacao:\n");
    printArray(vet, size, "Ordenado");
    
    return 0;
}