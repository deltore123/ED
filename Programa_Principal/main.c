#include <stdio.h>
#include <string.h>
#include "tad.h"

#define MAX_LISTAS 100

int main() {

    char comando[20];
    char nome[20];

    int expoente;
    int coeficiente;

    Lista *listas[MAX_LISTAS];
    int quantidade_listas = 0;

    while (1) {

        scanf("%s", comando);

        if (compara_string(comando, "FIM") == 0) {
            break;
        }

        if (compara_string(comando, "DEF") == 0) {

            int linhas;

            scanf("%s %d", nome, &linhas);

            listas[quantidade_listas] = cria_lista(nome[0]);

            for (int i = 0; i < linhas; i++) {

                scanf("%d %d", &coeficiente, &expoente);

                adiciona_elemento(
                    listas[quantidade_listas],
                    coeficiente,
                    expoente
                );
            }

            quantidade_listas++;
        }

        if (compara_string(comando, "SOMA") == 0){
            char nome[2], nome_2[2], nome_resultado[2];
            scanf("%s %s %s", nome, nome_2, nome_resultado);
            Lista *lista1= encontra_listas(listas, quantidade_listas, nome[0]);
            Lista *lista2 = encontra_listas(listas, quantidade_listas, nome_2[0]);
            if (lista1 == NULL || lista2 == NULL){
                printf("alguma das listas nao existe\n");
                continue;
            }
            Lista *resultado = soma_listas(lista1, lista2, nome_resultado[0]);
            listas[quantidade_listas] = resultado;
            quantidade_listas++;
        }
        if (compara_string(comando, "COEF")==0){
            char nome_lista[2];
            long long coeficiente;
            scanf("%s %lld", nome_lista, &coeficiente);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome_lista[0]);
            long long resultado = busca_coeficiente(lista, coeficiente);
            printf("%lld\n", resultado);
        }
        if (compara_string(comando, "REMOVE")==0){
            int grau;
            char nome[2];
            scanf("%s %d", nome, &grau);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            int flag = remove_elemento(lista, grau);
            if (flag == -1){
                printf("ERRO\n");
            }
        }
        if (compara_string(comando, "REMOVEMENOR")==0){
            char nome[2];
            scanf("%s", nome);
            Lista *lista = encontra_listas(listas, quantidade_listas, nome[0]);
            
        }
    }

    return 0;
}