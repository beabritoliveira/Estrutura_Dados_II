#include <stdio.h>
#include <stdlib.h>

// Definição dos possíveis valores de cor
#define VERM 0
#define PRET 1

// Definição da estrutura de um nó da árvore Red-Black
struct elemento{
    int valor;
    struct elemento *esquerda;
    struct elemento *direita;
    struct elemento *pai;
    int cor;
};

typedef struct elemento Elemento;

Elemento *rotacao_esquerda(Elemento *RB)
{
    Elemento *raiz = (Elemento *) malloc (sizeof(Elemento));
    raiz = RB->pai;
    raiz->direita = raiz->pai;
    raiz->pai = raiz->direita->pai;
    raiz->direita->pai = raiz;
    RB = raiz;
    return RB;
}

Elemento *rotacao_direita(Elemento *RB)
{
    Elemento *raiz = (Elemento *) malloc (sizeof(Elemento));
    raiz = RB->pai;
    raiz->esquerda = raiz->pai;
    raiz->pai = raiz->esquerda->pai;
    raiz->esquerda->pai = raiz;
    RB = raiz;
    return RB;
}


int contagem_pretos(Elemento *RB){
    int esq, dir;
    if(RB == NULL){
        return RB->cor;
    }
    else{
        esq = contagem_pretos(RB->esquerda);
        dir = contagem_pretos(RB->direita);
        
    }
    return esq - dir;
}


void balan_color(Elemento *novoNO){
    if (novoNO->pai != NULL){
        if (novoNO->cor == VERM && novoNO->pai->cor == VERM){
            if ( novoNO->pai->esquerda == NULL || novoNO->pai->direita == NULL){
                novoNO->pai->cor = PRET;
            }
            else{
                novoNO->cor = PRET;
            }
        }
        
        int cp = contagem_pretos(novoNO);
        if (cp > 0){
           novoNO = rotacao_direita(novoNO);
        }
        else if (cp < 0){
            novoNO = rotacao_esquerda(novoNO);
        }
    }
}


Elemento *criarNo(int valor){
    Elemento *novoNo = (Elemento *) malloc(sizeof(Elemento));
    novoNo->valor = valor;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->cor = VERM;
    return novoNo;
}

Elemento *inseriFolha(int valor, Elemento *RedBlack){
    if (RedBlack == NULL){
        RedBlack = criarNo(valor);
        RedBlack->pai = NULL;
        RedBlack->cor = PRET;
    }
    else{
        if (valor < RedBlack->valor){ // SE O VALOR É MENOR QUE O VALOR COMPARADO DA RAIZ
            if(RedBlack->esquerda == NULL){
                RedBlack->esquerda = criarNo(valor);
                RedBlack->esquerda->pai = RedBlack;
                balan_color(RedBlack->esquerda);
            }
            else{
                RedBlack->esquerda = inseriFolha(valor, RedBlack->esquerda);
            }
        }
        else if (valor > RedBlack->valor){ // SE O VALOR É MAIOR QUE O VALOR COMPARADO DA RAIZ
            if(RedBlack->direita == NULL){
                RedBlack->direita = criarNo(valor);
                RedBlack->direita->pai = RedBlack;
                balan_color(RedBlack->direita);
            }
            else{
                RedBlack->direita = inseriFolha(valor, RedBlack->direita);
            }
        }
    }
    
    return RedBlack;
}

// Função para imprimir a árvore (do professor)
void imprimeArvoreRB(Elemento *raiz, int b)
{
    if (raiz != NULL)
    {
        // Chama a função recursivamente para percorrer a subárvore direita
        imprimeArvoreRB(raiz->direita, b + 1);

        // Imprime o valor do nó atual com um espaçamento proporcional à sua profundidade
        for (int i = 0; i < b; i++)
            printf("       "); // espaços por nível
        if (raiz->cor == 0)
            printf("\033[31m%d\033[0m\n\n", raiz->valor);
        else
            printf("%d\n\n", raiz->valor);

        // Chama a função recursivamente para percorrer a subárvore esquerda
        imprimeArvoreRB(raiz->esquerda, b + 1);
    }
}

int main(){
    Elemento *arvore = NULL;
    arvore = inseriFolha(10, arvore);
    arvore = inseriFolha(20, arvore);
    arvore = inseriFolha(6, arvore);
    arvore = inseriFolha(30, arvore);
    arvore = inseriFolha(40, arvore);
    arvore = inseriFolha(17, arvore);
    arvore = inseriFolha(23, arvore);
    arvore = inseriFolha(18, arvore);
    arvore = inseriFolha(1, arvore);
    arvore = inseriFolha(3, arvore);
    arvore = inseriFolha(22, arvore);
    arvore = inseriFolha(21, arvore);
    printf("Árvore Red-Black: \n");
    imprimeArvoreRB(arvore, 3);

    return 0;
}
