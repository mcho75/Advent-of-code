#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

int day_4_1() {
    FILE* f = NULL;
    f = fopen("advent_4.txt", "r");
    bool gagnants[100];
    int cpt;
    int total = 0;
    int n;
    for (int k = 0; k < 209; k++) {
        cpt = 0;
        for (int i = 0; i < 100; i++) {
            gagnants[i] = false;
        }
        fscanf(f, "Card %d:", &n);
        printf("\nCarte %d\n", n);
        printf(" Gagnants :\n");
        for (int i = 0; i < 10; i++) {
            fscanf(f, "%d", &n);
            printf("  %d", n);
            gagnants[n] = true;
        }
        fscanf(f, " | ");
        printf("\n Tires :\n");
        for (int i = 0; i < 25; i++) {
            fscanf(f, "%d", &n);
            printf("  %d", n);
            if (gagnants[n]) {
                printf("Gagnant ! ");
                if (cpt == 0) {
                    cpt++;
                }
                else {
                    cpt = 2 * cpt;
                }
            }
        }
        fscanf(f, "\n");
        printf("\nTotal : %d\n", cpt);
        total = total + cpt;
    }
    fclose(f);
    return total;
}