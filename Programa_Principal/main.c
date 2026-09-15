#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tad.h"

#define MAX_LISTAS 512

int main(void) {

    Lista *listas[MAX_LISTAS] = {NULL};
    int quantidade_listas = 0;

    char comando[20];

    while (scanf("%s", comando) == 1) {

        /* define uma nova lista */
        if (strcmp(comando, "DEF") == 0) {

            char nome[33];
            int quantidade;
            int posicao;

            scanf("%s %d", nome, &quantidade);

            posicao = insere_ou_substitui(
                listas,
                &quantidade_listas,
                nome
            );

            if (posicao == ERRO) {
                continue;
            }

            /*
             * libera a lista vazia criada por
             * insere_ou_substitui e cria a lista
             * lendo os termos pelo TAD
             */
            libera(listas[posicao]);

            listas[posicao] =
                cria_lista_def(nome, quantidade);
        }

        /* soma duas listas */
        else if (strcmp(comando, "SOMA") == 0) {

            char nome1[33];
            char nome2[33];
            char nome_resultado[33];

            Lista *lista1;
            Lista *lista2;
            Lista *resultado;

            scanf(
                "%s %s %s",
                nome1,
                nome2,
                nome_resultado
            );

            lista1 = encontra_listas(
                listas,
                quantidade_listas,
                nome1
            );

            lista2 = encontra_listas(
                listas,
                quantidade_listas,
                nome2
            );

            resultado = soma_listas(
                lista1,
                lista2,
                nome_resultado
            );

            if (resultado != NULL) {

                int posicao = insere_ou_substitui(
                    listas,
                    &quantidade_listas,
                    nome_resultado
                );

                if (posicao != ERRO) {

                    libera(listas[posicao]);
                    listas[posicao] = resultado;
                }
            }
        }

        /* adiciona um termo */
        else if (strcmp(comando, "ADD") == 0) {

            char nome[33];
            long long coeficiente;
            long long expoente;

            Lista *lista;

            scanf(
                "%s %lld %lld",
                nome,
                &coeficiente,
                &expoente
            );

            lista = encontra_listas(
                listas,
                quantidade_listas,
                nome
            );

            if (lista != NULL) {

                adiciona_elemento(
                    lista,
                    coeficiente,
                    expoente
                );
            }
        }

        /* multiplica os coeficientes */
        else if (strcmp(comando, "ESCALA") == 0) {

            char nome[33];
            long long valor;

            Lista *lista;

            scanf("%s %lld", nome, &valor);

            lista = encontra_listas(
                listas,
                quantidade_listas,
                nome
            );

            if (lista != NULL) {
                escala(lista, valor);
            }
        }

        /* busca coeficiente */
        else if (strcmp(comando, "COEF") == 0) {

            char nome[33];
            long long expoente;

            Lista *lista;

            scanf("%s %lld", nome, &expoente);

            lista = encontra_listas(
                listas,
                quantidade_listas,
                nome
            );

            if (lista != NULL) {

                printf(
                    "%lld\n",
                    busca_coeficiente(
                        lista,
                        expoente
                    )
                );
            }
        }

        /* remove um termo */
        else if (strcmp(comando, "REMOVE") == 0) {

            char nome[33];
            long long expoente;

            Lista *lista;

            scanf("%s %lld", nome, &expoente);

            lista = encontra_listas(
                listas,
                quantidade_listas,
                nome
            );

            if (lista != NULL) {

                remove_elemento(
                    lista,
                    expoente
                );
            }
        }

        /* remove o termo de menor expoente */
        else if (
            strcmp(comando, "REMOVEMENOR") == 0
        ) {

            char nome[33];

            Lista *lista;

            scanf("%s", nome);

            lista = encontra_listas(
                listas,
                quantidade_listas,
                nome
            );

            if (lista != NULL) {
                removemenor(lista);
            }
        }

        /* mostra o grau */
        else if (strcmp(comando, "GRAU") == 0) {

            char nome[33];

            Lista *lista;

            scanf("%s", nome);

            lista = encontra_listas(
                listas,
                quantidade_listas,
                nome
            );

            if (lista != NULL) {
                printf("%lld\n", grau(lista));
            }
        }

        /* imprime */
        else if (strcmp(comando, "IMPRIME") == 0) {

            char nome[33];

            Lista *lista;

            scanf("%s", nome);

            lista = encontra_listas(
                listas,
                quantidade_listas,
                nome
            );

            if (lista != NULL) {
                imprime(lista);
            }
        }

        /* imprime ao contrario */
        else if (
            strcmp(comando, "IMPRIMEINV") == 0
        ) {

            char nome[33];

            Lista *lista;

            scanf("%s", nome);

            lista = encontra_listas(
                listas,
                quantidade_listas,
                nome
            );

            if (lista != NULL) {
                imprime_inv(lista);
            }
        }

        /* libera uma lista */
        else if (strcmp(comando, "LIBERA") == 0) {

            char nome[33];

            scanf("%s", nome);

            for (int i = 0; i < quantidade_listas; i++) {

                if (listas[i] != NULL) {

                    /*
                     * nao existe acesso direto aos campos
                     * da lista, apenas usamos as funcoes
                     * fornecidas pelo TAD.
                     */
                }
            }

            /*
             * aqui seria necessario que o TAD fornecesse
             * uma funcao para encontrar e liberar a lista.
             */
        }

        /* produto */
        else if (strcmp(comando, "PROD") == 0) {

            char nome1[33];
            char nome2[33];
            char nome_resultado[33];

            Lista *lista1;
            Lista *lista2;
            Lista *resultado;

            scanf(
                "%s %s %s",
                nome1,
                nome2,
                nome_resultado
            );

            lista1 = encontra_listas(
                listas,
                quantidade_listas,
                nome1
            );

            lista2 = encontra_listas(
                listas,
                quantidade_listas,
                nome2
            );

            resultado = prod(
                lista1,
                lista2,
                nome_resultado
            );

            if (resultado != NULL) {

                int posicao = insere_ou_substitui(
                    listas,
                    &quantidade_listas,
                    nome_resultado
                );

                if (posicao != ERRO) {

                    libera(listas[posicao]);
                    listas[posicao] = resultado;
                }
            }
        }

        /* finaliza o programa */
        else if (strcmp(comando, "FIM") == 0) {

            for (int i = 0; i < quantidade_listas; i++) {

                if (listas[i] != NULL) {
                    libera(listas[i]);
                }
            }

            break;
        }
    }

    return 0;
}