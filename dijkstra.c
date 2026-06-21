#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dijkstra.h"

typedef struct aux{
    int vertice;
    int peso;
    struct aux* prox;
} ElemLista, *PONT;

typedef struct Grafo {
    int numVertices;
    int numArestas;
    ElemLista** A;
} Grafo;

bool menor_distancia(int numA, int numB) {
    if (numA == -1) return false;
    if (numB == -1) return true;
    return numA < numB;
}

void busca_dijkstra(Grafo* g, int origem, int* pai, int* distancia) {
    if (!g || g->numVertices < 1) return;
    
    bool* visitado = malloc(sizeof(int)*g->numVertices);
    for (int i = 0; i < g->numVertices; i++) visitado[i] = false;

    distancia[origem] = 0;

    for (int i = 0; i < g->numVertices - 1; i++) {
        int escolhido = -1;
        int melhor = -1;

        for (int j = 0; j < g->numVertices; j++) {
            if (!visitado[j] && menor_distancia(distancia[j], melhor)) {
                melhor = distancia[j];
                escolhido = j;
            }
        }

        if (escolhido == -1) break;

        visitado[escolhido] = true;

        ElemLista* p = g->A[escolhido];

        while (p) {
            int vertice = p->vertice;
            int peso = p->peso;

            if (menor_distancia(distancia[escolhido] + peso, distancia[vertice])) {
                distancia[vertice] = distancia[escolhido] + peso;
                pai[vertice] = escolhido;
            }

            p = p->prox;
        }
    }

    free(visitado);
}

void imprimir_caminho(int origem, int destino, int* pai) {
    if (destino == -1) return;

    if (destino == origem) {
        printf("%d ", origem);
        return;
    }

    imprimir_caminho(origem, pai[destino], pai);
    printf("-> %d ", destino);
}

void dijkstra(Grafo* g, int origem, int destino) {
    if (origem == destino) {
        printf("Origem e destino sao iguais!");
        return;
    }
    
    int* pai = malloc(sizeof(int)*g->numVertices);
    for (int i = 0; i < g->numVertices; i++) pai[i] = -1;

    // Distância -1 simboliza distância infinita
    int* distancia = malloc(sizeof(int)*g->numVertices);
    for (int i = 0; i < g->numVertices; i++) distancia[i] = -1;

    busca_dijkstra(g, origem, pai, distancia);

    
    if (distancia[destino] == -1) {
        printf("Nao existe caminho\n");
    } else {
        printf("\nMenor caminho: ");
        imprimir_caminho(origem, destino, pai);
        printf("\nDistancia total: %i\n", distancia[destino]);
    }

    free(distancia);
    free(pai);
}