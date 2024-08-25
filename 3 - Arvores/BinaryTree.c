// Beatriz Brito Oliveira
#include <stdio.h>
#include <stdlib.h>
//Definindo a estrutura da árvore
struct elemento{
    int valor;
    struct elemento *esquerda;
    struct elemento *direita;
};

typedef struct elemento Elemento;

Elemento *inserirElemento(Elemento *ArvoreB, int valor){
    if(ArvoreB == NULL){
        //printf("ENTROU\n");
        Elemento *novaFolha;
        novaFolha = (Elemento *) malloc(sizeof(Elemento));
        novaFolha->valor = valor;
        novaFolha->esquerda = NULL;    
        novaFolha->direita = NULL; 
        ArvoreB = novaFolha;
    }
    else{
        if (ArvoreB->valor == valor){
            return ArvoreB;
        }
        else if ( valor < ArvoreB->valor){
            //printf("ENTROU NA ESQUERDA");
            ArvoreB->esquerda = inserirElemento(ArvoreB->esquerda , valor);
        }
        else{
            //printf("ENTROU NA DIREITA");
            ArvoreB->direita = inserirElemento(ArvoreB->direita , valor);
        }
    }
    return ArvoreB;
}

void imprimindoArvore(Elemento *ArvoreB){
    if(ArvoreB == NULL)
        return;
    imprimindoArvore(ArvoreB->esquerda);
    printf("%d ", ArvoreB->valor);
    imprimindoArvore(ArvoreB->direita);
}

// Retorna 1 se encontrou correspondência e 0 se não
int checandoExistencia(Elemento *ArvoreB, int valor){
    if(ArvoreB == NULL){
        Elemento *raiz = NULL;
        return 0;
    }
    else{
        if (ArvoreB->valor == valor)
            return 1;
        else if ( valor < ArvoreB->valor){
            return checandoExistencia(ArvoreB->esquerda , valor);
        }
        else{
            return checandoExistencia(ArvoreB->direita , valor);
        }
    }
}

Elemento *filhoEsquerda(Elemento *ArvoreB){
    if(ArvoreB->esquerda == NULL){
        return ArvoreB;
    }
    else{
        return filhoEsquerda(ArvoreB->esquerda);
    }
}

Elemento *excluindoElemento(Elemento *ArvoreB , int valor){
    // Importante armazenar o valor anterior para realocar o valor do proximo nó
    // Se o nó for folha (ou seja FILHO ESQUERDA E DIREITA FOR NULO SÓ EXCLUIR E NÃO TEM MAIS NADA PRA FAZER)
    // Se o nó tem filho a direita ele deve pegar o valor mais a esquerda do filho da direita
    // Se o nó tiver apenas filho a esquerda ou da direita pega o nó mais imediato

    // Recursividade para não perder os elementos do vetor; 
    if (ArvoreB == NULL){
        //1) Verifica se a árvore tá vazia ou se rodou toda a arvore e não encontrou correspondência
        return ArvoreB;
    }
    //Percorrendo a árvore
    else if ( valor < ArvoreB->valor){
        ArvoreB->esquerda = excluindoElemento(ArvoreB->esquerda , valor);
    }
    else if ( valor > ArvoreB->valor){
        ArvoreB->direita = excluindoElemento(ArvoreB->direita , valor);
    }
    else{ // (ArvoreB->valor == valor)  =>  Se achou o nó correspondente na árvore
        // Se o nó não tem filho a direita ou é nó folha
        if(ArvoreB->direita == NULL){
            if(ArvoreB->esquerda == NULL){
                // Se o nó é folha
                //printf("NO FOLHA \n");
                ArvoreB = NULL;
            }
            else{
                // Se o nó tem filho na esquerda (o filho da esquerda imediato vai substituir ele na hierarquia)
                ArvoreB = ArvoreB->esquerda;
            }
        }
        // Se o filho da direita existe
        else{ 
            // Se só tem o filho da direita
             if(ArvoreB->esquerda == NULL){
                 ArvoreB = ArvoreB->direita;
             }
             // Se o nó tem os dois filhos (esquerdo e direito) => precisa achar o filho mais a esquerda do filho da direita
             else{
                 Elemento *maisEsquerda = filhoEsquerda(ArvoreB->direita); // Recupera o valor do filho mais a esquerda do filho da direita
                 Elemento *teste = excluindoElemento(ArvoreB, maisEsquerda->valor); // Elimina o valor do filho que vai ser substituido da arvore 
                 teste->valor = maisEsquerda->valor;
                 return teste;
             }
        }
    }

    return ArvoreB;
}

void BuscarElemento(Elemento *ArvoreB , int valor){
    if(ArvoreB == NULL){
        printf("Não foi encontrado o elemento %d \n", valor);
        return;
    }
    if(ArvoreB->valor == valor){
    printf("Elemento %d encontrado na árvore\n", valor);
    return;
    }
    else if(valor < ArvoreB->valor){
        return BuscarElemento(ArvoreB->esquerda, valor);
    }
    else{
        return BuscarElemento(ArvoreB->direita, valor);
    }
    return;
}


int main(){
    // Criando a estrutura da árvore binária
    Elemento *arvore = NULL;

    arvore = inserirElemento(arvore , 10);
    arvore = inserirElemento(arvore , 9);
    arvore = inserirElemento(arvore , 15);
    arvore = inserirElemento(arvore , 11);
    arvore = inserirElemento(arvore , 13);
    arvore = inserirElemento(arvore , 20);
    arvore = inserirElemento(arvore , 8);
    arvore = inserirElemento(arvore , 10);
    arvore = inserirElemento(arvore , 5);
    arvore = inserirElemento(arvore , 7);
    arvore = inserirElemento(arvore , 18);
    arvore = inserirElemento(arvore , 16);

    printf("------ INSERINDO ELEMENTOS ------\n");
    imprimindoArvore(arvore);

    printf("\n\n------ EXCLUINDO ELEMENTOS ------\n");
    //Exemplo de exclusão de nó folha
    arvore = excluindoElemento(arvore, 16);
    imprimindoArvore(arvore);
    printf("\n");
    //Exemplo de exclusão de nó que só tem filho a esquerda
    arvore = excluindoElemento(arvore, 9);
    imprimindoArvore(arvore);
    printf("\n");
    //Exemplo de exclusão de nó que só tem filho a direita
    arvore = excluindoElemento(arvore, 11);
    imprimindoArvore(arvore);
    printf("\n");
    //Exemplo de exclusão de nó que só tem os dois filhos
    arvore = excluindoElemento(arvore, 10);
    imprimindoArvore(arvore);

    printf("\n\n------ BUSCANDO ELEMENTOS ------\n");
    BuscarElemento(arvore, 10);
    BuscarElemento(arvore, 8);
    BuscarElemento(arvore, 20);
    BuscarElemento(arvore, 7);
    BuscarElemento(arvore, 25);

    return 0;
}
