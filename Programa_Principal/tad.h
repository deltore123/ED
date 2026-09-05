#ifndef TAD_H
#define TAD_H

#define ERRO -1

typedef struct Lista Lista;

// Função DEF: Usada para criar uma lista e definir seu nome
Lista *cria_lista(char chave); 

// Função ADD: Adiciona um elemento à Lista 
int adiciona_elemento(Lista *lista,long long coeficiente,long long expoente); 

// Função SOMA: Soma duas Listas
Lista *soma_listas(Lista *lista1, Lista *lista2, char nome_resultado);

Lista *encontra_listas (Lista **lista, int quantidade, char nome);

// Função COEF: Dado um exponete, retorna o coeficiente associado a ele 
int busca_coeficiente (Lista *lista, int expoente);

//  Função REMOVE: Remove o elemento de grau x da lista fornecida
int remove_elemento(Lista *lista, long long grau);

long long int grau (Lista *lista);

int escala (Lista *lista, long long int escala);

#endif

