// Beatriz Brito Oliveira
#include <stdio.h>
#include <stdlib.h>

// 1°) DEFININDO A ESTRUTURA DA ÁRVORE
struct elemento{
    int valor;
    struct elemento *esquerda;
    struct elemento *direita;
    int altura;
};

typedef struct elemento Elemento;

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

void *balanciamento(Elemento *ArvoreAVL, int valor){
    int fB = fatorBalanceamento(ArvoreAVL);
    if(fB < -1){
        if(fatorBalanceamento(ArvoreAVL->direita) < 0){
            printf("ROTAÇÃO SIMPLES A ESQUERDA\n");
            return rotacaoEsquerda(ArvoreAVL);
        }
        else{
            printf("ROTAÇÃO DUPLA A ESQUERDA\n");
            ArvoreAVL->direita = rotacaoDireita(ArvoreAVL->direita);
            return rotacaoEsquerda(ArvoreAVL);
        }
    }
    else if (fB > 1 ){
        if(fatorBalanceamento(ArvoreAVL->esquerda) > 0){
            printf("ROTAÇÃO SIMPLES A DIREITA\n");
            return rotacaoDireita(ArvoreAVL);
        }
        else{
            printf("ROTAÇÃO DUPLA A DIREITA\n");
            ArvoreAV->esquerda = rotacaoEsquerda(ArvoreAVL->esquerda);
            return rotacaoDireita(ArvoreAVL);
        }
    }
}

Elemento *rotacaoEsquerda(Elemento *ArvoreAVL){
    
}

Elemento *rotacaoDireita(Elemento *ArvoreAVL){
    
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
    
    //RECALCULANDO ALTURA DE CADA NÓ
    if(ArvoreAVL->direita != NULL){
        if(ArvoreAVL->esquerda != NULL){
            if(ArvoreAVL->direita->altura > ArvoreAVL->esquerda->altura){
                ArvoreAVL->altura = 1 + ArvoreAVL->direita->altura;
            }
            else{
                ArvoreAVL->altura = 1 + ArvoreAVL->esquerda->altura;
            }
        }
        else{
            ArvoreAVL->altura = 1 + ArvoreAVL->direita->altura;
        }
    }
    else if (ArvoreAVL->esquerda != NULL){
        ArvoreAVL->altura = 1 + ArvoreAVL->esquerda->altura;
    }
    
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
    
    return 0;
}
