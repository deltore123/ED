#ifndef TAD_H
#define TAD_H

#define ERRO -1

typedef struct Lista Lista;

// Obs: As funcionalidades da função Fim ja foram implementadas diretamente na main, por ela isso não está declarada aqui

// Função DEF: Usada para criar uma lista e definir seu nome
Lista *cria_lista(char chave); 

// Função ADD: Adiciona um elemento à Lista 
int adiciona_elemento(Lista *lista,long long coeficiente,long long expoente); 

// Função SOMA: Soma duas Listas
Lista *soma_listas(Lista *lista1, Lista *lista2, char nome_resultado);

// Função Auxiliar que busca o ponteiro para a lista baseado no seu nome em uma lista de listas ( dai a dupla dereferenciação)
Lista *encontra_listas (Lista **lista, int quantidade, char nome);

// Função COEF: Dado um exponete, retorna o coeficiente associado a ele 
int busca_coeficiente (Lista *lista, int expoente);

//  Função REMOVE: Remove o elemento de grau x da lista fornecida
int remove_elemento(Lista *lista, long long grau);

// Função GRAU: Retorna o maior expoente da lista
long long int grau (Lista *lista);

// Função ESCALA: Multiplica todos os coeficientes da lista por um escalar
int escala (Lista *lista, long long int escala);

// Função REMOVEMENOR : Remove o termo de menor expoente da lista
int removemenor(Lista *lista);

// Função PROD: Realiza a multiplicação de dois polinômios
Lista *prod(Lista *lista1, Lista *lista2, char nome_resultado);

// Função IMPRIME: Imprime o polinômio formatado corretamente
void imprime(Lista *lista);

// Função IMPRIMEINV: Imprime o polinômio invertido
void imprime_inv(Lista *lista);

// Função LIBERA: Devolve a memória utilizada pela lista
void libera(Lista *lista);



#endif

