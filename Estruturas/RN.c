#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    VERMELHO,
    PRETO
} Cor;

typedef long TipoChave;

typedef struct Registro
{
    TipoChave Chave;
} Registro;

typedef struct No
{
    Registro Reg;
    struct No *pEsq, *pDir, *pPai;
    Cor cor;
} No;

typedef No *Apontador;

typedef struct No *TipoDicionario;

No *grandparent(No *n)
{
    if (n && n->pPai)
        return n->pPai->pPai;
    return NULL;
}

No *tio(No *n)
{
    No *g = grandparent(n);
    if (!g)
        return NULL;
    return (n->pPai == g->pEsq) ? g->pDir : g->pEsq;
}

void rotacao_esquerda(No **raiz, No *n)
{
    No *r = n->pDir;
    n->pDir = r->pEsq;
    if (r->pEsq)
        r->pEsq->pPai = n;
    r->pPai = n->pPai;
    if (!n->pPai)
        *raiz = r;
    else if (n == n->pPai->pEsq)
        n->pPai->pEsq = r;
    else
        n->pPai->pDir = r;
    r->pEsq = n;
    n->pPai = r;
}

void rotacao_direita(No **raiz, No *n)
{
    No *l = n->pEsq;
    n->pEsq = l->pDir;
    if (l->pDir)
        l->pDir->pPai = n;
    l->pPai = n->pPai;
    if (!n->pPai)
        *raiz = l;
    else if (n == n->pPai->pEsq)
        n->pPai->pEsq = l;
    else
        n->pPai->pDir = l;
    l->pDir = n;
    n->pPai = l;
}

void insert_case1(No **raiz, No *n)
{
    if (!n->pPai)
        n->cor = PRETO;
    else
        insert_case2(raiz, n);
}

void insert_case2(No **raiz, No *n)
{
    if (n->pPai->cor == PRETO)
        return;
    insert_case3(raiz, n);
}

void insert_case3(No **raiz, No *n)
{
    No *t = tio(n);
    No *g;
    if (t && t->cor == VERMELHO)
    {
        n->pPai->cor = PRETO;
        t->cor = PRETO;
        g = grandparent(n);
        g->cor = VERMELHO;
        insert_case1(raiz, g);
    }
    else
    {
        insert_case4(raiz, n);
    }
}

void insert_case4(No **raiz, No *n)
{
    No *g = grandparent(n);
    if (n == n->pPai->pDir && n->pPai == g->pEsq)
    {
        rotacao_esquerda(raiz, n->pPai);
        n = n->pEsq;
    }
    else if (n == n->pPai->pEsq && n->pPai == g->pDir)
    {
        rotacao_direita(raiz, n->pPai);
        n = n->pDir;
    }
    insert_case5(raiz, n);
}

void insert_case5(No **raiz, No *n)
{
    No *g = grandparent(n);
    n->pPai->cor = PRETO;
    g->cor = VERMELHO;
    if (n == n->pPai->pEsq)
        rotacao_direita(raiz, g);
    else
        rotacao_esquerda(raiz, g);
}

void inserir(No **raiz, Registro *reg)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->Reg = *reg;
    novo->pEsq = novo->pDir = novo->pPai = NULL;
    novo->cor = VERMELHO;

    No *y = NULL;
    No *x = *raiz;

    while (x)
    {
        y = x;
        if (reg->Chave < x->Reg.Chave)
            x = x->pEsq;
        else
            x = x->pDir;
    }

    novo->pPai = y;
    if (!y)
        *raiz = novo;
    else if (reg->Chave < y->Reg.Chave)
        y->pEsq = novo;
    else
        y->pDir = novo;

    insert_case1(raiz, novo);
}

void in_ordem(No *raiz)
{
    if (raiz)
    {
        in_ordem(raiz->pEsq);
        printf("%ld(%s) ", raiz->Reg.Chave, raiz->cor == VERMELHO ? "R" : "P");
        in_ordem(raiz->pDir);
    }
}

void liberar(No *raiz)
{
    if (raiz)
    {
        liberar(raiz->pEsq);
        liberar(raiz->pDir);
        free(raiz);
    }
}

int main()
{
    No *raiz = NULL;
    Registro reg;
    int opcao, n, i;

    do
    {
        printf("\nEscolha uma opcao:\n1. Inserir valores\n2. Em ordem\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Quantos valores deseja inserir? ");
            scanf("%d", &n);
            for (i = 0; i < n; i++)
            {
                printf("Digite o valor %d: ", i + 1);
                scanf("%ld", &reg.Chave);
                inserir(&raiz, &reg);
            }
            break;

        case 2:
            printf("\nÁrvore em ordem: ");
            in_ordem(raiz);
            printf("\n");
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    liberar(raiz);
    return 0;
}
