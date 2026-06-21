#include "grafo.h"
#include "db.h"
#include "dijkstra.h"
#include "gerar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void preencher_form() {
    int tamanho = -1;
    int pesoMax = -1;
    int chanceAresta = -1;
    while (tamanho < 1) {
        printf("Digite o numero de salas: ");
        scanf("%d", &tamanho);
        if (tamanho < 1) {
            printf("Valor invalido, tente novamente.\n");
        }
    }
    while (pesoMax < 0) {
        printf("Digite a distancia maxima: ");
        scanf("%d", &pesoMax);
        if (pesoMax < 0) {
            printf("Valor invalido, tente novamente.\n");
        }
    }
    while (chanceAresta < 1 || chanceAresta > 100) {
        printf("Digite a chance (em %%) de passagem (1 a 100): ");
        scanf("%d", &chanceAresta);

        if (chanceAresta < 1 || chanceAresta > 100) {
            printf("Valor invalido, tente novamente.\n");
        }
    }

    gerar_grafo(tamanho, chanceAresta, pesoMax);
}

int main() {
    FILE *arestas = fopen("dados/arestas.csv", "r");
    FILE *vertices = fopen("dados/vertices.txt", "r");

    if (arestas == NULL || vertices == NULL) {
        preencher_form();
    } else {
        char resposta[20];
        while (resposta[0] != 'S' && resposta[0] != 'N' && resposta[0] != 's' && resposta[0] != 'n') {
            printf("Gerar novo grafo? [S/N]: ");
            fgets(resposta, 20, stdin);
            if (resposta[0] != 'S' && resposta[0] != 'N' && resposta[0] != 's' && resposta[0] != 'n')   {
                printf("\nResposta invalida, tente novamente.\n");
            }
        }
        if (resposta[0] == 'S' || resposta[0] == 's') {
            preencher_form();
        }
        fclose(arestas);
        fclose(vertices);
    }
    
    int tamanho;
    vertices = fopen("dados/vertices.txt", "r");
    fscanf(vertices, "%d", &tamanho);
    fclose(vertices);
    
    Grafo *g = inicializa_grafo(tamanho);
    ler_arestas_csv(g);

    printf("\n\n");
    exibe_grafo(g);
    printf("\n\n");

    int origem = -1;
    int destino = -1;
    while (origem < 0 || origem > tamanho - 1) {
        printf("Digite a origem (0 a %d): ", tamanho - 1);
        scanf("%d", &origem);
        if (origem < 0 || origem > tamanho - 1) {
            printf("Valor invalido, tente novamente.\n");
        }
    }

    while (destino < 0 || destino > tamanho - 1) {
        printf("Digite o destino (0 a %d): ", tamanho - 1);
        scanf("%d", &destino);
        if (destino < 0 || destino > tamanho - 1) {
            printf("Valor invalido, tente novamente.\n");
        }
    }
    printf("\n");
    dijkstra(g, origem, destino);
}