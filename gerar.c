#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gerar.h"

void gerar_grafo(int tamanho, int chanceAresta, int pesoMax) {
    FILE *arestas = fopen("dados/arestas.csv", "w");
    FILE *vertices = fopen("dados/vertices.txt", "w");

    fflush(stdout);
    if (arestas == NULL || vertices == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    fprintf(arestas, "origem,destino,peso\n");
    fprintf(vertices, "%d\n", tamanho);

    srand(time(NULL));

    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (i == j) continue;

            if (rand() % 101 <= chanceAresta) {
                int peso = rand() % pesoMax + 1;
                fprintf(arestas, "%d,%d,%d\n", i, j, peso);
            }
        }
    }

    fclose(arestas);
    fclose(vertices);
}