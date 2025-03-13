#include <stdio.h>
#include <stdlib.h>

typedef enum {VERMELHO, PRETO} Cor;
typedef long TipoChave;

typedef struct Registro {
    TipoChave Chave;
} Registro;

typedef struct No* Apontador;
typedef Apontador TipoDicionario;

typedef struct No {
    Registro Reg;
    Apontador pEsq, pDir;
    Cor cor;
} No;

typedef No TNo;

// Funções auxiliares
Cor getCor(Apontador no) {
    if (no == NULL)
        return PRETO;
    return no->cor;
}

void trocaCor(Apontador no) {
    if (no != NULL) {
        no->cor = (no->cor == VERMELHO) ? PRETO : VERMELHO;
    }
}

// Rotações
void RSE(TNo** ppRaiz) {
    TNo *pAux;

    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    
    pAux->cor = (*ppRaiz)->cor;
    (*ppRaiz)->cor = VERMELHO;
    
    (*ppRaiz) = pAux;
}

void RSD(TNo** ppRaiz) {
    TNo *pAux;

    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    
    pAux->cor = (*ppRaiz)->cor;
    (*ppRaiz)->cor = VERMELHO;
    
    (*ppRaiz) = pAux;
}

// Função para mover nó vermelho para a esquerda
int move_vermelho_esquerda(TNo** ppRaiz) {
    trocaCor(*ppRaiz);
    
    if (getCor((*ppRaiz)->pDir->pEsq) == VERMELHO) {
        RSD(&((*ppRaiz)->pDir));
        RSE(ppRaiz);
        trocaCor(*ppRaiz);
        return 1;
    }
    
    return 0;
}

// Função para mover nó vermelho para a direita
int move_vermelho_direita(TNo** ppRaiz) {
    trocaCor(*ppRaiz);
    
    if (getCor((*ppRaiz)->pEsq->pEsq) == VERMELHO) {
        RSD(ppRaiz);
        trocaCor(*ppRaiz);
        return 1;
    }
    
    return 0;
}

// Função para balancear a árvore
int balanceia(TNo** ppRaiz) {
    int modificado = 0;
    
    // Caso 1: No vermelho à direita
    if (getCor((*ppRaiz)->pDir) == VERMELHO && getCor((*ppRaiz)->pEsq) == PRETO) {
        RSE(ppRaiz);
        modificado = 1;
    }
    
    // Caso 2: Dois nós vermelhos consecutivos à esquerda
    if (getCor((*ppRaiz)->pEsq) == VERMELHO && getCor((*ppRaiz)->pEsq->pEsq) == VERMELHO) {
        RSD(ppRaiz);
        modificado = 1;
    }
    
    // Caso 3: Dois filhos vermelhos
    if (getCor((*ppRaiz)->pEsq) == VERMELHO && getCor((*ppRaiz)->pDir) == VERMELHO) {
        trocaCor(*ppRaiz);
        modificado = 1;
    }
    
    return modificado;
}

// Função para inserir um novo nó na árvore rubro-negra
int Insere(TNo** ppRaiz, Registro* x) {
    int inserido = 0;
    
    // Caso base: inserção em árvore vazia ou folha
    if (*ppRaiz == NULL) {
        *ppRaiz = (TNo*)malloc(sizeof(TNo));
        (*ppRaiz)->Reg = *x;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        (*ppRaiz)->cor = VERMELHO; // Novos nós sempre são vermelhos
        return 1;
    }
    
    // Inserção recursiva conforme BST tradicional
    if (x->Chave < (*ppRaiz)->Reg.Chave) {
        inserido = Insere(&((*ppRaiz)->pEsq), x);
    } else if (x->Chave > (*ppRaiz)->Reg.Chave) {
        inserido = Insere(&((*ppRaiz)->pDir), x);
    } else {
        // Chave já existe, não inserir duplicatas
        return 0;
    }
    
    // Balanceamento e correção de cores
    balanceia(ppRaiz);
    
    return inserido;
}

// Garante que a raiz sempre seja preta
void garanteRaizPreta(TNo** ppRaiz) {
    if (*ppRaiz != NULL) {
        (*ppRaiz)->cor = PRETO;
    }
}

// Função para inserir com tratamento da raiz
int InsereRB(TNo** ppRaiz, Registro* x) {
    int resultado = Insere(ppRaiz, x);
    garanteRaizPreta(ppRaiz);
    return resultado;
}

