#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"

#define MAX_LISTAS 512

typedef struct Termo{
    long long coeficiente;
    long long expoente;
    struct Termo *proximo;
} Termo;

typedef struct Lista {
    Termo *inicio;
    char nome[33];
    int quantidade;
} Lista;

int compara_termos(const void *a, const void *b)
{
    const TermoEntrada *t1 = a;
    const TermoEntrada *t2 = b;

    if (t1->expoente < t2->expoente)
        return 1;

    if (t1->expoente > t2->expoente)
        return -1;

    return 0;
}

Lista *cria_lista_def(char *nome, TermoEntrada termos[], int quantidade)
{
    Lista *lista = cria_lista(nome);

    if (lista == NULL)
        return NULL;

    qsort(termos, quantidade, sizeof(TermoEntrada), compara_termos);

    Termo *cauda = NULL;

    int i = 0;

    while (i < quantidade) {

        long long expoente = termos[i].expoente;
        long long coeficiente = 0;

        while (i < quantidade && termos[i].expoente == expoente) {
            coeficiente += termos[i].coeficiente;
            i++;
        }

        if (coeficiente == 0)
            continue;

        Termo *novo = malloc(sizeof(Termo));

        if (novo == NULL) {
            libera(lista);
            return NULL;
        }

        novo->coeficiente = coeficiente;
        novo->expoente = expoente;
        novo->proximo = NULL;

        if (lista->inicio == NULL) {
            lista->inicio = novo;
        } else {
            cauda->proximo = novo;
        }

        cauda = novo;
        lista->quantidade++;
    }

    return lista;
}


Lista *cria_lista(char *chave) {
    // Aloca espaço para a lista dinâmicamente
    Lista *lista = malloc(sizeof(Lista));

    // Verifica se espaço foi alocado corretamente
    if (lista == NULL) {
        return NULL;
    }
   
    strcpy(lista->nome, chave);
    lista->quantidade = 0;
    lista->inicio=NULL;
    return lista;
}

int adiciona_elemento(Lista *lista, long long coeficiente, long long expoente) {
    if (coeficiente == 0 || lista == NULL) {
        return ERRO;
    }

    /* Lista vazia ou novo termo vai antes do início */
    if (lista->inicio == NULL || expoente > lista->inicio->expoente) {
        Termo *novo = malloc(sizeof(Termo));
        if (novo == NULL) return ERRO;

        novo->coeficiente = coeficiente;
        novo->expoente = expoente;
        novo->proximo = lista->inicio;

        lista->inicio = novo;
        lista->quantidade++;
        return 0;
    }

    /* Expoente igual ao do primeiro termo */
    if (lista->inicio->expoente == expoente) {
        lista->inicio->coeficiente += coeficiente;
        if (lista->inicio->coeficiente == 0) {
            Termo *remover = lista->inicio;
            lista->inicio = remover->proximo;
            free(remover);
            lista->quantidade--;
        }
        return 0;
    }

    /* Passagem única: percorre até encontrar o expoente ou a posição correta */
    Termo *atual = lista->inicio;
    while (atual->proximo != NULL && atual->proximo->expoente > expoente) {
        atual = atual->proximo;
    }

    /* Encontrou expoente existente */
    if (atual->proximo != NULL && atual->proximo->expoente == expoente) {
        atual->proximo->coeficiente += coeficiente;
        if (atual->proximo->coeficiente == 0) {
            Termo *remover = atual->proximo;
            atual->proximo = remover->proximo;
            free(remover);
            lista->quantidade--;
        }
        return 0;
    }

    /* Insere novo termo na posição correta */
    Termo *novo = malloc(sizeof(Termo));
    if (novo == NULL) return ERRO;

    novo->coeficiente = coeficiente;
    novo->expoente = expoente;
    novo->proximo = atual->proximo;

    atual->proximo = novo;
    lista->quantidade++;
    return 0;
}

Lista *soma_listas(Lista *lista1, Lista *lista2, char *nome_resultado) {

    if (lista1 == NULL || lista2 == NULL) {
        return NULL;
    }

    Lista *resultado = cria_lista(nome_resultado);
    if (resultado == NULL) {
        return NULL;
    }

    Termo *termo1 = lista1->inicio;
    Termo *termo2 = lista2->inicio;
    Termo *cauda = NULL; /* ponteiro para o último termo inserido */

    while (termo1 != NULL && termo2 != NULL) {
        long long coef, exp;

        if (termo1->expoente == termo2->expoente) {
            coef = termo1->coeficiente + termo2->coeficiente;
            exp = termo1->expoente;
            termo1 = termo1->proximo;
            termo2 = termo2->proximo;
        } else if (termo1->expoente > termo2->expoente) {
            coef = termo1->coeficiente;
            exp = termo1->expoente;
            termo1 = termo1->proximo;
        } else {
            coef = termo2->coeficiente;
            exp = termo2->expoente;
            termo2 = termo2->proximo;
        }

        if (coef == 0) continue;

        Termo *novo = malloc(sizeof(Termo));
        if (novo == NULL) { libera(resultado); return NULL; }
        novo->coeficiente = coef;
        novo->expoente = exp;
        novo->proximo = NULL;

        if (cauda == NULL) {
            resultado->inicio = novo;
        } else {
            cauda->proximo = novo;
        }
        cauda = novo;
        resultado->quantidade++;
    }

    /* Copia os termos restantes da lista que ainda não terminou */
    Termo *restante = (termo1 != NULL) ? termo1 : termo2;
    while (restante != NULL) {
        Termo *novo = malloc(sizeof(Termo));
        if (novo == NULL) { libera(resultado); return NULL; }
        novo->coeficiente = restante->coeficiente;
        novo->expoente = restante->expoente;
        novo->proximo = NULL;

        if (cauda == NULL) {
            resultado->inicio = novo;
        } else {
            cauda->proximo = novo;
        }
        cauda = novo;
        resultado->quantidade++;
        restante = restante->proximo;
    }

    return resultado;
}

