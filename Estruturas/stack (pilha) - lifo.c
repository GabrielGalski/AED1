#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int reg;
    char nome[50];
}Student;

typedef struct{
    Student *students;
    Student *top;
    Student *base;
    int limit;
} Stack;

void reset(Stack *stack){
    stack->students = NULL;
    stack->top = NULL;
    stack->base = NULL;
    stack->limit = 0;
}

bool empty(Stack *stack){
    return stack->limit == 0;
}

bool full(Stack *stack){
    Student *test = (Student *)malloc(sizeof(Student));
    if(test){
        free(test);
        return false;  l
    }
    return true;  
}

bool push(Stack *stack, Student *item){
    Student *newStudents = (Student *)malloc(sizeof(Student) * (stack->limit + 1));
    if(!newStudents){
        printf("Erro de alocacao de memoria\n");
        return false;
    }
    
    for(int i = 0; i < stack->limit; i++){
        newStudents[i] = stack->students[i];
    }
    
    printf("Digite o numero de registro: ");
    scanf("%d", &item->reg);
    printf("Digite o nome: ");
    scanf(" %49[^\n]", item->nome);
    
    newStudents[stack->limit] = *item;
    
    if(stack->students) free(stack->students);
    stack->students = newStudents;
    stack->limit++;
    stack->base = &stack->students[0];
    stack->top = &stack->students[stack->limit - 1];
    
    return true;
}

bool pop(Stack *stack, Student *item){
    if(empty(stack)){
        return false;
    }
    
    *item = *stack->top;
    
    if(stack->limit == 1){
        free(stack->students);
        reset(stack);
        return true;
    }
    
    Student *newStudents = (Student *)malloc(sizeof(Student) * (stack->limit - 1));
    if(!newStudents){
        printf("Erro de alocacao de memoria\n");
        return false;
    }
    
    for(int i = 0; i < stack->limit - 1; i++){
        newStudents[i] = stack->students[i];
    }
    
    free(stack->students);
    stack->students = newStudents;
    stack->limit--;
    stack->base = &stack->students[0];
    stack->top = &stack->students[stack->limit - 1];
    
    return true;
}

void listar(Stack *stack){
    if(empty(stack)){
        printf("\nPilha vazia!\n");
        return;
    }
    
    printf("\nListando alunos (do topo para base):\n");
    for(int i = stack->limit - 1; i >= 0; i--){
        printf("Registro: %d - Nome: %s\n", 
               stack->students[i].reg, 
               stack->students[i].nome);
    }
}

int main(){
    Stack pilha;
    reset(&pilha);
    Student aluno;
    int opcao;
    
    do {
        printf("\n1. adicionar aluno\n2. remover aluno\n3. listar\n0. sair\n escolha: ");
        scanf("%d", &opcao);
        
        switch(opcao){
            case 1:
                if(!push(&pilha, &aluno)){
                    printf("\nsaindo...\n");
                } else {
                    printf("\nAluno adicionado com sucesso!\n");
                }
                break;
                
            case 2:
                if(!pop(&pilha, &aluno)){
                    printf("\nErro: Pilha vazia!\n");
                } else {
                    printf("\nAluno removido:\n");
                    printf("Registro: %d - Nome: %s\n", 
                           aluno.reg, aluno.nome);
                }
                break;
                
            case 3:
                listar(&pilha);
                break;
                
            case 4:
                printf("\nEncerrando programa...\n");
                // Libera memória antes de sair
                if(pilha.students) free(pilha.students);
                break;
                
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 4);
    
    return 0;
}