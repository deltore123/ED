#ifndef TAD_H
#define TAD_H

#define ERRO -1
#define MAX_LISTAS 512

typedef struct Lista Lista;

/* cria uma lista vazia com o nome informado */
Lista *cria_lista(char *chave);

/* adiciona um termo mantendo a lista ordenada */
int adiciona_elemento(
    Lista *lista,
    long long coeficiente,
    long long expoente
);

/* le os termos de um DEF e cria a lista */
Lista *cria_lista_def(char *nome, int quantidade);

/* soma duas listas */
Lista *soma_listas(
    Lista *lista1,
    Lista *lista2,
    char *nome_resultado
);

/* procura uma lista pelo nome */
Lista *encontra_listas(
    Lista **listas,
    int quantidade,
    char *nome
);

/* reserva (ou libera e reserva) uma posicao para uma lista com o nome dado */
int insere_ou_substitui(
    Lista **listas,
    int *quantidade,
    char *nome
);

/* procura o coeficiente de um determinado expoente */
long long busca_coeficiente(
    Lista *lista,
    long long expoente
);

/* remove um termo */
int remove_elemento(
    Lista *lista,
    long long grau
);

/* retorna o maior expoente da lista */
long long grau(Lista *lista);

/* multiplica todos os coeficientes por um valor */
int escala(
    Lista *lista,
    long long escala
);

/* remove o termo de menor expoente */
int removemenor(Lista *lista);

/* multiplica duas listas */
Lista *prod(
    Lista *lista1,
    Lista *lista2,
    char *nome_resultado
);

/* imprime a lista */
void imprime(Lista *lista);

/* imprime a lista na ordem inversa */
void imprime_inv(Lista *lista);

/* libera a lista */
void libera(Lista *lista);

#endif
