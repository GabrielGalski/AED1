#include <stdio.h>
#include <stdlib.h>

typedef long TipoChave;

typedef struct Registro
{
    TipoChave Chave;
} Registro;

typedef struct No *Apontador;
typedef Apontador TipoDicionario;

typedef struct No
{
    Registro Reg;
    Apontador pEsq, pDir;
} No;

typedef No TNo;

int Altura(TNo *pRaiz)
{
    int iEsq, iDir;
    if (pRaiz == NULL)
        return 0;

    iEsq = Altura(pRaiz->pEsq);
    iDir = Altura(pRaiz->pDir);

    if (iEsq > iDir)
        return iEsq + 1;
    else
        return iDir + 1;
}

int FB(TNo *pRaiz)
{
    if (pRaiz == NULL)
        return 0;

    return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);
}

void RSE(TNo **ppRaiz)
{
    TNo *pAux;

    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD(TNo **ppRaiz)
{
    TNo *pAux;

    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int BalancaEsq(TNo **ppRaiz)
{
    int fbe = FB((*ppRaiz)->pEsq);
    if (fbe > 0)
    {
        RSD(ppRaiz);
        return 1;
    }
    else if (fbe < 0)
    {
        /* rotação dupla direita */
        RSE(&((*ppRaiz)->pEsq));
        RSD(ppRaiz);
        return 1;
    }
    return 0;
}

int BalancaDir(TNo **ppRaiz)
{
    int fbd = FB((*ppRaiz)->pDir);
    if (fbd < 0)
    {
        RSE(ppRaiz);
        return 1;
    }
    else if (fbd > 0)
    {
        /* rotação dupla esquerda */
        RSD(&((*ppRaiz)->pDir));
        RSE(ppRaiz);
        return 1;
    }
    return 0;
}

int Balanceamento(TNo **ppRaiz)
{
    int fb = FB(*ppRaiz);
    if (fb > 1)
        return BalancaEsq(ppRaiz);
    else if (fb < -1)
        return BalancaDir(ppRaiz);
    else
        return 0;
}

int Insere(TNo **ppRaiz, Registro *x)
{
    if (*ppRaiz == NULL)
    {
        *ppRaiz = (TNo *)malloc(sizeof(TNo));
        (*ppRaiz)->Reg = *x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        return 1;
    }
    else if ((*ppRaiz)->Reg.Chave > x->Chave)
    {
        if (Insere(&(*ppRaiz)->pEsq, x))
        {
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
    }
    else if ((*ppRaiz)->Reg.Chave < x->Chave)
    {
        if (Insere(&(*ppRaiz)->pDir, x))
        {
            if (Balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
    }
    return 0;
}

void InOrdem(TNo *pRaiz)
{
    if (pRaiz != NULL)
    {
        InOrdem(pRaiz->pEsq);
        printf("%ld ", pRaiz->Reg.Chave);
        InOrdem(pRaiz->pDir);
    }
}

void PreOrdem(TNo *pRaiz)
{
    if (pRaiz != NULL)
    {
        printf("%ld ", pRaiz->Reg.Chave);
        PreOrdem(pRaiz->pEsq);
        PreOrdem(pRaiz->pDir);
    }
}

void PosOrdem(TNo *pRaiz)
{
    if (pRaiz != NULL)
    {
        PosOrdem(pRaiz->pEsq);
        PosOrdem(pRaiz->pDir);
        printf("%ld ", pRaiz->Reg.Chave);
    }
}

void Libera(TNo *pRaiz)
{
    if (pRaiz != NULL)
    {
        Libera(pRaiz->pEsq);
        Libera(pRaiz->pDir);
        free(pRaiz);
    }
}

TNo *Busca(TNo *pRaiz, TipoChave chave)
{
    if (pRaiz == NULL)
        return NULL;

    if (chave < pRaiz->Reg.Chave)
        return Busca(pRaiz->pEsq, chave);
    else if (chave > pRaiz->Reg.Chave)
        return Busca(pRaiz->pDir, chave);
    else
        return pRaiz;
}

int main()
{
    TNo *raiz = NULL;
    Registro reg;
    int opcao, n, i;

    do
    {
        printf("\nEscolha uma opcao:\n1. Inserir valores\n2. Buscar valor\n3. em ordem\n4. pre-ordem\n5. pos-ordem\n0. Sair\nOpcao: ");
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

                if (Insere(&raiz, &reg))
                    printf("Valor %ld inserido com sucesso!\n", reg.Chave);
                else
                    printf("Erro ao inserir o valor %ld (pode já existir na árvore).\n", reg.Chave);
            }
            break;

        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%ld", &reg.Chave);

            if (Busca(raiz, reg.Chave) != NULL)
                printf("Valor %ld encontrado na árvore!\n", reg.Chave);
            else
                printf("Valor %ld não foi encontrado na árvore.\n", reg.Chave);
            break;

        case 3:
            printf("Árvore em ordem: ");
            InOrdem(raiz);
            printf("\n");
            break;

        case 4:
            printf("Árvore em pré-ordem: ");
            PreOrdem(raiz);
            printf("\n");
            break;

        case 5:
            printf("Árvore em pós-ordem: ");
            PosOrdem(raiz);
            printf("\n");
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    Libera(raiz);

    return 0;
}