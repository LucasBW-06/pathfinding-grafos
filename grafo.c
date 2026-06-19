#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"

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

Grafo* inicializa_grafo(int vertices) {
    if (vertices < 1) return NULL;
    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    g->numArestas = 0;
    g->numVertices = vertices;

    g->A = (ElemLista**) malloc(vertices * sizeof(ElemLista*));

    for (int i = 0; i < vertices; i++) {
        g->A[i] = NULL;
    }

    return g;
}

bool inserir_aresta(Grafo* g, int origem, int destino, int peso) {
    if (!g || origem < 0 || destino < 0 || origem >= g->numVertices || destino >= g->numVertices) return false;
    ElemLista *novo, *ant = NULL;
    ElemLista* atual = g->A[origem];
    while (atual && atual->vertice < destino) {
        ant = atual;
        atual = atual->prox;
    }
    if (atual && atual->vertice==destino) return false;
    novo = (ElemLista*)malloc(sizeof(ElemLista));
    novo->vertice = destino;
    novo->prox = atual;
    novo->peso = peso;
    if (ant) {
        ant->prox = novo;
    } else {
        g->A[origem] = novo;
    }
    g->numArestas++;
    return true;
}

void exibe_grafo(Grafo* g) {
    if (!g) return;
    printf("Imprimindo grafo (vertices: %i; arestas %i).\n", g->numVertices, g->numArestas);
    ElemLista* atual;
    for (int i = 0; i < g->numVertices; i++) {
        printf("[%i]", i);
        atual = g->A[i];
        while (atual) {
            printf(" >>[%i]>> %i", atual->peso, atual->vertice);
            atual = atual->prox;
        }
        printf("\n");
    }
}

bool libera_grafo(Grafo* g) {
    if (g == NULL) return false;

    ElemLista *atual, *apagar;

    for (int i = 0; i < g->numVertices; i++) {
        atual = g->A[i];
        while (atual) {
            apagar = atual;
            atual = atual->prox;
            free(apagar);
        }
    }

    free(g->A);

    g->numArestas = 0;
    g->numVertices = 0;
    g->A = NULL;
    free(g);
    return true;
}

int numero_vertices(Grafo* g) {
    if (g != NULL) return g->numVertices;
    return -1;
}

int numero_aresta(Grafo* g) {
    if (g != NULL) return g->numArestas;
    return -1;
}