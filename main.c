#include "grafo.h"
#include "db.h"
#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Grafo *g = inicializa_grafo(20);
    ler_arestas_csv(g, "arestas.csv");

    exibe_grafo(g);

    dijkstra(g, 0, 3);
}