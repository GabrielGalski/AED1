/*
=================================================================================================================================
Agenda_pBuffer.c

Agenda pBuffer 
=================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT sizeof(int)
#define CHAR 30
#define STRT malloc(sizeof(void *) + INT + CHAR + INT + CHAR)
#define OP (int *)(pBuffer)
#define MEM() malloc(sizeof(void *) + CHAR + INT + CHAR)

void *pBuffer;

void PushPerson();
void PopPerson();
void ListPerson();
void SerchPerson();
void Free();

/*
=================================================================================================================================
Main

Função main do programa
=================================================================================================================================
*/
int main( void ) {
    pBuffer = STRT;
    if ( !pBuffer ) {
        perror( "ERRO!\nfechando...." );
        return -1;
    }

    *(void **)((char *)pBuffer + sizeof(int)) = NULL; 

    while ( 1 ) {
        int *op = OP;

        printf( "\n========== Agenda ==========\n1- Adicionar contato\n2- Remover contato\n3- Buscar contatos\n4- Listar contatos\n5- Sair\n============================\nEscolha: " );
        scanf( "%d", op );
        getchar();

        switch ( *op ) {
            case 1:
                PushPerson();
                break;
            case 2:
                PopPerson();
                break;
            case 3:
                SerchPerson();
                break;
            case 4:
                ListPerson();
                break;
            case 5:
                printf( "\nSaindo...\n" );
                Free();
                return 0;
            default:
                printf( "\nopcao inválida.\n tente novamente.\n" );
                break;
        }
    }

    Free();
    return 0;
}

/*
=================================================================================================================================
PushPerson

Adiciona um novo contato à agenda
=================================================================================================================================
*/
void PushPerson() {
    void **head = (void **)((char *)pBuffer + sizeof(int));
    char *nomeBuff = (char *)((char *)pBuffer + sizeof(int) + sizeof(void *));
    int *idadeBuff = (int *)(nomeBuff + CHAR);
    char *emailBuff = (char *)(idadeBuff + 1);

    printf( "Nome: " );
    scanf( " %29[^\n]", nomeBuff );
    getchar();

    printf( "Idade: " );
    scanf( "%d", idadeBuff );
    getchar();

    printf( "Email: " );
    scanf( " %29[^\n]", emailBuff );
    getchar();

    void *node = MEM();
    if ( !node ) {
        perror( "ERRO!\nfechando...." );
        return;
    }
    *(void **)node = NULL;

    char *nome = (char *)((char *)node + sizeof(void *));
    int *idade = (int *)(nome + CHAR);
    char *email = (char *)(idade + 1);

    strcpy( nome, nomeBuff );
    *idade = *idadeBuff;
    strcpy( email, emailBuff );

    *(void **)node = *head;
    *head = node;
}

/*
=================================================================================================================================
PopPerson

Função para remover um contato pelo nome
=================================================================================================================================
*/
void PopPerson() {
    void **head = (void **)((char *)pBuffer + sizeof(int));
    char *nomeRemove = (char *)((char *)pBuffer + sizeof(int) + sizeof(void *));

    printf( "\nDigite o nome para remover: " );
    scanf( " %29[^\n]", nomeRemove );
    getchar();

    void *curr = *head;
    void *prev = NULL;

    while ( curr != NULL ) {
        char *nome = (char *)((char *)curr + sizeof(void *));
        if ( strcmp( nome, nomeRemove ) == 0 ) {
            if ( prev == NULL ) {
                *head = *(void **)curr;
            } else {
                *(void **)prev = *(void **)curr;
            }
            free( curr );
            printf( "\n%s foi removido da agenda.\n", nomeRemove );
            return;
        }
        prev = curr;
        curr = *(void **)curr;
    } printf( "\n %s não encontrado na agenda\n", nomeRemove );
}

/*
=================================================================================================================================
ListPerson

Lista todos os contatos da agenda.
=================================================================================================================================
*/
void ListPerson() {
    void *curr = *(void **)((char *)pBuffer + sizeof(int));

    if ( curr == NULL ) {
        printf( "\nnenhum nome na agenda\n" );
        return;
    }

    while ( curr != NULL ) {
        char *nome = (char *)((char *)curr + sizeof(void *));
        int *idade = (int *)(nome + CHAR);
        char *email = (char *)(idade + 1);

        printf( "\nContato: | Nome: %s | Idade: %d | Email: %s |\n", nome, *idade, email );
        curr = *(void **)curr;
    }
}

/*
=================================================================================================================================

SerchPerson

Busca um contato pelo nome.
=================================================================================================================================

*/
void SerchPerson() {
    void **head = (void **)((char *)pBuffer + sizeof(int));
    char *nomeBusca = (char *)((char *)pBuffer + sizeof(int) + sizeof(void *));

    printf( "\nDigite o nome para ser encontrado: " );
    scanf( " %29[^\n]", nomeBusca );
    getchar();

    void *curr = *head;

    while ( curr != NULL ) {
        char *nome = (char *)((char *)curr + sizeof(void *));
        if ( strcmp( nome, nomeBusca ) == 0 ) {
            int *idade = (int *)(nome + CHAR);
            char *email = (char *)(idade + 1);
            printf( "\nContato: | Nome: %s | Idade: %d | Email: %s |\n", nome, *idade, email );
            return;
        }
        curr = *(void **)curr;
    }

    printf( "\n%s não esta na agenda\n", nomeBusca );
}

/*
=================================================================================================================================
Free

Libera toda a memória alocada.
=================================================================================================================================

*/
void Free() {
    void *curr = *(void **)((char *)pBuffer + sizeof(int));
    while ( curr != NULL ) {
        void *node = curr;
        curr = *(void **)curr;
        free( node );
    }
    free( pBuffer );
}
