#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tad.h"

#define MAX_LISTAS 512

int main() {

    char comando[20];
    char nome[33];

    Lista *listas[MAX_LISTAS] = {NULL};
    int quantidade_listas = 0;

    while (1) {

        if (scanf("%19s", comando) != 1) {
            break; // entrada acabou sem "FIM" -- evita loop infinito
        }

        if (strcmp(comando, "FIM") == 0) {
            break;
        }

        else if (strcmp(comando, "DEF") == 0) {
            int linhas;
            scanf("%32s %d", nome, &linhas);

            // DEF
            int indice_alvo = insere_ou_substitui(listas, &quantidade_listas, nome);
            if (indice_alvo == -1) {
            for (int i = 0; i < linhas; i++) {
                long long coef, exp;
                scanf("%lld %lld", &coef, &exp); // consome a entrada mesmo descartando
            }
                continue;
            }
            listas[indice_alvo] = cria_lista(nome);

            for (int i = 0; i < linhas; i++) {
                long long coef, exp;
                scanf("%lld %lld", &coef, &exp);
                adiciona_elemento(listas[indice_alvo], coef, exp);
            }
        }

        else if (strcmp(comando, "SOMA") == 0){
            char nome[33], nome_2[33], nome_resultado[33];
            scanf("%32s %32s %32s", nome, nome_2, nome_resultado);
            Lista *lista1= encontra_listas(listas, quantidade_listas, nome);
            Lista *lista2 = encontra_listas(listas, quantidade_listas, nome_2);
            if (lista1 == NULL || lista2 == NULL){
                continue;
            }
            // SOMA
            Lista *resultado = soma_listas(lista1, lista2, nome_resultado);
            int indice_alvo = insere_ou_substitui(listas, &quantidade_listas, nome_resultado);
            if (indice_alvo == -1) { libera(resultado); continue; }
                listas[indice_alvo] = resultado;
            }
        else if (strcmp(comando, "ADD") == 0){
            char nome[33];
            long long coef, exp;
            scanf("%32s %lld %lld", nome, &coef, &exp);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome);
            if (lista == NULL) {
                continue;
            }
            adiciona_elemento(lista, coef, exp);
        }
        else if (strcmp(comando, "ESCALA") == 0){
            char nome[33];
            long long valor_escala;
            scanf("%32s %lld", nome, &valor_escala);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome);
            if (lista == NULL) {
                continue;
            }
            escala(lista, valor_escala);
        }
        else if (strcmp(comando, "COEF")==0){
            char nome_lista[33];
            long long coeficiente;
            scanf("%32s %lld", nome_lista, &coeficiente);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome_lista);
            if (lista == NULL) {
                continue;
            }
            long long resultado = busca_coeficiente(lista, coeficiente);
            printf("%lld\n", resultado);
        }
        else if (strcmp(comando, "REMOVE")==0){
            long long grau;
            char nome[33];
            scanf("%32s %lld", nome, &grau);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome);
            if (lista == NULL) {
                continue;
            }
            remove_elemento(lista, grau);
            
        }
        else if (strcmp(comando, "REMOVEMENOR")==0){
            char nome[33];
            scanf("%32s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome);
            if (lista == NULL) {
                continue;
            }
            removemenor(lista);
        }
        else if (strcmp(comando, "GRAU")==0){
            char nome[33];
            scanf("%32s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome);
            if (lista == NULL) {
                continue;
            }
            printf("%lld\n", grau(lista));
        }
        else if (strcmp(comando, "IMPRIME")==0){
            char nome[33];
            scanf("%32s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome);
            if (lista == NULL) {
                continue;
            }
            imprime(lista);
            printf("\n");
        }
        else if (strcmp(comando, "IMPRIMEINV")==0){
            char nome[33];
            scanf("%32s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome);
            if (lista == NULL) {
                continue;
            }
            imprime_inv(lista);
            printf("\n");
        }
        else if (strcmp(comando, "LIBERA")==0){
            char nome[33];
            scanf("%32s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome);
            if (lista == NULL) {
                continue;
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
            char nome1[33], nome2[33], nome3[33];
            scanf("%32s %32s %32s", nome1, nome2, nome3);

            // Encontrando listas, na lista de listas
            Lista *lista1 = encontra_listas(listas, quantidade_listas, nome1);
            Lista *lista2 = encontra_listas(listas, quantidade_listas, nome2);

            // Caso algumas delas não exista o programa não faz nada
            if( lista1 == NULL || lista2 == NULL){
                continue;
            }

            // Chamada da função e armazenamento do resultado
            // PROD
            Lista *resultado = prod(lista1, lista2, nome3);
            int indice_alvo = insere_ou_substitui(listas, &quantidade_listas, nome3);
            if (indice_alvo == -1) { 
                libera(resultado); continue; 
            }
             listas[indice_alvo] = resultado;
        }
        else {
            continue;
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