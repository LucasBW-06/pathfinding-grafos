#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <stdbool.h>

typedef struct Grafo Grafo;

void busca(Grafo* g, int origem, int destino);

#endif