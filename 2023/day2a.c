#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

int day_2_1() {
    FILE* f = NULL;
    f = fopen("advent_2.txt", "r");
    char cube[MAX];
    int couleurs[3] = {12, 13, 14};
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
        while (en_cours) {
            fscanf(f, "%d %s", &nombre, cube);
            if (cube[0] == 'r') {
                if (nombre > couleurs[0]) {
                    a_compter = false;
                }
                if (cube[3] == '\0') {
                    en_cours = false;
                }
            }
            if (cube[0] == 'g') {
                if (nombre > couleurs[1]) {
                    a_compter = false;
                }
                if (cube[5] == '\0') {
                    en_cours = false;
                }
            }
            if (cube[0] == 'b') {
                if (nombre > couleurs[2]) {
                    a_compter = false;
                }
                if (cube[4] == '\0') {
                    en_cours = false;
                }
            }
            printf(" Pour %s : %d\n", cube, nombre);
        }
        fscanf(f, "\n");
        if (a_compter) {
            total = total + n;
        }
    }
    fclose(f);
    return total;
}