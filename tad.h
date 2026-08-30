#ifndef TAD_H
#define TAD_H

#define ERRO -1

typedef struct Lista lista;

Lista *cria_lista(char chave);

int adiciona_elemento(Lista *lista,
                       long long coeficiente,
                       long long expoente);

Lista *soma_listas(Lista *lista1, Lista *lista2, char nome_resultado);

Lista *encontra_listas (Lista **lista, int quantidade, char nome);

int busca_coeficiente (Lista *lista, int expoente);

int remove(Lista *lista, long long grau);

long long int grau (Lista *lista);

int escala (Lista *lista, long long int escala);

#endif

