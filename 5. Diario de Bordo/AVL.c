// BEATRIZ BRITO OLIVEIRA
#include <stdio.h>
#include <stdlib.h>

struct elemento{
    int valor;
    struct elemento *esquerda;
    struct elemento *direita;
    int altura;
};

typedef struct elemento Elemento;

//IMPRIMI O VALOR DO NÓ E A SUA ALTURA
void imprimindoArvore(Elemento *ArvoreB){
    if(ArvoreB == NULL)
        return;
    
    imprimindoArvore(ArvoreB->esquerda);
    printf("%d - %d\n", ArvoreB->valor, ArvoreB->altura);
    imprimindoArvore(ArvoreB->direita);
}

//CALCULA A ALTURA DE CADA NÓ DA ÁRVORE
int recAltura(Elemento *ArvoreAVL){
    if(ArvoreAVL == NULL){
        // SETADO COMO ZERO JÁ QUE SEMPRE QUE O NÓ É FOLHA ELE VAI TER COMO ALTURA 0, JÁ QUE É SOMADO 1 MAIS TARDE
        return -1;
    }
    
    int esq = -2, dir = -2;
    // CALCULA O VALOR DOS FILHOS DA ESQUERDA E DA DIREITA E SOMA MAIS UM JÁ QUE CADA Npai = Nfilho + 1
    esq  = 1 + recAltura(ArvoreAVL->esquerda);
    dir = 1 + recAltura(ArvoreAVL->direita);
    
    // COMPARA QUAL FILHO TEM MAIOR ALTURA, QUAL CAMINHO É MAIS LONGO, PARA DEFINIR A ALTURA CORRETA
    if(esq > dir){
        ArvoreAVL->altura = esq;
    }
    else {
        ArvoreAVL->altura = dir;
    }
    
    return ArvoreAVL->altura ;
}

// DEFININDO O FATOR DE BALANCEAMENTO DE CADA NÓ
int fatorBalanceamento(Elemento *ArvoreAVL){
    if(ArvoreAVL == NULL){
        return 0;
    }
    else{
        if(ArvoreAVL->esquerda != NULL){ // SE O FILHO A ESQUERDA EXISTE
            if (ArvoreAVL->direita != NULL){ // SE O FILHO A DIREITA TAMBÉM EXISTE
                return ArvoreAVL->esquerda->altura - ArvoreAVL->direita->altura; // FATOR DE BALANCEMANETO É SEMPRE FB = filho_esquerda - filho_direita
            }
            else{
                // SE SÓ EXISTE FILHO A ESQUERDA É O TAMANHO DO CAMINHO DA ESQUERDA MAIS UM A SUA ALTURA
                return ArvoreAVL->esquerda->altura + 1;
            }
        }
        else if (ArvoreAVL->direita != NULL){
            // SE SÓ EXISTE FILHO A DIREITA É O TAMANHO DO CAMINHO DA DIREITA MAIS UM A SUA ALTURA E COMO É A DIREITA O SINAL É NEGATIVO
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
    recAltura(ArvoreAVL); //Recalculando a altura da árvore
    return ArvoreAVL;
}

Elemento *rotacaoDireita(Elemento *ArvoreAVL){
    Elemento *NovaDireita = (Elemento *) malloc (sizeof(Elemento));
    NovaDireita = ArvoreAVL; // Define o valor atual da raiz como a nova direita
    ArvoreAVL = ArvoreAVL->esquerda; // Passa o valor do filho da esquerda para ser a nova raiz 
    NovaDireita->esquerda = ArvoreAVL->direita; //Define o filho que os filhos da direita do antigo filho da esquerda virem filhos a esquerda do novo filho da direita (antiga raiz)
    ArvoreAVL->direita = NovaDireita;
    recAltura(ArvoreAVL); //Recalculando a altura da árvore
    return ArvoreAVL;
}

// DEFINE SE A ÁRVORE NECESSITA DE ROTAÇÃO OU NÃO; SE O FATOR DE BALANCEAMENTO É DIFERENTE 1,0 OU -1 HÁ ROTAÇÃO
Elemento *balanciamento(Elemento *ArvoreAVL, int valor){
    int fB = fatorBalanceamento(ArvoreAVL);
    if(fB < -1){
        if(fatorBalanceamento(ArvoreAVL->direita) < 0){ 
            // SE O NÓ DO FILHO A DIREITA É NEGATIVO SIGNIFICA QUE A ROTAÇÃO É SIMPLES, OU SEJA ELES TÃO NA MESMA DIREÇÃO (\)
            //printf("ROTAÇÃO SIMPLES A ESQUERDA\n");
            ArvoreAVL = rotacaoEsquerda(ArvoreAVL);
        }
        else{
            // SE O NÓ DO FILHO A DIREITA É POSITIVO SIGNIFICA QUE A ROTAÇÃO É DUPLA, OU SEJA ELES NÃO ESTÃO NA MESMA DIREÇÃO (>)
            //printf("ROTAÇÃO DUPLA A ESQUERDA\n"); // RSD + RSE
            ArvoreAVL->direita = rotacaoDireita(ArvoreAVL->direita);
            ArvoreAVL = rotacaoEsquerda(ArvoreAVL);
        }
    }
    else if (fB > 1 ){
        if(fatorBalanceamento(ArvoreAVL->esquerda) > 0){
            // SE O NÓ DO FILHO A ESQUERDA É POSITIVO SIGNIFICA QUE A ROTAÇÃO É SIMPLES, OU SEJA ELES TÃO NA MESMA DIREÇÃO (/)
            //printf("ROTAÇÃO SIMPLES A DIREITA\n");
            ArvoreAVL = rotacaoDireita(ArvoreAVL);
        }
        else{
            // SE O NÓ DO FILHO A ESQUERDA É NEGATIVO SIGNIFICA QUE A ROTAÇÃO É DUPLA, OU SEJA ELES NÃO ESTÃO NA MESMA DIREÇÃO (<)
            //printf("ROTAÇÃO DUPLA A DIREITA\n"); // RSE + RSD
            ArvoreAVL->esquerda = rotacaoEsquerda(ArvoreAVL->esquerda);
            ArvoreAVL = rotacaoDireita(ArvoreAVL);
        }
    }
    return ArvoreAVL;
}

// INSERÇÃO DE ELEMENTO NA ÁRVORE
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
        if (valor < ArvoreAVL->valor){ // SE O VALOR É MENOR QUE O VALOR COMPARADO DA RAIZ
            ArvoreAVL->esquerda = inseriFolha(valor, ArvoreAVL->esquerda);
        }
        else if (valor > ArvoreAVL->valor){ // SE O VALOR É MAIOR QUE O VALOR COMPARADO DA RAIZ
            ArvoreAVL->direita = inseriFolha(valor, ArvoreAVL->direita);
        }
    }
    
    //RECALCULA A ALTURA DA ARVORE PARA CALCULAR O BALANCIAMENTO DEPOIS 
    recAltura(ArvoreAVL);
    ArvoreAVL = balanciamento(ArvoreAVL, valor);
    
    return ArvoreAVL;
}

