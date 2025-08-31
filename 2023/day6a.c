#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

int day_6_1() {
    FILE* f = NULL;
    f = fopen("advent_6.txt", "r");
    int time[4];
    int distance[4];
    int cpt;
    int total = 1;
    fscanf(f, "Time:");
    for (int k = 0; k < 4; k++) {
        fscanf(f, "%d", &time[k]);
        printf("%d ", time[k]);
    }
    printf("\n");
    fscanf(f, "\nDistance:");
    for (int k = 0; k < 4; k++) {
        fscanf(f, "%d", &distance[k]);
        printf("%d ", distance[k]);
    }
    for (int k = 0; k < 4; k++) {
        cpt = 0;
        for (int i = 0; i < time[k]; i++) {
            printf("\nPour i = %d, on avance de %d ", i, (time[k]-i)*i);
            if (distance[k] < (time[k]-i)*i) {
                cpt++;
                printf(" OK !");
            }
        }
        printf("Total %d : %d\n\n", k, cpt);
        total = total * cpt;
    }
    fclose(f);
    return total;
}