#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

int day_3_2() {
    FILE* f = NULL;
    f = fopen("advent_3.txt", "r");
    int minmax[4] = {-1, 2, -1, 2};
    char symbole;
    int cpt = 0;
    int total = 0;
    int** tableau = malloc(140 * sizeof(int*));
    int nombre_lu[140];
    int position;
    bool a_ajouter[1000];
    int nb_voisins;
    int score_gear;
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
                    for (int l = 1; l < position+1; l++) {
                        tableau[i][j-l] = tableau[i][j-l] + (nombre_lu[k]*(int)pow(10, position-k-1));
                    }
                }
                position = 0;
                if (symbole == '*') {
                    tableau[i][j] = -1;
                }
                else {
                    tableau[i][j] = -2;
                }
            }
        }
    }
    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 140; j++) {
            printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < 140; i++) {
        printf("Ligne %d\n", i);
        for (int j = 0; j < 140; j++) {
            for (int k = 0; k < 1000; k++) {
                a_ajouter[k] = false;
            }
            nb_voisins = 0;
            score_gear = 1;
            if (tableau[i][j] == -1) {
                printf(" Roue en %d %d\n", i, j);
                if (i == 0) {minmax[0] = 0;} else {minmax[0] = -1;}
                if (i == 139) {minmax[1] = 0;} else {minmax[1] = 2;}
                if (j == 0) {minmax[2] = 0;} else {minmax[2] = -1;}
                if (j == 139) {minmax[3] = 0;} else {minmax[3] = 2;}
                for (int k = minmax[0]; k < minmax[1]; k++) {
                    for (int l = minmax[2]; l < minmax[3]; l++) {
                        if (tableau[i+k][j+l] > 0) {
                            if (!a_ajouter[tableau[i+k][j+l]]) {
                                nb_voisins++;
                                a_ajouter[tableau[i+k][j+l]] = true;
                                printf("  %d est un voisin\n", tableau[i+k][j+l]);
                            }
                        }
                    }
                }
                if (nb_voisins == 2) {
                    printf("  Deux voisins : ok !!\n");
                    for (int i = 0; i < 1000; i++) {
                        if (a_ajouter[i]) {
                            score_gear = score_gear * i;
                        }
                    }
                    total = total + score_gear;
                }
            }
        }
    }
    for (int i = 0; i < 140; i++) {
        free(tableau[i]);
    }
    free(tableau);
    fclose(f);
    return total;
}