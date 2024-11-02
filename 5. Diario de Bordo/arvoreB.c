//ORDEM 3
#include <stdio.h>
#include <stdlib.h>

struct elemento{
    int valor1;
    int valor2;
    struct elemento *esquerda;
    struct elemento *meio;
    struct elemento *direita;
    struct elemento *pai;
};

typedef struct elemento Elemento;

Elemento *criaNO(int valor){
    Elemento *novoNo = (Elemento *) malloc(sizeof(Elemento));
    novoNo->valor1 = valor;
    novoNo->valor2 = NULL;
    novoNo->esquerda = NULL;
    novoNo->meio = NULL;
    novoNo->direita = NULL;
    novoNo->pai = NULL;
    return novoNo;
}

Elemento *inserirElemento(Elemento *Arvore, int valor){
    if (Arvore == NULL){
        Arvore = criaNO(valor);
    }
    else if (Arvore->valor2 == NULL){
        // ENTRA SEMPRE QUE TIVER 1 SÓ NA RAIZ
        if(valor > Arvore->valor1){//checa se é maior que valor1
            if (Arvore->meio != NULL){//CHECA SE EXISTE O FILHO DO MEIO
                Arvore->meio = inserirElemento(Arvore->meio, valor);
            }
            else{ // Se ele é maior que valor1 e não existe filho do meio (ou seja não teve quebra ele entra como um elemento no array atual)
                Arvore->valor2 = valor;
            }
        }      
        else if (valor < Arvore->valor1){
            if (Arvore->esquerda != NULL){//CHECA SE EXISTE O FILHO DO MEIO
                Arvore->esquerda = inserirElemento(Arvore->esquerda, valor);
            }
            else{ // Se ele é maior que valor1 e não existe filho do meio (ou seja não teve quebra ele entra como um elemento no array atual)
                Arvore->valor2 = Arvore->valor1;
                Arvore->valor1 = valor;
            }
        }
        //CHECA SE TEM ALGUM FILHO NA ESQUERDA OU NO MEIO (SÓ TEM FILHO A DIREITA SE valor1 e valor2 FOREM DIFERENTE DE 0)
          
    }
    else{
        //SE valor1 e valor2 estão preenchidos precisa quebrar
        //PRIMEIRO DESCOBRE QUEM TÁ NO MEIO (QUE É O QUE VAI SUBIR)
        int v1 = Arvore->valor1 , v2 = Arvore->valor2;
        Elemento *novoNO = (Elemento *) malloc(sizeof(Elemento));
        if (Arvore->pai == NULL){ // NÃO TEM RAIZ EM CIMA
            if(valor > v1 && valor < v2){
                printf("valor meio");
                novoNO = criaNO(valor);
                novoNO->esquerda = criaNO(v1);
                novoNO->meio = criaNO(v2);
            }
            else if (valor < v1){
                printf("valor1 meio");
                novoNO = criaNO(v1);
                novoNO->esquerda = criaNO(valor);
                novoNO->meio = criaNO(v2);
            }
            else{
                printf("valor2 meio");
                novoNO = criaNO(v2);
                novoNO->esquerda = criaNO(v1);
                novoNO->meio = criaNO(valor);
            }
            Arvore = novoNO;
        }
        else{
            if(Arvore>pai->valor2 == NULL){
                //Só tem um elemento na RAIZ
                // checar se o valor1 do pai é maior ou menor que o novo valor entrando na raiz
                if(valor > v1 && valor < v2){
                    //valor = sobe
                    novoNO = Arvore;
                    novoNO->pai->valor2 = valor;
                    novoNO->pai->direita = criaNO(v2);
                    novoNO->pai->meio = inserirElemento(novoNO->meio, v1);
                }
                else if(valor < v1){
                    //valor1 = sobe
                    novoNO = Arvore;
                    novoNO->pai->valor2 = v1;
                    novoNO->pai->direita = criaNO(v2);
                    novoNO->pai->meio = inserirElemento(novoNO->meio, valor);
                }
                else{
                    //valor2 = sobe
                    novoNO = Arvore;
                    novoNO->pai->valor2 = v2;
                    novoNO->pai->direita = criaNO(valor);
                    novoNO->pai->meio = inserirElemento(novoNO->meio, v1);
                }
            }
        }
    }
    return Arvore;
}


int main()
{
    Elemento *Arvore = NULL;
    Arvore = inserirElemento(Arvore, 10);
    Arvore = inserirElemento(Arvore, 5);
    printf("\n%d\n", Arvore->valor1);
    printf("\n%d\n", Arvore->valor2);
    
    Arvore = inserirElemento(Arvore, 8);
    printf("\n%d\n", Arvore->valor1);
    printf("\n%d\n", Arvore->esquerda->valor1);
    printf("\n%d\n", Arvore->meio->valor1);

    
    return 0;
}
