#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int reg;
    char nome[50];
} info;

typedef struct node {
    info data;
    struct node *next;
} node;

typedef struct {
    node *pFirst;
    int count;
} sentinel;

sentinel* createList() {
    sentinel* list = (sentinel *)malloc(sizeof(sentinel));
    list->pFirst = NULL;
    list->count = 0;
    return list;
}

void push(sentinel* list) {
    node* newNode = (node*)malloc(sizeof(node));
    info newInfo;
    
    printf("Digite o registro: ");
    scanf("%d", &newInfo.reg);
    printf("Digite o nome: ");
    scanf(" %s", newInfo.nome);
    
    newNode->data = newInfo;
    newNode->next = list->pFirst;
    list->pFirst = newNode;
    list->count++;
    
    printf("Usuario adicionado com sucesso!\n");
}

void reset(sentinel* list) {
    node* current = list->pFirst;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    list->pFirst = NULL;
    list->count = 0;
    printf("Lista resetada com sucesso!\n");
}

void listar(sentinel* list) {
    if (list->pFirst == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    
    printf("\nListagem de usuarios:\n");
    node* current = list->pFirst;
    int i = 1;
    while (current != NULL) {
        printf("%d. Nome: %s (Registro: %d)\n", 
               i++, current->data.nome, current->data.reg);
        current = current->next;
    }
}

void pop(sentinel* list) {
    if (list->pFirst == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    
    node* temp = list->pFirst;
    list->pFirst = list->pFirst->next;
    printf("Usuario removido: %s (Registro: %d)\n", temp->data.nome, temp->data.reg);
    free(temp);
    list->count--;
}

void showCount(sentinel* list) {
    printf("Numero de usuarios na lista: %d\n", list->count);
}

void freeList(sentinel* list) {
    reset(list);
    free(list);
}

int main() {
    sentinel* list = createList();
    int option;
    
    do {
        printf("\n=== MENU ===\n");
        printf("1. Adicionar usuario (Push)\n");
        printf("2. Remover usuario (Pop)\n");
        printf("3. Mostrar numero de usuarios\n");
        printf("4. Resetar lista\n");
        printf("5. Listar usuarios\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);
        if(option < 1 || option > 5) break;
        switch(option) {
            case 1:
                push(list);
                break;
            case 2:
                pop(list);
                break;
            case 3:
                showCount(list);
                break;
            case 4:
                reset(list);
                break;
            case 5:
                listar(list);
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (option != 0);
    
    freeList(list);
    return 0;
}