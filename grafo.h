#include <stdbool.h>
#ifndef GRAFO_H
#define GRAFO_H

typedef struct Grafo Grafo;

Grafo* inicializa_grafo(int vertices);

bool inserir_aresta(Grafo* g, int origem, int destino, int peso);

void exibe_grafo(Grafo* g);

bool libera_grafo(Grafo* g);

int numero_vertices(Grafo* g);

int numero_arestas(Grafo* g);

#endif