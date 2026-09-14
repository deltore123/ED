#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tad.h"

#define MAX_LISTAS 100

int main() {

    char comando[20];
    char nome[20];

    Lista *listas[MAX_LISTAS];
    int quantidade_listas = 0;

    while (1) {

        scanf("%s", comando);

        if (strcmp(comando, "FIM") == 0) {
            break;
        }

        else if (strcmp(comando, "DEF") == 0) {
            int linhas;
            scanf("%s %d", nome, &linhas);

            int indice_alvo = insere_ou_substitui(listas, &quantidade_listas, nome[0], MAX_LISTAS);
            listas[indice_alvo] = cria_lista(nome[0]);

            for (int i = 0; i < linhas; i++) {
                long long coef, exp;
                scanf("%lld %lld", &coef, &exp);
                adiciona_elemento(listas[indice_alvo], coef, exp);
            }
        }

        else if (strcmp(comando, "SOMA") == 0){
            char nome[2], nome_2[2], nome_resultado[2];
            scanf("%s %s %s", nome, nome_2, nome_resultado);
            Lista *lista1= encontra_listas(listas, quantidade_listas, nome[0]);
            Lista *lista2 = encontra_listas(listas, quantidade_listas, nome_2[0]);
            if (lista1 == NULL || lista2 == NULL){
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            Lista *resultado = soma_listas(lista1, lista2, nome_resultado[0]);

            int indice_alvo = insere_ou_substitui(listas, &quantidade_listas, nome_resultado[0], MAX_LISTAS);
            listas[indice_alvo] = resultado;
        }
        else if (strcmp(comando, "ADD") == 0){
            char nome[2];
            long long coef, exp;
            scanf("%s %lld %lld", nome, &coef, &exp);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            adiciona_elemento(lista, coef, exp);
        }
        else if (strcmp(comando, "ESCALA") == 0){
            char nome[2];
            long long valor_escala;
            scanf("%s %lld", nome, &valor_escala);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            escala(lista, valor_escala);
        }
        else if (strcmp(comando, "COEF")==0){
            char nome_lista[2];
            long long coeficiente;
            scanf("%s %lld", nome_lista, &coeficiente);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome_lista[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            long long resultado = busca_coeficiente(lista, coeficiente);
            printf("%lld\n", resultado);
        }
        else if (strcmp(comando, "REMOVE")==0){
            long long grau;
            char nome[2];
            scanf("%s %lld", nome, &grau);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            remove_elemento(lista, grau);
            
        }
        else if (strcmp(comando, "REMOVEMENOR")==0){
            char nome[2];
            scanf("%s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            removemenor(lista);
        }
        else if (strcmp(comando, "GRAU")==0){
            char nome[2];
            scanf("%s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            printf("%lld\n", grau(lista));
        }
        else if (strcmp(comando, "IMPRIME")==0){
            char nome[2];
            scanf("%s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            imprime(lista);
            printf("\n");
        }
        else if (strcmp(comando, "IMPRIMEINV")==0){
            char nome[2];
            scanf("%s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            imprime_inv(lista);
            printf("\n");
        }
        else if (strcmp(comando, "LIBERA")==0){
            char nome[2];
            scanf("%s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            if (lista == NULL) {
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }
            // Anula o ponteiro no array antes de liberar
            for (int i = 0; i < quantidade_listas; i++) {
                if (listas[i] == lista) {
                    listas[i] = NULL;
                    break;
                }
            }
            libera(lista);
        } 

        else if(strcmp(comando, "PROD")==0){
            // Escaneando nomes das listas a serem multiplicadas
            char nome1[2], nome2[2], nome3[2];
            scanf("%s %s %s", nome1, nome2, nome3);

            // Encontrando listas, na lista de listas
            Lista *lista1 = encontra_listas(listas, quantidade_listas, nome1[0]);
            Lista *lista2 = encontra_listas(listas, quantidade_listas, nome2[0]);

            // Caso algumas delas não exista o programa não faz nada
            if( lista1 == NULL || lista2 == NULL){
                fprintf(stderr, "erro: polinomio nao definido\n");
                exit(2);
            }

            // Chamada da função e armazenamento do resultado
            Lista *resultado = prod(lista1, lista2, nome3[0]);

            int indice_alvo = insere_ou_substitui(listas, &quantidade_listas, nome3[0], MAX_LISTAS);
            listas[indice_alvo] = resultado;
        }
        else {
            exit(3);
        }
    }

    // Libera todas as listas restantes
    for (int i = 0; i < quantidade_listas; i++) {
        if (listas[i] != NULL) {
            libera(listas[i]);
        }
    }

    return 0;
}
