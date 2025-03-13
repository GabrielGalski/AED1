#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct structType {
    struct structType *pPrevious;
    struct structType *pNext;
    int idade; 
    char nome[50];
} structType;

typedef struct {
    structType *pFirst;
    structType *pLast;
    unsigned int count;
} heap;

void empty(heap *h) {
    h->pFirst = NULL;
    h->pLast = NULL;
    h->count = 0;
}

heap *reset(heap *h) {
    structType *current = h->pFirst;
    while (current != NULL) {
        structType *temp = current;
        current = current->pNext;
        free(temp);
    }
    empty(h);
    return h;
}

void push(heap *h) {
    structType *newNode = (structType *)malloc(sizeof(structType));
    if (newNode == NULL) {
        printf("Erro ao alocar memória para novo nó.\n");
        return;
    }

    printf("Digite a idade: ");
    scanf("%d", &newNode->idade);
    printf("Digite o nome: ");
    getchar(); 
    fgets(newNode->nome, sizeof(newNode->nome), stdin);
    newNode->nome[strcspn(newNode->nome, "\n")] = '\0'; 
    newNode->pNext = NULL;
    newNode->pPrevious = NULL;


    if (h->pFirst == NULL) {
        h->pFirst = newNode;
        h->pLast = newNode;
    } else {
        structType *current = h->pFirst;
        structType *prev = NULL;

        while (current != NULL && current->idade < newNode->idade) {
            prev = current;
            current = current->pNext;
        }

        if (prev == NULL) { 
            newNode->pNext = h->pFirst;
            h->pFirst->pPrevious = newNode;
            h->pFirst = newNode;
        } else if (current == NULL) {
            prev->pNext = newNode;
            newNode->pPrevious = prev;
            h->pLast = newNode;
        } else { 
            prev->pNext = newNode;
            newNode->pPrevious = prev;
            newNode->pNext = current;
            current->pPrevious = newNode;
        }
    }

    h->count++;
    printf("Elemento inserido: [Idade: %d, Nome: %s]\n", newNode->idade, newNode->nome);
}

int pop(heap *h) {
    if (h->pFirst == NULL) {
        printf("Heap vazia. Nenhum elemento para remover.\n");
        return -1;
    }

    structType *temp = h->pFirst;
    int idade = temp->idade;

    h->pFirst = h->pFirst->pNext;
    if (h->pFirst != NULL) {
        h->pFirst->pPrevious = NULL;
    } else {
        h->pLast = NULL;
    }

    free(temp);
    h->count--;
    printf("Elemento removido: Idade %d\n", idade);
    return idade;
}

void listHeap(heap *h) {
    if (h->pFirst == NULL) {
        printf("Heap vazia.\n");
        return;
    }

    structType *current = h->pFirst;
    printf("Elementos na heap (ordenados por idade):\n");
    while (current != NULL) {
        printf("[Idade: %d, Nome: %s]\n", current->idade, current->nome);
        current = current->pNext;
    }
}

int main() {
    heap h;
    empty(&h);
    int opcao;

    do {
        printf("1. push\n2. pop\n3. listar\n4. quantidade na fila\n5. resetar\n0. sair\nescolha: ");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                push(&h);
                break;
            }
            case 2: {
                pop(&h);
                break;
            }
            case 3: {
                listHeap(&h);
                break;
            }
            case 4: {
                printf("Número de itens na heap: %u\n", h.count);
                break;
            }
            case 5: {
                reset(&h);
                printf("Heap resetada.\n");
                break;
            }
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    reset(&h);
    return 0;
}
