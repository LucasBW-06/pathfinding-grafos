#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == j) continue;
            if (rand() % 2 == 1) {
                int peso = rand() % 20 + 1;
                printf("%d,%d,%d\n", i, j, peso);
            }
        }
    }
}