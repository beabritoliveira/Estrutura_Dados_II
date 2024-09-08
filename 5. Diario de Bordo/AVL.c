//Beatriz Brito Oliveira
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

Elemento *filhoEsquerda(Elemento *ArvoreAVL){
    if(ArvoreAVL->esquerda == NULL){
        return ArvoreAVL;
    }
    else{
        return filhoEsquerda(ArvoreAVL->esquerda);
    }
}

Elemento *excluindoElemento(Elemento *ArvoreAVL , int valor){
    if (ArvoreAVL == NULL){
        return ArvoreAVL;
    }
    else if ( valor < ArvoreAVL->valor){
        ArvoreAVL->esquerda = excluindoElemento(ArvoreAVL->esquerda , valor);
    }
    else if ( valor > ArvoreAVL->valor){
        ArvoreAVL->direita = excluindoElemento(ArvoreAVL->direita , valor);
    }
    else{
        if(ArvoreAVL->direita == NULL){
            if(ArvoreAVL->esquerda == NULL){
                // Se o nó é folha
                //printf("NO FOLHA \n");
                ArvoreAVL = NULL;
            }
            else{
                // Se o nó tem filho na esquerda (o filho da esquerda imediato vai substituir ele na hierarquia)
                ArvoreAVL = ArvoreAVL->esquerda;
            }
        }
        // Se o filho da direita existe
        else{ 
            // Se só tem o filho da direita
             if(ArvoreAVL->esquerda == NULL){
                 ArvoreAVL = ArvoreAVL->direita;
             }
             // Se o nó tem os dois filhos (esquerdo e direito) => precisa achar o filho mais a esquerda do filho da direita
             else{
                 Elemento *maisEsquerda = filhoEsquerda(ArvoreAVL->direita); // Recupera o valor do filho mais a esquerda do filho da direita
                 Elemento *teste = excluindoElemento(ArvoreAVL, maisEsquerda->valor); // Elimina o valor do filho que vai ser substituido da arvore 
                 teste->valor = maisEsquerda->valor;
                 return teste;
             }
        }
        ArvoreAVL = balanciamento(ArvoreAVL, valor);
    }

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