Lista *encontra_listas(Lista **lista, int quantidade, char *nome) {
    int i = 0;
    while (i < quantidade) {
        if (lista[i] != NULL && strcmp(lista[i]->nome, nome) == 0) {
            return lista[i];
        }
        i++;
    }
    return NULL;
}

int insere_ou_substitui(Lista *listas[], int *quantidade_listas, char *nome)
{
    // Procura se o nome já existe
    for (int i = 0; i < *quantidade_listas; i++) {
        if (listas[i] != NULL && strcmp(listas[i]->nome, nome) == 0) {
            libera(listas[i]);
            listas[i] = NULL;
            return i;
        }
    }

    // Procura uma posição vazia para reutilizar
    for (int i = 0; i < *quantidade_listas; i++) {
        if (listas[i] == NULL) {
            return i;
        }
    }

    // Não encontrou posição vazia
    if (*quantidade_listas >= MAX_LISTAS) {
        return -1;
    }

    // Usa uma nova posição
    int indice = *quantidade_listas;
    (*quantidade_listas)++;

    return indice;
}

long long busca_coeficiente(Lista *lista, long long expoente) {
    if (lista == NULL) {
        return 0;
    }

    Termo *atual = lista->inicio;

    while (atual != NULL && atual->expoente >= expoente) {
        if (atual->expoente == expoente) {
            return atual->coeficiente;
        }
        atual = atual->proximo;
    }

    return 0;
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

    Termo *remover = atual->proximo;

    atual->proximo = NULL;

    free(remover);

    lista->quantidade--;

    return 0;
}

long long int grau(Lista *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        return ERRO;
    }

    return lista->inicio->expoente;
}

int escala (Lista *lista, long long int escala){
    if (lista==NULL){
        return ERRO;
    }
    Termo *atual = lista->inicio;

    if (atual == NULL){
        return ERRO;
    }
    if (escala == 0 && atual != NULL){
        Termo *remove = lista->inicio;
        atual = atual->proximo;
        while (atual!=NULL){
            free (remove);
            remove = atual;
            atual=atual->proximo;
        }
        free(remove);
        lista->inicio= NULL;
        lista->quantidade= 0;
        return 0;
    }
    while (atual!=NULL){
        atual->coeficiente = atual->coeficiente*escala;
        atual = atual->proximo;
    }

    return 0;
}

void imprime(Lista *lista){
    if (lista == NULL || lista->inicio == NULL) {
        printf("0");
        return;
    }
    Termo *atual = lista->inicio;
    while (atual != NULL) {
        printf("%lld*x^%lld", atual->coeficiente, atual->expoente);
        atual = atual->proximo;
        if (atual != NULL) {
            printf(" ");
        }
    }
}

void imprime_inv(Lista *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        printf("0");
        return;
    }

    /* Inverte a lista in-place (O(1) de espaco extra) */
    Termo *anterior = NULL;
    Termo *atual = lista->inicio;
    while (atual != NULL) {
        Termo *proximo = atual->proximo;
        atual->proximo = anterior;
        anterior = atual;
        atual = proximo;
    }
    lista->inicio = anterior; /* agora em ordem crescente de grau */

    Termo *no = lista->inicio;
    while (no != NULL) {
        printf("%lld*x^%lld", no->coeficiente, no->expoente);
        if (no->proximo != NULL) printf(" ");
        no = no->proximo;
    }

    /* Desfaz a inversao para manter a lista em ordem decrescente */
    anterior = NULL;
    atual = lista->inicio;
    while (atual != NULL) {
        Termo *proximo = atual->proximo;
        atual->proximo = anterior;
        anterior = atual;
        atual = proximo;
    }
    lista->inicio = anterior;
}
// Retorna ponteiro para nova lista resultante da multiplicação das outras duas
Lista *prod(Lista *lista1, Lista *lista2, char *nome_resultado){
    if (lista1 == NULL || lista2 == NULL) {
        return NULL;
    }

    Lista *resultado = cria_lista(nome_resultado);
    if (resultado == NULL) {
        return NULL;
    }

    Termo *t1 = lista1->inicio;
    while(t1 != NULL){
        // Cria uma lista temporária para guardar t1 multiplicado por todo lista2
        Lista *temp = cria_lista("temp");
        
        Termo *t2 = lista2->inicio;
        while (t2 != NULL) {
            long long expoente = t1->expoente + t2->expoente;
            long long coeficiente = t1->coeficiente * t2->coeficiente;
            
            adiciona_elemento(temp, coeficiente, expoente);
            t2 = t2->proximo;
        }

        // Soma a lista temp ao nosso resultado acumulado e salva em nova variável
        Lista *novo_resultado = soma_listas(resultado, temp, nome_resultado);
        
        // Destrói as listas velhas para liberar a memória
        libera(resultado);
        libera(temp);
        
        // Atualiza o ponteiro do resultado
        resultado = novo_resultado;
        
        t1 = t1->proximo;
    }

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
