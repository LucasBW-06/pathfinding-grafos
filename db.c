#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "db.h"
#include "grafo.h"

bool ler_arestas_csv(Grafo *g, const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (!arq) return false;

    char linha[100];

    // Pula o cabeçalho
    fgets(linha, sizeof(linha), arq);

    while (fgets(linha, sizeof(linha), arq)) {

        int origem, destino, peso;
        char *token;

        // origem
        token = strtok(linha, ",");
        if (!token) continue;
        origem = atoi(token);

        // destino
        token = strtok(NULL, ",");
        if (!token) continue;
        destino = atoi(token);

        // peso
        token = strtok(NULL, ",");
        if (!token) continue;
        peso = atoi(token);

        inserir_aresta(g, origem, destino, peso);
    }

    fclose(arq);
    return true;
}