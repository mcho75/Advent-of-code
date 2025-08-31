#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

int day_2_2() {
    FILE* f = NULL;
    f = fopen("advent_2.txt", "r");
    char cube[MAX];
    int couleurs[3];
    int total = 0;
    int nombre;
    int n;
    bool a_compter;
    bool en_cours;
    for (int k = 0; k < 100; k++) {
        a_compter = true;
        en_cours = true;
        fscanf(f, "Game %d: ", &n);
        printf("Partie %d :\n", n);
        for (int i = 0; i < 3; i++) {
            couleurs[i] = 0;
        }
        while (en_cours) {
            fscanf(f, "%d %s", &nombre, cube);
            if (cube[0] == 'r') {
                if (nombre > couleurs[0]) {
                    couleurs[0] = nombre;
                    printf(" Nouveau min : ");
                }
                if (cube[3] == '\0') {
                    en_cours = false;
                }
            }
            if (cube[0] == 'g') {
                if (nombre > couleurs[1]) {
                    couleurs[1] = nombre;
                    printf(" Nouveau min : ");
                }
                if (cube[5] == '\0') {
                    en_cours = false;
                }
            }
            if (cube[0] == 'b') {
                if (nombre > couleurs[2]) {
                    couleurs[2] = nombre;
                    printf(" Nouveau min : ");
                }
                if (cube[4] == '\0') {
                    en_cours = false;
                }
            }
            printf(" Pour %s : %d\n", cube, nombre);
        }
        fscanf(f, "\n");
        printf("Total de %d\n", couleurs[0] * couleurs[1] * couleurs[2]);
        total = total + (couleurs[0] * couleurs[1] * couleurs[2]);
    }
    fclose(f);
    return total;
}