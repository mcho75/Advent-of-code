#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define TAILLE 140

struct barrieres {
    char valeur;
    bool deja_vu;
    bool haut;
    bool bas;
    bool gauche;
    bool droite;
};
typedef struct barrieres barrieres;

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

bool hors_grille(int i, int j) {
    return (i < 0) || (j < 0) || (i >= TAILLE) || (j >= TAILLE);
}

int explorer(char** fleurs, char a_chercher, int i, int j, bool** deja_vu, barrieres** barr, int* aire) {
    if (hors_grille(i, j)) {
        return 1;
    }
    if (deja_vu[i][j]) {
        return 0;
    }
    if (fleurs[i][j] != a_chercher) {
        return 1;
    }
    deja_vu[i][j] = true;
    barr[i][j].deja_vu = true;
    barr[i][j].bas = hors_grille(i+1, j) || (fleurs[i+1][j] != a_chercher);
    barr[i][j].haut = hors_grille(i-1, j) || (fleurs[i-1][j] != a_chercher);
    barr[i][j].gauche = hors_grille(i, j-1) || (fleurs[i][j-1] != a_chercher);
    barr[i][j].droite = hors_grille(i, j+1) || (fleurs[i][j+1] != a_chercher);
    *aire = *aire + 1;
    return explorer(fleurs, a_chercher, i+1, j, deja_vu, barr, aire)
             + explorer(fleurs, a_chercher, i-1, j, deja_vu, barr, aire)
             + explorer(fleurs, a_chercher, i, j+1, deja_vu, barr, aire)
             + explorer(fleurs, a_chercher, i, j-1, deja_vu, barr, aire);
}

// 0: haut, 1: droite, 2: bas, 3: gauche
void parcourir(barrieres** barr, char a_chercher, int i, int j, int direction) {
    if (!hors_grille(i,j) && (barr[i][j].valeur == a_chercher)) {
        // printf("       Parcours de %c depuis %d %d (direction : %d)\n", a_chercher, i, j, direction);
        barr[i][j].valeur = '.';
        if (direction == 0 && barr[i][j].haut == true) {
            barr[i][j].haut = false;
            parcourir(barr, a_chercher, i, j-1, direction);
            parcourir(barr, a_chercher, i, j+1, direction);
        }
        if (direction == 1 && barr[i][j].droite == true) {
            barr[i][j].droite = false;
            parcourir(barr, a_chercher, i-1, j, direction);
            parcourir(barr, a_chercher, i+1, j, direction);
        }
        if (direction == 2 && barr[i][j].bas == true) {
            barr[i][j].bas = false;
            parcourir(barr, a_chercher, i, j-1, direction);
            parcourir(barr, a_chercher, i, j+1, direction);
        }
        if (direction == 3 && barr[i][j].gauche == true) {
            barr[i][j].gauche = false;
            parcourir(barr, a_chercher, i-1, j, direction);
            parcourir(barr, a_chercher, i+1, j, direction);
        }
        barr[i][j].valeur = a_chercher;
    }
}

int compter_barrieres(barrieres** barr, bool** deja_vu) {
    int total = 0;
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (deja_vu[i][j]) {
                if (barr[i][j].haut) {
                    // printf("   %d %d : haut\n", i, j);
                    total++;
                    parcourir(barr, barr[i][j].valeur, i, j, 0);
                }
                if (barr[i][j].droite) {
                    // printf("   %d %d : droite\n", i, j);
                    total++;
                    parcourir(barr, barr[i][j].valeur, i, j, 1);
                }
                if (barr[i][j].bas) {
                    // printf("   %d %d : bas\n", i, j);
                    total++;
                    parcourir(barr, barr[i][j].valeur, i, j, 2);
                }
                if (barr[i][j].gauche) {
                    // printf("   %d %d : gauche\n", i, j);
                    total++;
                    parcourir(barr, barr[i][j].valeur, i, j, 3);
                }
            }
        }
    }
    return total;
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
    barrieres** barr = malloc(TAILLE * sizeof(barrieres*));
    for (int i = 0; i < TAILLE; i++) {
        barr[i] = malloc(TAILLE * sizeof(barrieres));
        for (int j = 0; j < TAILLE; j++) {
            barr[i][j].valeur = fleurs[i][j];
            barr[i][j].deja_vu = false;
            barr[i][j].bas = false;
            barr[i][j].haut = false;
            barr[i][j].gauche = false;
            barr[i][j].droite = false;
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
            if (!barr[i][j].deja_vu) {
                aire = 0;
                perim = explorer(fleurs, fleurs[i][j], i, j, deja_vu, barr, &aire);
                perim = compter_barrieres(barr, deja_vu);
                printf("Pour %c : %d %d\n", fleurs[i][j], aire, perim);
                total += aire * perim;
            }
        }
    }
    afficher(fleurs);
    printf("TOTAL : %lld\n", total);
}