#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

int day_4_2() {
    FILE* f = NULL;
    f = fopen("advent_4.txt", "r");
    bool gagnants[100];
    int nombre_de_chaque[209];
    for (int i = 0; i < 209; i++) {
        nombre_de_chaque[i] = 1;
        printf("%d ", nombre_de_chaque[i]);
    }
    int cpt;
    int total = 0;
    int n;
    for (int k = 0; k < 209; k++) {
        fscanf(f, "Card %d:", &n);
        cpt = 0;
        for (int i = 0; i < 100; i++) {
            gagnants[i] = false;
        }
        for (int i = 0; i < 10; i++) {
            fscanf(f, "%d", &n);
            gagnants[n] = true;
        }
        fscanf(f, " | ");
        for (int i = 0; i < 25; i++) {
            fscanf(f, "%d", &n);
            if (gagnants[n]) {
                cpt++;
                if (k+cpt < 209) {
                    nombre_de_chaque[k+cpt] = nombre_de_chaque[k+cpt] + nombre_de_chaque[k];
                    printf("Carte %d : on ajoute %d, %d fois\n", k, k+cpt, nombre_de_chaque[k]);
                }
            }
        }
        printf("\n");
        for (int i = 0; i < 209; i++) {
            printf("%d ", nombre_de_chaque[i]);
        }
        printf("\n");
        fscanf(f, "\n");
        total = total + nombre_de_chaque[k];
    }
    fclose(f);
    return total;
}