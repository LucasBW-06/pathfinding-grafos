#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdbool.h>

typedef struct Grafo Grafo;

bool menor_distancia(int numA, int numB);

void busca_dijkstra(Grafo* g, int origem, int* pai, int* distancia);

void imprimir_caminho(int origem, int destino, int* pai);

void dijkstra(Grafo* g, int origem, int destino);

#endif