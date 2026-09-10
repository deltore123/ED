/*Esse arquivo será responsável por gerar os casos de teste do programa principal*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_polinomio(char nome){
    printf("DEF %c 50000\n", nome);
    int max_grau = 500000;
    int num_termos = 50000;

    int *graus = (int *)malloc((max_grau + 1) * sizeof(int));
    for (int i = 0; i <= max_grau; i++) {
        graus[i] = i;
    }
    

    // Lógica para sortear 50.000 graus únicos entre 0 e 500000
    for(int i = 0; i < num_termos; i++){
        long long r = rand();
        r = (r << 15) | (rand());
        int j = i + (r % (max_grau - i + 1));
        int temp = graus [i];
        graus [i] = graus[j];
        graus [j] = temp;


        // Lógica para sortear coeficientes entre -1000 e 1000
        int coef;
        do {
            coef = (rand() % 2001) - 1000;
        } while (coef == 0);

        // Para cada termo: printf("%d %d\n", coef, grau);
        printf("%d %d\n", coef, graus[i]);
    }

    // Libera a memória do vetor auxiliar
    free(graus);

    // Gerar os comandos de escala
    for(int i=0; i<20000;i++){
        int c = (rand() % 1000) + 1;
        printf("ESCALA %c %d\n",nome,c);
    }
}

int main() {
    // Inicializa a semente para a geração de números aleatórios
    srand(time(NULL));
    
    // Gera o polinômio A e seus comandos de inspeção
    gera_polinomio('A');
    printf("IMPRIME A\n");
    printf("GRAU A\n");
    
    // Gera o polinômio B e o comando de soma
    gera_polinomio('B');
    printf("SOMA A B R\n");
    
    printf("FIM\n");
    return 0;
}