#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pathfinder.h"

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

typedef struct No {
    int vertice;
    int dist;
} No;

typedef struct Heap {
    No* dados;
    int tamanho;
    int capacidade;
} Heap;

Heap* inicializa_heap(int capacidade) {
    if (capacidade < 1) return NULL;
    Heap *h = (Heap*) malloc(sizeof(Heap));
    h->dados = malloc(sizeof(No)*capacidade);
    h->tamanho = 0;
    h->capacidade = capacidade;

    return h;
}

void subir(Heap* h, int indice) {
    if (!h || indice == 0) return;

    int pai = (indice - 1) / 2;

    if (h->dados[indice].dist < h->dados[pai].dist) {
        No temp = h->dados[indice];
        h->dados[indice] = h->dados[pai];
        h->dados[pai] = temp;

        subir(h, pai);
    }
}

void descer(Heap* h, int indice) {
    if (!h || indice >= h->tamanho) return;

    int filho = 2 * indice + 1;
    if (filho >= h->tamanho) return;

    if (filho + 1 < h->tamanho) {
        if (h->dados[filho + 1].dist < h->dados[filho].dist) {
            filho++;
        }
    }

    if (h->dados[filho].dist < h->dados[indice].dist) {
        No temp = h->dados[indice];
        h->dados[indice] = h->dados[filho];
        h->dados[filho] = temp;

        descer(h, filho);
    }
}

bool inserir_heap(Heap* h, int vertice, int distancia) {
    if (!h) return false;

    No novo;
    novo.vertice = vertice;
    novo.dist = distancia;

    h->dados[h->tamanho] = novo;

    subir(h, h->tamanho);

    h->tamanho++;

    return true;
}

bool remover_heap(Heap* h, No* saida) {
    if (!h || h->tamanho == 0) return false;

    *saida = h->dados[0];

    h->tamanho--;
    h->dados[0] = h->dados[h->tamanho];

    descer(h, 0);

    return true;
}

bool menor_distancia(int numA, int numB) {
    if (numA == -1) return false;
    if (numB == -1) return true;
    return numA < numB;
}

void dijkstra(Grafo* g, int origem, int* pai, int* distancia) {
    if (!g || g->numVertices < 1) return;

    Heap *h = inicializa_heap(g->numArestas + 1);

    distancia[origem] = 0;

    inserir_heap(h, origem, 0);

    while (h->tamanho > 0) {
        No atual;
        remover_heap(h, &atual);
        if (atual.dist > distancia[atual.vertice]) continue;
        ElemLista* v = g->A[atual.vertice];
        while (v) {
            if (menor_distancia(atual.dist + v->peso, distancia[v->vertice])) {
                distancia[v->vertice] = atual.dist + v->peso;
                pai[v->vertice] = atual.vertice;
                inserir_heap(h, v->vertice, distancia[v->vertice]);
            }
            v = v->prox;
        }
    }
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

bool verificar_acesso(int tamanho, int* distancia) {
    for (int i = 0; i < tamanho; i++) {
        if (distancia[i] == -1) {
            return false;
        }
    }
    return true;
}

void busca(Grafo* g, int origem, int destino) {
    
    int* pai = malloc(sizeof(int)*g->numVertices);
    for (int i = 0; i < g->numVertices; i++) pai[i] = -1;

    // Distância -1 simboliza distância infinita
    int* distancia = malloc(sizeof(int)*g->numVertices);
    for (int i = 0; i < g->numVertices; i++) distancia[i] = -1;

    dijkstra(g, origem, pai, distancia);
    
    if (verificar_acesso(g->numVertices, distancia)) {
        printf("Todas as salas sao alcancaveis.\n");
    } else {
        printf("Há paredes que bloqueiam caminhos para certas salas.\n");
    }

    printf("\nSala de origem: %i", origem);
    printf("\nSala de destino: %i", destino);

    if (origem == destino) {
        printf("Origem e destino sao iguais!\n");
    } else if (distancia[destino] == -1) {
        printf("Nao existe caminho para o destino.\n");
    } else {
        printf("\nMenor caminho de %i para %i: ", origem, destino);
        imprimir_caminho(origem, destino, pai);
        printf("\nDistancia total entre origem e destino: %i\n", distancia[destino]);
    }

    free(distancia);
    free(pai);
}