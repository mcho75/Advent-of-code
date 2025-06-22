#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define LARGEUR 59
#define HAUTEUR 59

// Test : 8
// Vrai : 59

int** lire_fichier(FILE* f) {
    int** tab = malloc(HAUTEUR * sizeof(int*));
    char c;
    for (int i = 0; i < HAUTEUR; i++) {
        tab[i] = malloc(LARGEUR * sizeof(int));
        for (int j = 0; j < LARGEUR; j++) {
            fscanf(f, "%c", &c);
            tab[i][j] = c - 48;
        }
        fscanf(f, "\n");
    }
    return tab;
}

int nb_chemins(int** tab, int i, int j, int valeur_act, bool** deja_vu) {
    if ((i < 0) || (i >= HAUTEUR) || (j < 0) || (j >= LARGEUR)) {
        return 0;
    }
    if (deja_vu[i][j]) {
        return 0;
    }
    if ((valeur_act == 8) && (tab[i][j] == 9)) {
        // printf("9 detecte en (%d %d)\n", i, j);
        deja_vu[i][j] = true;
        return 1;
    }
    if (tab[i][j] == valeur_act + 1) {
        // printf("    %d detecte en (%d %d)\n", valeur_act+1, i, j);
        return nb_chemins(tab, i-1, j, valeur_act+1, deja_vu)
               + nb_chemins(tab, i+1, j, valeur_act+1, deja_vu)
               + nb_chemins(tab, i, j-1, valeur_act+1, deja_vu)
               + nb_chemins(tab, i, j+1, valeur_act+1, deja_vu);
    }
    return 0;
}

int nb_chemins_distincts(int** tab, int i, int j, int valeur_act) {
    if ((i < 0) || (i >= HAUTEUR) || (j < 0) || (j >= LARGEUR)) {
        return 0;
    }
    if ((valeur_act == 8) && (tab[i][j] == 9)) {
        // printf("9 detecte en (%d %d)\n", i, j);
        return 1;
    }
    if (tab[i][j] == valeur_act + 1) {
        // printf("    %d detecte en (%d %d)\n", valeur_act+1, i, j);
        return nb_chemins_distincts(tab, i-1, j, valeur_act+1)
               + nb_chemins_distincts(tab, i+1, j, valeur_act+1)
               + nb_chemins_distincts(tab, i, j-1, valeur_act+1)
               + nb_chemins_distincts(tab, i, j+1, valeur_act+1);
    }
    return 0;
}

int chercher_zeros(int** tab) {
    bool** deja_vu = malloc(HAUTEUR * sizeof(bool*));
    for (int i = 0; i < HAUTEUR; i++) {
        deja_vu[i] = malloc(LARGEUR * sizeof(bool));
    }
    int total = 0;
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            if (tab[i][j] == 0) {
                // int val = nb_chemins(tab, i, j, -1, deja_vu);
                int val = nb_chemins_distincts(tab, i, j, -1);
                printf("POUR CE 0 : %d\n", val);
                total += val;
            }
        }
    }
    return total;
}

void afficher_tab(int** tab) {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            printf("%d", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    FILE* f = fopen("day10.txt", "r");
    int** tab = lire_fichier(f);
    fclose(f);
    printf("\n");
    afficher_tab(tab);
    printf("TOTAL : %d\n", chercher_zeros(tab));
    return 0;
}