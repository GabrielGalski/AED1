#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int reg;
    char nome[50];
} info;

typedef struct node
{
    info data;
    struct node *next;
} node;

typedef struct
{
    node *pFirst;
    int count;
} sentinel;

sentinel *createList()
{
    sentinel *list = (sentinel *)malloc(sizeof(sentinel));
    list->pFirst = NULL;
    list->count = 0;
    return list;
}

void push(sentinel *list)
{
    node *newNode = (node *)malloc(sizeof(node));
    info temp;

    printf("digite o registro: ");
    scanf("%d", &temp.reg);
    printf("digite o nome: ");
    scanf(" %49s", temp.nome);
    newNode->data = temp;
    newNode->next = list->pFirst;
    list->pFirst = newNode;
    list->count++;

    printf("\nusuario adicionado\n");
}

void resetList(sentinel *list)
{
    node *curr = list->pFirst;
    while (curr != NULL)
    {
        node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    list->pFirst = NULL;
    list->count = 0;
    printf("\nlista resetada\n");
}

void listar(sentinel *list)
{
    if (list->pFirst == NULL)
    {
        printf("lista vazia...\n");
        return;
    }

    printf("\nsuarios:\n");
    node *curr = list->pFirst;
    while (curr != NULL)
    {
        printf("Nome: %s (Registro: %d)\n", curr->data.nome, curr->data.reg);
        curr = curr->next;
    }
}

void pop(sentinel *list)
{
    node *temp = list->pFirst;
    list->pFirst = list->pFirst->next;
    printf("usuario removido: %s\n", temp->data.nome);
    free(temp);
    list->count--;
}

void showCount(sentinel *list)
{
    printf("usuarios na lista: %d\n", list->count);
}

void freeList(sentinel *list)
{
    resetList(list);
    free(list);
}

int main()
{
    sentinel *list = createList();
    int op;

    do
    {
        printf("1. adicionar usuario\n2. remover usuario\n3. numeros de usuarios\n4. resetar queue\n5. listar\n0. sair\nescolha: ");
        scanf("%d", &op);

        switch (op)
        {
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
            resetList(list);
            break;
        case 5:
            listar(list);
            break;
        case 0:
            printf("saindo...\n");
            break;
        default:
            printf("saindo...\n");
        }
    } while (op != 0);

    freeList(list);
    return 0;
}