// ENCONTRA O FILHO MAIS A ESQUERDA 
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
        recAltura(ArvoreAVL);
    }
    else if ( valor > ArvoreAVL->valor){
        ArvoreAVL->direita = excluindoElemento(ArvoreAVL->direita , valor);
        recAltura(ArvoreAVL);
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
        // CALCULA O NOVO BALANCIAMENTO
        ArvoreAVL = balanciamento(ArvoreAVL,valor);
    }

    return ArvoreAVL;
}

int main(){
    printf("-- INSERINDO ELEMENTO --\n");
    Elemento *arvore = NULL;
    arvore = inseriFolha(10, arvore);
    arvore = inseriFolha(20, arvore);
    arvore = inseriFolha(6, arvore);
    arvore = inseriFolha(30, arvore);
    //ROTAÇÃO SIMPLES A ESQUERDA
    arvore = inseriFolha(40, arvore);
    //ROTAÇÃO DUPLA A ESQUERDA
    arvore = inseriFolha(17, arvore);
    arvore = inseriFolha(23, arvore);
    arvore = inseriFolha(18, arvore);
    arvore = inseriFolha(1, arvore);
    //ROTAÇÃO DUPLA A DIREITA
    arvore = inseriFolha(3, arvore);
    arvore = inseriFolha(22, arvore);
    //ROTAÇÃO SIMPLES A DIREITA
    arvore = inseriFolha(21, arvore);
    imprimindoArvore(arvore);
    
    
    printf("\n\n-- EXCLUINDO ELEMENTO --\n");
    //REMOVENDO NÓS
    arvore = (excluindoElemento(arvore, 23));
    arvore = (excluindoElemento(arvore, 21));
    // removendo a raiz
    arvore = (excluindoElemento(arvore, 20));
    // excluindo nó com filho
    arvore = (excluindoElemento(arvore, 17));
    imprimindoArvore(arvore);
    
    return 0;
}
