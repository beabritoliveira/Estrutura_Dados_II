// Beatriz Brito Oliveira
#include <stdio.h>
#include <stdlib.h>

struct elemento{
    int valor;
    struct elemento *esquerda;
    struct elemento *direita;
    int altura;
};

typedef struct elemento Elemento;

void imprimindoArvore(Elemento *ArvoreB){
    if(ArvoreB == NULL)
        return;
    
    imprimindoArvore(ArvoreB->esquerda);
    printf("%d - %d\n", ArvoreB->valor, ArvoreB->altura);
    imprimindoArvore(ArvoreB->direita);
}

int recAltura(Elemento *ArvoreAVL){
    if(ArvoreAVL == NULL){
        return -1;
    }
    
    int esq = -2, dir = -2;
    esq  = 1 + recAltura(ArvoreAVL->esquerda);
    dir = 1 + recAltura(ArvoreAVL->direita);
    
    if(esq > dir){
        ArvoreAVL->altura = esq;
    }
    else {
        ArvoreAVL->altura = dir;
    }
    
    return ArvoreAVL->altura ;
}

int fatorBalanceamento(Elemento *ArvoreAVL){
    if(ArvoreAVL == NULL){
        return 0;
    }
    else{
        if(ArvoreAVL->esquerda != NULL){
            if (ArvoreAVL->direita != NULL){
                return ArvoreAVL->esquerda->altura - ArvoreAVL->direita->altura;
            }
            else{
                return ArvoreAVL->esquerda->altura + 1;
            }
        }
        else if (ArvoreAVL->direita != NULL){
            return - (ArvoreAVL->direita->altura + 1);
        }        
    }

}

Elemento *rotacaoEsquerda(Elemento *ArvoreAVL){
    // 1°) Pega o filho da esquerda da raiz e torna ele como a nova raiz
    // 2°) Pega a raiz antiga e torna ela como o filho da esquerda
    Elemento *NovaEsquerda = (Elemento *) malloc (sizeof(Elemento));
    NovaEsquerda = ArvoreAVL; //Tornando a raiz o filho da esquerda
    ArvoreAVL = ArvoreAVL->direita; // A raiz se tornando o filho da direita
    NovaEsquerda->direita = ArvoreAVL->esquerda; // Passando os filhos da esquerda da dirieta em filhos da direita da esquerda
    ArvoreAVL->esquerda = NovaEsquerda;
    return ArvoreAVL;
}

Elemento *rotacaoDireita(Elemento *ArvoreAVL){
    Elemento *NovaDireita = (Elemento *) malloc (sizeof(Elemento));
    NovaDireita = ArvoreAVL;
    ArvoreAVL = ArvoreAVL->esquerda; 
    NovaDireita->esquerda = ArvoreAVL->direita; 
    ArvoreAVL->direita = NovaDireita;
    return ArvoreAVL;
}

Elemento *balanciamento(Elemento *ArvoreAVL, int valor){
    int fB = fatorBalanceamento(ArvoreAVL);
    if(fB < -1){
        if(fatorBalanceamento(ArvoreAVL->direita) < 0){
            //printf("ROTAÇÃO SIMPLES A ESQUERDA\n");
            ArvoreAVL = rotacaoEsquerda(ArvoreAVL);
        }
        else{
            //printf("ROTAÇÃO DUPLA A ESQUERDA\n");
            ArvoreAVL->direita = rotacaoDireita(ArvoreAVL->direita);
            recAltura(ArvoreAVL);
            ArvoreAVL = rotacaoEsquerda(ArvoreAVL);
        }
    }
    else if (fB > 1 ){
        if(fatorBalanceamento(ArvoreAVL->esquerda) > 0){
            //printf("ROTAÇÃO SIMPLES A DIREITA\n");
            ArvoreAVL = rotacaoEsquerda(ArvoreAVL);
        }
        else{
            //printf("ROTAÇÃO DUPLA A DIREITA\n");
            ArvoreAVL->esquerda = rotacaoEsquerda(ArvoreAVL->esquerda);
            recAltura(ArvoreAVL);
            ArvoreAVL = rotacaoDireita(ArvoreAVL);
        }
    }
    recAltura(ArvoreAVL);
    return ArvoreAVL;
}

Elemento *inseriFolha(int valor, Elemento *ArvoreAVL){
    if (ArvoreAVL == NULL){
        //printf("FOLHA OU ÁRVORE VAZIA");
        Elemento *novoNo = (Elemento *) malloc(sizeof(Elemento));
        novoNo->valor = valor;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        novoNo->altura = 0; //Um elemento sempre entra como folha, logo sua altura é 0
        ArvoreAVL = novoNo;
    }
    else{
        if (valor < ArvoreAVL->valor){
            ArvoreAVL->esquerda = inseriFolha(valor, ArvoreAVL->esquerda);
        }
        else if (valor > ArvoreAVL->valor){
            ArvoreAVL->direita = inseriFolha(valor, ArvoreAVL->direita);
        }
    }
    
    recAltura(ArvoreAVL);
    ArvoreAVL = balanciamento(ArvoreAVL, valor);
    
    return ArvoreAVL;
}


int main(){
    Elemento *arvore = NULL;
    arvore = inseriFolha(10, arvore);
    arvore = inseriFolha(20, arvore);
    arvore = inseriFolha(5, arvore);
    arvore = inseriFolha(30, arvore);
    arvore = inseriFolha(40, arvore);
    arvore = inseriFolha(3, arvore);
    imprimindoArvore(arvore);
    
    return 0;
}
