#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

int day_3_1() {
    FILE* f = NULL;
    f = fopen("advent_3.txt", "r");
    int minmax[4] = {-1, 2, -1, 2};
    char symbole;
    int cpt = 0;
    int total = 0;
    int** tableau = malloc(140 * sizeof(int*));
    int nombre_lu[140];
    int position;
    int maximum = 0;
    bool lit_nombre;
    bool a_ajouter;
    for (int i = 0; i < 140; i++) {
        tableau[i] = malloc(140 * sizeof(int));
        for (int j = 0; j < 140; j++) {
            tableau[i][j] = 0;
        }
    }
    for (int i = 0; i < 140; i++) {
        position = 0;
        for (int j = 0; j < 141; j++) {
            fscanf(f, "%c", &symbole);
            if (((int)symbole) > 47 && ((int)symbole < 58)) {
                nombre_lu[position] = (int)symbole - 48;
                position++;
            }
            else {
                for (int k = 0; k < position; k++) {
                    tableau[i][j-1] = tableau[i][j-1] + (nombre_lu[k]*(int)pow(10, position-k-1));
                }
                if (j != 0 && maximum < tableau[i][j-1]) {
                    printf("Nouveau max : %d\n", tableau[i][j-1]);
                    maximum = tableau[i][j-1];
                }
                position = 0;
                if (symbole == '.') {
                    tableau[i][j] = -2;
                }
                else {
                    tableau[i][j] = -1;
                }
            }
        }
    }
    printf("Maximum : %d\n", maximum);
    for (int i = 103; i < 105; i++) {
        for (int j = 0; j < 140; j++) {
            printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 140; i++) {
        printf("Ligne %d\n", i);
        lit_nombre = false;
        a_ajouter = false;
        for (int j = 0; j < 140; j++) {
            if (tableau[i][j] > -1) {
                lit_nombre = true;
                if (i == 0) {minmax[0] = 0;} else {minmax[0] = -1;}
                if (i == 139) {minmax[1] = 0;} else {minmax[1] = 2;}
                if (j == 0) {minmax[2] = 0;} else {minmax[2] = -1;}
                if (j == 139) {minmax[3] = 0;} else {minmax[3] = 2;}
                for (int k = minmax[0]; k < minmax[1]; k++) {
                    for (int l = minmax[2]; l < minmax[3]; l++) {
                        if (tableau[i+k][j+l] == -1) {
                            a_ajouter = true;
                        }
                    }
                }
            }
            else if (lit_nombre) {
                if (a_ajouter) {
                    printf("Nombre a ajouter : %d\n", tableau[i][j-1]);
                    total = total + tableau[i][j-1];
                }
                lit_nombre = false;
                a_ajouter = false;
            }
        }
        if (a_ajouter && lit_nombre) {
            printf("Nombre a ajouter : %d\n", tableau[i][139]);
            total = total + tableau[i][139];
        }
    }
    free(tableau);
    fclose(f);
    return total;
}