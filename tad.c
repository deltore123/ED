#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

#define ERRO -1
#define BOOLEANO int

typedef struct Termo{
    long long coeficiente;
    long long expoente;
    struct Termo *proximo;
} Termo;

typedef struct Lista {
    Termo *inicio;
    char nome;
    int quantidade;
} Lista;



Lista *cria_lista(char chave) {
    Lista *lista = malloc(sizeof(Lista));

    if (lista == NULL) {
        return NULL;
    }
 
    lista->nome = chave;
    lista->quantidade = 0;
    lista->inicio=NULL;
    return lista;
}

int adiciona_elemento (Lista *lista, long long coeficiente, long long expoente){
    if (lista == NULL){
        return ERRO;
    }
    Termo *novo = malloc(sizeof(Termo));
    if (novo == NULL){
        return ERRO;
    }

    if (lista->inicio == NULL){
        novo->coeficiente = coeficiente;
        novo->expoente = expoente;
        novo->proximo = NULL;
        lista->inicio = novo;
        lista->quantidade++;
        return 0;
    }

    if (expoente > lista->inicio->expoente) {
        novo->proximo = lista->inicio;
        lista->inicio = novo;
        lista->quantidade++;
        return 0;
    }

    if (atual == NULL){
        return ERRO;
    }

    Termo *atual = lista->inicio;

    while (atual->proximo != NULL && atual->proximo->expoente > expoente){
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    atual->proximo = novo;  

    lista->quantidade++;

    return 0;

}

Lista *soma_listas(Lista *lista1, Lista *lista2, char nome_resultado) {

    if (lista1 == NULL || lista2 == NULL) {
        return NULL;
    }

    Lista *resultado = cria_lista(nome_resultado);
    resultado->nome = nome_resultado;
    if (resultado == NULL) {
        return NULL;
    }

    Termo *termo1 = lista1->inicio;
    Termo *termo2 = lista2->inicio;

    while (termo1 != NULL && termo2 != NULL) {

        if (termo1->expoente == termo2->expoente) {

            long long coeficiente =
                termo1->coeficiente + termo2->coeficiente;

            if (coeficiente != 0) {
                adiciona_elemento(
                    resultado,
                    coeficiente,
                    termo1->expoente
                );
            }

            termo1 = termo1->proximo;
            termo2 = termo2->proximo;
        }

        else if (termo1->expoente > termo2->expoente) {

            adiciona_elemento(
                resultado,
                termo1->coeficiente,
                termo1->expoente
            );

            termo1 = termo1->proximo;
        }

        else {

            adiciona_elemento(
                resultado,
                termo2->coeficiente,
                termo2->expoente
            );

            termo2 = termo2->proximo;
        }
    }

    while (termo1 != NULL) {

        adiciona_elemento(
            resultado,
            termo1->coeficiente,
            termo1->expoente
        );

        termo1 = termo1->proximo;
    }


    while (termo2 != NULL) {

        adiciona_elemento(
            resultado,
            termo2->coeficiente,
            termo2->expoente
        );

        termo2 = termo2->proximo;
    }

    return resultado;
}

Lista *encontra_listas (Lista **lista, int quantidade, char nome){
    int i=0;
    while(lista[0]->nome != nome && i<quantidade){
        i++;
    }
    return lista[i];
}

int busca_coeficiente (Lista *lista, int expoente){
    Termo *atual = lista->inicio;
    for (int i=0; i<lista->quantidade; i++){
        if (atual->expoente != expoente){
            atual = atual->proximo;
        }

        if (atual->expoente == expoente) {
            return atual->coeficiente;
        }

    }
    return ERRO;

}

int remove(Lista *lista, long long grau) {

    if (lista == NULL || lista->inicio == NULL) {
        return ERRO;
    }

    if (lista->inicio->expoente == grau) {

        Termo *remover = lista->inicio;

        lista->inicio = lista->inicio->proximo;

        free(remover);

        lista->quantidade--;

        return 0;
    }

    Termo *atual = lista->inicio;

    while (atual->proximo != NULL &&
           atual->proximo->expoente != grau) {

        atual = atual->proximo;
    }

    if (atual->proximo == NULL) {
        return ERRO;
    }

    Termo *remover = atual->proximo;

    atual->proximo = remover->proximo;

    free(remover);

    lista->quantidade--;

    return 0;
}

int removemenor(Lista *lista) {

    if (lista == NULL || lista->inicio == NULL) {
        return ERRO;
    }

    if (lista->inicio->proximo == NULL) {

        Termo *remover = lista->inicio;

        free (remover);

        lista->inicio= NULL;

        lista->quantidade--;

        return 0;
    }

    Termo *atual = lista->inicio;

    while (atual->proximo->proximo != NULL) {

        atual = atual->proximo;
    }

    if (atual->proximo == NULL) {
        return ERRO;
    }

    Termo *remover = atual->proximo;

    atual->proximo = NULL

    free(remover);



    lista->quantidade--;

    return 0;
}

long long int grau (Lista *lista){
    Termo *inicio = lista->inicio;
    return inicio->expoente;
}

int escala (Lista *lista, long long int escala){
    if (lista==NULL){
        return ERRO;
    }
    Termo *atual = lista->inicio;

    if (atual == NULL){
        return ERRO;
    }

    while (atual!=NULL){
        atual->coeficiente = atual->coeficiente*escala;
    }

    return 0;
}