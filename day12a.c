#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define TAILLE 140

char** lire_fichier_espaces(FILE* f) {
    char** tab = malloc((2*TAILLE+1) * sizeof(char*));
    for (int i = 0; i < TAILLE; i++) {
        tab[2*i] = malloc((2*TAILLE+1) * sizeof(char));
        tab[2*i+1] = malloc((2*TAILLE+1) * sizeof(char));
        for (int j = 0; j < TAILLE; j++) {
            fscanf(f, "%c", &tab[2*i+1][2*j+1]);
            tab[2*i+1][2*j] = ' ';
            tab[2*i][2*j] = ' ';
            tab[2*i][2*j+1] = ' ';
        }
        tab[2*i][2*TAILLE] = ' ';
        tab[2*i+1][2*TAILLE] = ' ';
        fscanf(f, "\n");
    }
    tab[2*TAILLE] = malloc((2*TAILLE+1) * sizeof(char));
    for (int i = 0; i < 2*TAILLE + 1; i++) {
        tab[2*TAILLE][i] = ' ';
    }
    return tab;
}

int explorer(char** fleurs, char a_chercher, int i, int j, bool** deja_vu, bool**deja_vu2, int* aire) {
    if ((i < 0) || (j < 0) || (i >= TAILLE) || (j >= TAILLE)) {
        // printf("(%d %d)\n", i, j);
        return 1;
    }
    if (deja_vu[i][j]) {
        return 0;
    }
    if (fleurs[i][j] != a_chercher) {
        return 1;
    }
    deja_vu[i][j] = true;
    deja_vu2[i][j] = true;
    *aire = *aire + 1;
    // printf("(%d %d)\n", i, j);
    return explorer(fleurs, a_chercher, i+1, j, deja_vu, deja_vu2, aire)
             + explorer(fleurs, a_chercher, i-1, j, deja_vu, deja_vu2, aire)
             + explorer(fleurs, a_chercher, i, j+1, deja_vu, deja_vu2, aire)
             + explorer(fleurs, a_chercher, i, j-1, deja_vu, deja_vu2, aire);
}

char** lire_fichier(FILE* f) {
    char** tab = malloc(TAILLE * sizeof(char*));
    for (int i = 0; i < TAILLE; i++) {
        tab[i] = malloc(TAILLE * sizeof(char));
        for (int j = 0; j < TAILLE; j++) {
            fscanf(f, "%c", &tab[i][j]);
        }
        fscanf(f, "\n");
    }
    return tab;
}

void afficher(char** fleurs) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            printf("\033[4%dm \033[00m", (fleurs[i][j]-65)%9);
        }
        printf("\n");
    }
}

int main() {
    FILE* f = fopen("day12.txt", "r");
    char** fleurs = lire_fichier(f);
    fclose(f);
    bool** deja_vu = malloc(TAILLE * sizeof(bool*));
    for (int i = 0; i < TAILLE; i++) {
        deja_vu[i] = malloc(TAILLE * sizeof(bool));
    }
    bool** deja_vu2 = malloc(TAILLE * sizeof(bool*));
    for (int i = 0; i < TAILLE; i++) {
        deja_vu2[i] = malloc(TAILLE * sizeof(bool));
        for (int j = 0; j < TAILLE; j++) {
            deja_vu2[i][j] = false;
        }
    }
    int aire;
    int perim;
    long long int total = 0;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            for (int i = 0; i < TAILLE; i++) {
                for (int j = 0; j < TAILLE; j++) {
                    deja_vu[i][j] = false;
                }
            }
            if (!deja_vu2[i][j]) {
                aire = 0;
                perim = explorer(fleurs, fleurs[i][j], i, j, deja_vu, deja_vu2, &aire);
                printf("Pour %c : %d %d\n", fleurs[i][j], aire, perim);
                total += aire * perim;
            }
        }
    }
    // afficher(fleurs);
    printf("TOTAL : %lld\n", total);
}