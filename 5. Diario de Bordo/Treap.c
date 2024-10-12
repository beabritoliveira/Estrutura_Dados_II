// Beatriz Brito Oliveira
#include <stdio.h>
#include <stdlib.h>

struct elemento{
  int valor;
  int prioridade;
  struct elemento *pai;
  struct elemento *esq;
  struct elemento *dir;
};

typedef struct elemento Elemento;

Elemento *inserirElemento(Elemento *Arvore, int valor, int prioridade){
    Elemento *Treap = (Elemento *) malloc(sizeof(Elemento));
    if (Arvore == NULL){
      // Se a árvore tá vazia 
        Treap->valor = valor;
        Treap->prioridade = prioridade;
        Treap->esq = NULL;
        Treap->dir = NULL;
        Treap->pai = NULL;
        Arvore = Treap;
    }
    else{
        if(prioridade < Arvore->prioridade ){ // Checa para colocar o número de maior prioridade na raiz da árvore
            //Vai virar um dos filhos
            if (valor < Arvore->valor){ 
                //Vira o filho da esquerda
                Arvore->esq = inserirElemento(Arvore->esq, valor, prioridade);
                Arvore->esq->pai = Arvore;
            }
            else{
                //Vira o filho da direita
                Arvore->dir = inserirElemento(Arvore->dir, valor, prioridade);
                Arvore->dir->pai = Arvore;
            }
        }
        else{
            //Vai subir para ser uma raiz 
            Treap->valor = valor;
            Treap->prioridade = prioridade;
            Treap->pai = NULL;
            if (valor < Arvore->valor){
                Treap->dir = Arvore;
                Treap->esq = NULL;
            }
            else{
                Treap->esq = Arvore;
                Treap->dir = NULL;
            }
            Arvore->pai = Treap;
            Arvore = Treap;
        }
    }
    
    return Arvore;
}

//IMPRIMI O VALOR DO NÓ E A SUA ALTURA
void imprimindoArvore(Elemento *Arvore){
    if(Arvore == NULL)
        return;
    
    imprimindoArvore(Arvore->esq);
    printf("%d - %d\n", Arvore->valor, Arvore->prioridade);
    imprimindoArvore(Arvore->dir);
}

int main()
{
    printf("-- INSERINDO ELEMENTO --\n");
    Elemento *arvore = NULL;
    arvore = inserirElemento(arvore, 7, 37);
    arvore = inserirElemento(arvore, 9, 3);
    arvore = inserirElemento(arvore, 11, 80);
    arvore = inserirElemento(arvore, 14, 78);
    arvore = inserirElemento(arvore, 1, 33);
    arvore = inserirElemento(arvore, 16, 54);
    arvore = inserirElemento(arvore, 18, 98);
    arvore = inserirElemento(arvore, 15, 29);
    arvore = inserirElemento(arvore, 17, 11);
    arvore = inserirElemento(arvore, 27, 70);
    imprimindoArvore(arvore);
    return 0;
}