// Funções de travessia
void InOrdem(TNo* pRaiz) {
    if (pRaiz != NULL) {
        InOrdem(pRaiz->pEsq);
        printf("%ld(%c) ", pRaiz->Reg.Chave, (pRaiz->cor == VERMELHO) ? 'V' : 'P');
        InOrdem(pRaiz->pDir);
    }
}

void PreOrdem(TNo* pRaiz) {
    if (pRaiz != NULL) {
        printf("%ld(%c) ", pRaiz->Reg.Chave, (pRaiz->cor == VERMELHO) ? 'V' : 'P');
        PreOrdem(pRaiz->pEsq);
        PreOrdem(pRaiz->pDir);
    }
}

void PosOrdem(TNo* pRaiz) {
    if (pRaiz != NULL) {
        PosOrdem(pRaiz->pEsq);
        PosOrdem(pRaiz->pDir);
        printf("%ld(%c) ", pRaiz->Reg.Chave, (pRaiz->cor == VERMELHO) ? 'V' : 'P');
    }
}

// Liberar memória
void Libera(TNo* pRaiz) {
    if (pRaiz != NULL) {
        Libera(pRaiz->pEsq);
        Libera(pRaiz->pDir);
        free(pRaiz);
    }
}

// Função para buscar um valor na árvore
TNo* Busca(TNo* pRaiz, TipoChave chave) {
    if (pRaiz == NULL) 
        return NULL;
    
    if (chave < pRaiz->Reg.Chave)
        return Busca(pRaiz->pEsq, chave);
    else if (chave > pRaiz->Reg.Chave)
        return Busca(pRaiz->pDir, chave);
    else
        return pRaiz;
}

// Função para verificar se a árvore é uma RB válida (para testes)
int verifica_rn(TNo* pRaiz) {
    if (pRaiz == NULL) 
        return 1;
    
    // Verifica propriedade 3: Todo nó vermelho possui filhos pretos
    if (getCor(pRaiz) == VERMELHO) {
        if (getCor(pRaiz->pEsq) == VERMELHO || getCor(pRaiz->pDir) == VERMELHO) {
            printf("Violação: Nó vermelho com filho vermelho encontrado\n");
            return 0;
        }
    }
    
    return verifica_rn(pRaiz->pEsq) && verifica_rn(pRaiz->pDir);
}

int main() {
    TNo* raiz = NULL;
    Registro reg;
    int opcao, n, i;
    
    
    do {
        printf("\nEscolha uma opcao:\n1. Inserir valores\n2. Buscar valor\n3. em ordem\n4. pre-ordem\n5. pos-ordem\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                printf("Quantos valores deseja inserir? ");
                scanf("%d", &n);
                
                for(i = 0; i < n; i++) {
                    printf("Digite o valor %d: ", i+1);
                    scanf("%ld", &reg.Chave);
                    
                    if (InsereRB(&raiz, &reg))
                        printf("Valor %ld inserido com sucesso!\n", reg.Chave);
                    else
                        printf("Erro ao inserir o valor %ld (pode já existir na árvore).\n", reg.Chave);
                }
                break;
                
            case 2:
                printf("Digite o valor a ser buscado: ");
                scanf("%ld", &reg.Chave);
                
                TNo* resultado = Busca(raiz, reg.Chave);
                if (resultado != NULL)
                    printf("Valor %ld encontrado na árvore! Cor: %s\n", 
                          reg.Chave, (resultado->cor == VERMELHO) ? "Vermelho" : "Preto");
                else
                    printf("Valor %ld não foi encontrado na árvore.\n", reg.Chave);
                break;
                
            case 3:
                printf("Árvore em ordem (valor(cor)): ");
                InOrdem(raiz);
                printf("\n");
                break;
                
            case 4:
                printf("Árvore em pré-ordem (valor(cor)): ");
                PreOrdem(raiz);
                printf("\n");
                break;
                
            case 5:
                printf("Árvore em pós-ordem (valor(cor)): ");
                PosOrdem(raiz);
                printf("\n");
                break;
                
            case 6:
                if (verifica_rn(raiz))
                    printf("A árvore obedece às propriedades rubro-negras!\n");
                else
                    printf("A árvore NÃO obedece às propriedades rubro-negras.\n");
                    
                if (raiz != NULL && getCor(raiz) != PRETO)
                    printf("Aviso: A raiz não é preta!\n");
                break;
                
            case 0:
                printf("Saindo...\n");
                break;
                
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);
    
    // Liberar memória antes de encerrar
    Libera(raiz);
    
    return 0;
}
