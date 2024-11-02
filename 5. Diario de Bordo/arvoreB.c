//Código de Árvore B de ORDEM 3
//Beatriz Brito Oliveira
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
        // SE A ARVORE->PAI == NULL ELA É A MAIOR RAIZ
        if(Arvore->pai != NULL){
            //1° DESCOBRE QUEM TÁ NO MEIO
            if(Arvore->pai->valor2 != NULL){
                v1 = Arvore->pai->valor1 , v2 = Arvore->pai->valor2;
                //Precisa escalar um nível
                //printf("Adiciona um nível");
                if(valor > v1 && valor < v2){
                    //printf("valor meio");
                    novoNO = criaNO(valor);
                    novoNO->esquerda = criaNO(v1);
                    if(Arvore->esquerda != NULL)
                        novoNO->esquerda->esquerda = Arvore->esquerda;
                    novoNO->meio = criaNO(v2);
                    if(Arvore->direita != NULL)
                        novoNO->meio->meio = Arvore->direita;
                    //Checa o primeiro valor da arvore meio anterior para saber se entra na esquerda ou menio atual
                    if(Arvore->meio != NULL){
                        if(Arvore->meio->valor1 > valor){
                        novoNO->meio->esquerda = Arvore->meio;
                        }
                        else{
                            novoNO->esquerda->meio = Arvore->meio;
                        }
                    }
                    
                }
                else if (valor < v1){
                    //printf("valor1 meio");
                    novoNO = criaNO(v1);
                    novoNO->esquerda = criaNO(valor);
                    if(Arvore->esquerda != NULL){
                        novoNO->esquerda->meio = Arvore->esquerda;
                    }
                    novoNO->meio = criaNO(v2);
                    if(Arvore->meio != NULL){
                        novoNO->meio->esquerda = Arvore->meio;
                    }
                    if (Arvore->direita != NULL){
                        novoNO->meio->meio = Arvore->direita;
                    }
                }
                else{
                    //printf("valor2 meio");
                    novoNO = criaNO(v2);
                    novoNO->esquerda = criaNO(v1);
                    if(Arvore->esquerda != NULL){
                        novoNO->esquerda->esquerda = Arvore->esquerda;
                    }
                    if(Arvore->meio != NULL){
                        novoNO->esquerda->meio = Arvore->meio;
                    }
                    novoNO->meio = criaNO(valor);
                    if (Arvore->direita != NULL){
                        novoNO->meio->esquerda = Arvore->direita;
                    }
                }
                Arvore = novoNO;
            }
            else{
                //printf("Adiciona um na raiz");
                if(Arvore->pai->valor1 > valor){
                    Arvore->pai->valor2 = Arvore->pai->valor1;
                    Arvore->pai->direita = Arvore->pai->meio;
                    Arvore->pai->meio = Arvore->pai->esquerda;
                    Arvore->pai->valor1 = valor;
                }
            }
        }
        else{
           // printf("Cria a raiz");
            if(valor > v1 && valor < v2){
                printf("valor meio");
                novoNO = criaNO(valor);
                novoNO->esquerda = criaNO(v1);
                if(Arvore->esquerda != NULL)
                    novoNO->esquerda->esquerda = Arvore->esquerda;
                novoNO->meio = criaNO(v2);
                if(Arvore->direita != NULL)
                    novoNO->meio->meio = Arvore->direita;
                //Checa o primeiro valor da arvore meio anterior para saber se entra na esquerda ou menio atual
                if(Arvore->meio != NULL){
                    if(Arvore->meio->valor1 > valor){
                    novoNO->meio->esquerda = Arvore->meio;
                    }
                    else{
                        novoNO->esquerda->meio = Arvore->meio;
                    }
                }
                
            }
            else if (valor < v1){
                printf("valor1 meio");
                novoNO = criaNO(v1);
                novoNO->esquerda = criaNO(valor);
                if(Arvore->esquerda != NULL){
                    novoNO->esquerda->meio = Arvore->esquerda;
                }
                novoNO->meio = criaNO(v2);
                if(Arvore->meio != NULL){
                    novoNO->meio->esquerda = Arvore->meio;
                }
                if (Arvore->direita != NULL){
                    novoNO->meio->meio = Arvore->direita;
                }
            }
            else{
                printf("valor2 meio");
                novoNO = criaNO(v2);
                novoNO->esquerda = criaNO(v1);
                if(Arvore->esquerda != NULL){
                    novoNO->esquerda->esquerda = Arvore->esquerda;
                }
                if(Arvore->meio != NULL){
                    novoNO->esquerda->meio = Arvore->meio;
                }
                novoNO->meio = criaNO(valor);
                if (Arvore->direita != NULL){
                    novoNO->meio->esquerda = Arvore->direita;
                }
            }
            Arvore = novoNO;
        }
    }
    return Arvore;
}


int main()
{
    Elemento *Arvore = NULL;
    Arvore = inserirElemento(Arvore, 10);
    Arvore = inserirElemento(Arvore, 5);
    Arvore = inserirElemento(Arvore, 20);
    
    printf("\nNOVA INSERÇÃO\n");
    Arvore = inserirElemento(Arvore, 15);
    printf("\n%d\n", Arvore->valor1); // 10
    printf("\n%d\n", Arvore->esquerda->valor1); //5
    printf("\n%d\n", Arvore->meio->valor1); //15
    printf("\n%d\n", Arvore->meio->valor2); //20
    
    printf("\n\nNOVA INSERÇÃO\n");
    Arvore = inserirElemento(Arvore, 18);
    printf("\n%d\n", Arvore->valor1); // 10
    printf("\n%d\n", Arvore->esquerda->valor1); //5
    printf("\n%d\n", Arvore->meio->valor1); //18
    printf("\n%d\n", Arvore->meio->esquerda->valor1); //15
    printf("\n%d\n", Arvore->meio->meio->valor1); //20
    Arvore = inserirElemento(Arvore, 16);
    
    printf("\n\nNOVA INSERçÃO\n");
    printf("\n%d\n", Arvore->valor1); // 10
    printf("\n%d\n", Arvore->esquerda->valor1); //5
    printf("\n%d\n", Arvore->meio->valor1); //18
    printf("\n%d\n", Arvore->meio->esquerda->valor1); //15
    printf("\n%d\n", Arvore->meio->esquerda->valor2); //16
    printf("\n%d\n", Arvore->meio->meio->valor1); //20
    return 0;
}
