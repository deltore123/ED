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

    
    Termo *atual = lista->inicio;

    if (atual == NULL){
        return ERRO;
    }


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
    while(i < quantidade && lista[i]->nome != nome){
        i++;
    }
    if (i == quantidade) {
        return NULL;
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

int remove_elemento(Lista *lista, long long grau) {

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

    atual->proximo = NULL;

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

void imprime(Lista *lista){
    // Define o primeiro termo como o primeiro da lista
    Termo *atual = lista->inicio;
    // Itera sobre todos os termos
    for(int i =0; i<lista->quantidade; i++){
        // Imprime coeficiente, "X" e o expoente nessa ordem
        printf("%lld", atual->coeficiente);
        printf("X");
        printf("%lld", atual->expoente);
        // Passa para o próximo termo
        atual = atual->proximo;
    }
}

// Termo atual é o primeiro termo da lista
void imprime_inv_recursiva(Termo *atual) {
    // Caso Base ( se for nulo passou do fim da lista)
    if ( atual == NULL){
        return; 
    }

    // Faz chamada recursiva para impirmir o próximo
    imprime_inv_recursiva(atual->proximo); 

    // Agora que já imprimiu o próximo imprime o atual
    printf("%lld*x^%lld ", atual->coeficiente, atual->expoente); 
    
    return;
}

void imprime_inv(Lista *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("0");
        return;
    }
    imprime_inv_recursiva(lista->inicio);
}

int compara_string (char string1[], char string2[]){
    int i=0;
    while (string1[i] != '\0' && string2[i] != '\0'){
        if (string1[i] != string2[i]){
            return 1;
        }
        i++;
    }
    if (string1[i] != string2[i]){
            return 1;
        }
    return 0;
}

// Retorna ponteiro para nova lista resultante da multiplicação das outras duas
Lista *prod(Lista *lista1, Lista *lista2, char nome_resultado){
    // Verifica se alguma das listas é nula
     if (lista1 == NULL || lista2 == NULL) {
        return NULL;
    }

    // Cria a lista que conterá resultado da multiplicação
    Lista *resultado = cria_lista(nome_resultado);
    
    // Verifica se lista foi criada com sucesso
    if (resultado == NULL) {
        return NULL;
    }

    // Duas iterações aninhadas para fazer a multiplicação de todos os elementos
    Termo *t1 = lista1->inicio;
    while(t1!= NULL){
        Termo *t2 = lista2->inicio;
        while (t2!=NULL){
            // Calcula expoente e coeficiente do termo resultante da multiplicação
            long long expoente = t1->expoente + t2->expoente;
            long long coeficiente = t1->coeficiente * t2->coeficiente;
            // Usa função adiciona elemento para adicionar na lista de resultad
            // Essa função já vai fazer a organização dos elementos automaticamente
            adiciona_elemento(resultado, coeficiente, expoente);  
            
            // Muda t2 para o próximo termo
            t2 = t2->proximo;
        }
        
        // Muda t1 para próximo termo 
        t1 = t1->proximo;
    }

    // Função retorna o ponteiro da nova lista
    return resultado;


}

void libera(Lista *lista){
    if (lista == NULL) {
        return;
    }

    Termo *atual = lista->inicio;

    while (atual != NULL) {
        Termo *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(lista);
}