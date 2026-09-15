#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tad.h"

/* estrutura interna de um termo */
typedef struct Termo {
    long long coeficiente;
    long long expoente;
    struct Termo *proximo;
} Termo;

/* estrutura interna da lista */
struct Lista {
    Termo *inicio;
    char nome[33];
    int quantidade;
};

/* cria uma lista vazia */
Lista *cria_lista(char *chave) {

    Lista *lista = malloc(sizeof(Lista));

    if (lista == NULL) {
        return NULL;
    }

    lista->inicio = NULL;
    lista->quantidade = 0;

    strcpy(lista->nome, chave);

    return lista;
}

/* adiciona um termo mantendo a lista ordenada por expoente */
int adiciona_elemento(
    Lista *lista,
    long long coeficiente,
    long long expoente
) {

    Termo *novo;
    Termo *atual;
    Termo *anterior;

    /* coeficiente zero nao precisa ser armazenado */
    if (coeficiente == 0) {
        return 0;
    }

    novo = malloc(sizeof(Termo));

    if (novo == NULL) {
        return ERRO;
    }

    novo->coeficiente = coeficiente;
    novo->expoente = expoente;
    novo->proximo = NULL;

    atual = lista->inicio;
    anterior = NULL;

    /* procura a posicao correta */
    while (atual != NULL && atual->expoente > expoente) {
        anterior = atual;
        atual = atual->proximo;
    }

    /* expoente ja existe */
    if (atual != NULL && atual->expoente == expoente) {

        atual->coeficiente += coeficiente;

        free(novo);

        /* se o coeficiente ficou zero, remove o termo */
        if (atual->coeficiente == 0) {

            if (anterior == NULL) {
                lista->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            free(atual);
            lista->quantidade--;
        }

        return 0;
    }

    /* insere no inicio */
    if (anterior == NULL) {

        novo->proximo = lista->inicio;
        lista->inicio = novo;

    } else {

        novo->proximo = atual;
        anterior->proximo = novo;
    }

    lista->quantidade++;

    return 0;
}

/*
 * cria uma lista a partir dos termos informados pelo usuario.
 * a leitura fica dentro do TAD, portanto o main nao precisa
 * conhecer a estrutura Termo.
 */
Lista *cria_lista_def(char *nome, int quantidade) {

    Lista *lista;
    long long coeficiente;
    long long expoente;
    int i;

    lista = cria_lista(nome);

    if (lista == NULL) {
        return NULL;
    }

    for (i = 0; i < quantidade; i++) {

        scanf("%lld %lld", &coeficiente, &expoente);

        if (adiciona_elemento(
                lista,
                coeficiente,
                expoente
            ) == ERRO) {

            libera(lista);
            return NULL;
        }
    }

    return lista;
}

/* procura uma lista pelo nome */
Lista *encontra_listas(
    Lista **listas,
    int quantidade,
    char *nome
) {

    int i;

    for (i = 0; i < quantidade; i++) {

        if (listas[i] != NULL &&
            strcmp(listas[i]->nome, nome) == 0) {

            return listas[i];
        }
    }

    return NULL;
}

/* cria uma nova lista ou substitui uma existente */
int insere_ou_substitui(
    Lista **listas,
    int *quantidade,
    char *nome
) {

    int i;

    for (i = 0; i < *quantidade; i++) {

        if (listas[i] != NULL &&
            strcmp(listas[i]->nome, nome) == 0) {

            libera(listas[i]);

            listas[i] = cria_lista(nome);

            if (listas[i] == NULL) {
                return ERRO;
            }

            return i;
        }
    }

    listas[*quantidade] = cria_lista(nome);

    if (listas[*quantidade] == NULL) {
        return ERRO;
    }

    (*quantidade)++;

    return *quantidade - 1;
}

/* soma duas listas */
Lista *soma_listas(
    Lista *lista1,
    Lista *lista2,
    char *nome_resultado
) {

    Lista *resultado;
    Termo *a;
    Termo *b;

    resultado = cria_lista(nome_resultado);

    if (resultado == NULL) {
        return NULL;
    }

    a = lista1->inicio;
    b = lista2->inicio;

    while (a != NULL && b != NULL) {

        if (a->expoente > b->expoente) {

            adiciona_elemento(
                resultado,
                a->coeficiente,
                a->expoente
            );

            a = a->proximo;

        } else if (b->expoente > a->expoente) {

            adiciona_elemento(
                resultado,
                b->coeficiente,
                b->expoente
            );

            b = b->proximo;

        } else {

            adiciona_elemento(
                resultado,
                a->coeficiente + b->coeficiente,
                a->expoente
            );

            a = a->proximo;
            b = b->proximo;
        }
    }

    while (a != NULL) {

        adiciona_elemento(
            resultado,
            a->coeficiente,
            a->expoente
        );

        a = a->proximo;
    }

    while (b != NULL) {

        adiciona_elemento(
            resultado,
            b->coeficiente,
            b->expoente
        );

        b = b->proximo;
    }

    return resultado;
}

/* procura o coeficiente de um expoente */
long long busca_coeficiente(
    Lista *lista,
    long long expoente
) {

    Termo *atual = lista->inicio;

    while (atual != NULL &&
           atual->expoente >= expoente) {

        if (atual->expoente == expoente) {
            return atual->coeficiente;
        }

        atual = atual->proximo;
    }

    return 0;
}

/* remove um termo */
int remove_elemento(
    Lista *lista,
    long long grau
) {

    Termo *atual;
    Termo *anterior;

    atual = lista->inicio;
    anterior = NULL;

    while (atual != NULL &&
           atual->expoente > grau) {

        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL ||
        atual->expoente != grau) {

        return ERRO;
    }

    if (anterior == NULL) {
        lista->inicio = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);

    lista->quantidade--;

    return 0;
}

/* retorna o maior expoente */
long long grau(Lista *lista) {

    if (lista == NULL ||
        lista->inicio == NULL) {

        return 0;
    }

    return lista->inicio->expoente;
}

/* multiplica todos os coeficientes por um valor */
int escala(
    Lista *lista,
    long long escala
) {

    Termo *atual;
    Termo *anterior;
    Termo *proximo;

    atual = lista->inicio;
    anterior = NULL;

    while (atual != NULL) {

        atual->coeficiente *= escala;

        proximo = atual->proximo;

        /* remove termos que ficaram com coeficiente zero */
        if (atual->coeficiente == 0) {

            if (anterior == NULL) {
                lista->inicio = proximo;
            } else {
                anterior->proximo = proximo;
            }

            free(atual);
            lista->quantidade--;

        } else {

            anterior = atual;
        }

        atual = proximo;
    }

    return 0;
}

/* remove o termo de menor expoente */
int removemenor(Lista *lista) {

    Termo *atual;
    Termo *anterior;

    if (lista == NULL ||
        lista->inicio == NULL) {

        return ERRO;
    }

    atual = lista->inicio;
    anterior = NULL;

    while (atual->proximo != NULL) {

        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL) {
        lista->inicio = NULL;
    } else {
        anterior->proximo = NULL;
    }

    free(atual);

    lista->quantidade--;

    return 0;
}

/* multiplica duas listas */
Lista *prod(
    Lista *lista1,
    Lista *lista2,
    char *nome_resultado
) {

    Lista *resultado;
    Termo *a;
    Termo *b;

    resultado = cria_lista(nome_resultado);

    if (resultado == NULL) {
        return NULL;
    }

    a = lista1->inicio;

    while (a != NULL) {

        b = lista2->inicio;

        while (b != NULL) {

            adiciona_elemento(
                resultado,
                a->coeficiente * b->coeficiente,
                a->expoente + b->expoente
            );

            b = b->proximo;
        }

        a = a->proximo;
    }

    return resultado;
}

/* imprime a lista */
void imprime(Lista *lista) {

    Termo *atual = lista->inicio;
    int primeiro = 1;

    while (atual != NULL) {

        if (!primeiro && atual->coeficiente > 0) {
            printf("+");
        }

        printf("%lldx^%lld",
               atual->coeficiente,
               atual->expoente);

        primeiro = 0;
        atual = atual->proximo;
    }

    printf("\n");
}

/* imprime a lista na ordem inversa */
void imprime_inv(Lista *lista) {

    Termo *anterior = NULL;
    Termo *atual = lista->inicio;
    Termo *proximo;

    /* inverte a lista */
    while (atual != NULL) {

        proximo = atual->proximo;
        atual->proximo = anterior;
        anterior = atual;
        atual = proximo;
    }

    lista->inicio = anterior;

    imprime(lista);

    /* inverte novamente para recuperar a ordem original */
    anterior = NULL;
    atual = lista->inicio;

    while (atual != NULL) {

        proximo = atual->proximo;
        atual->proximo = anterior;
        anterior = atual;
        atual = proximo;
    }

    lista->inicio = anterior;
}

/* libera todos os termos e a lista */
void libera(Lista *lista) {

    Termo *atual;
    Termo *proximo;

    if (lista == NULL) {
        return;
    }

    atual = lista->inicio;

    while (atual != NULL) {

        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(lista);
}