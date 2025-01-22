#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const int MAX = 10;

typedef struct
{
    int reg;
    char nome[50];
} Aluno;

typedef struct{
    Aluno alunos[10];
    int top;
    int base;
    int limite;
} Pilha;

void reset(Pilha *pilha)
{
    pilha->top = 0;
    pilha->base = 0;
    pilha->limite = MAX;
}

bool empty(Pilha *pilha)
{
    return pilha->top == 0;
}

bool full(Pilha *pilha)
{
    return pilha->top == MAX;
}

bool push(Pilha *pilha, Aluno *item)
{
    if (!full(pilha))
    {
        pilha->alunos[pilha->top] = *item;
        pilha->top++;
        return true;
    }
    else
    {
        return false;
    }
}

void pop(Pilha *pilha, Aluno *aluno)
{
    if (empty(pilha))
    {
        printf("\nPilha vazia, nao e possivel remover elementos.\n");
        return;
    }
    pilha->top--;
    *aluno = pilha->alunos[pilha->top];
}

void listar(Pilha *pilha)
{
    if (empty(pilha))
    {
        printf("\nLista vazia\n");
        return;
    }
    printf("\nalunos:\n");
    for (int i = 0; i < pilha->top; i++)
    {
        printf("registro: %d, nome: %s\n", pilha->alunos[i].reg, pilha->alunos[i].nome);
    }
}

int main()
{
    Pilha pilha;
    reset(&pilha);

    int op;
    Aluno aluno;

    do
    {

        printf("\n1. adicionar aluno\n2. remover aluno\n3. listar\n4. sair\n escolha: ");

        scanf("%d", &op);

        switch (op)
        {
        case 1:
            if (full(&pilha))
            {
                printf("\npilha cheia\n");
            }
            else
            {
                printf("\nDigite o registro do aluno: ");
                scanf("%d", &aluno.reg);
                printf("Digite o nome do aluno: ");
                scanf(" %49s", aluno.nome);
                if (push(&pilha, &aluno))
                {
                    printf("\naluno inserido\n");
                }
            }
            break;
        case 2:
            if (empty(&pilha))
            {
                printf("\nA pilha esta vazia. Nao ha alunos para remover.\n");
            }
            else
            {
                pop(&pilha, &aluno);
                printf("\naluno removido: Registro: %d, Nome: %s\n", aluno.reg, aluno.nome);
            }
            break;
        case 3:
            listar(&pilha);
            break;
        case 4:
            printf("\nsaindo...\n");
            break;
        default:
            printf("\nsaindo...\n");
        }
    } while (op != 4);

    return 0;
}
