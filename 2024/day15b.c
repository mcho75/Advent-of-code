#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define DIMENSION 50

// 1361518 : trop peu

char** lire_fichier_grille(FILE* f, int* x, int* y) {
    char** tab = malloc(DIMENSION * sizeof(char*));
    char lu;
    for (int i = 0; i < DIMENSION; i++) {
        tab[i] = malloc(2*DIMENSION * sizeof(char));
        for (int j = 0; j < 2*DIMENSION; j = j + 2) {
            fscanf(f, "%c", &lu);
            if (lu == '#') {
                tab[i][j] = '#';
                tab[i][j+1] = '#';
            }
            if (lu == 'O') {
                tab[i][j] = '[';
                tab[i][j+1] = ']';
            }
            if (lu == '.') {
                tab[i][j] = '.';
                tab[i][j+1] = '.';
            }
            if (lu == '@') {
                tab[i][j] = '@';
                tab[i][j+1] = '.';
                *x = j;
                *y = i;
            }
        }
        fscanf(f, "\n");
    }
    return tab;
}

bool dans_grille(int i, int j) {
    return ((i >= 0) && (i < DIMENSION) && (j >= 0) && (j < 2*DIMENSION));
}

bool deplacement_caisse(char** grille, int i, int j, int x, int y) {
    // printf("Analyse en %d %d (voit %c)\n", x, y, grille[y+i][x+j]);
    if (!dans_grille(y+i, x+j)) {
        return false;
    }
    if (grille[y+i][x+j] == '.') {
        return true;
    }
    if (grille[y+i][x+j] == '#') {
        return false;
    }
    if (i != 0) {
        // deplacement haut/bas (particulier) avec j = 0
        if (grille[y+i][x] == '[') {
            if (deplacement_caisse(grille, i, j, x, y+i) && deplacement_caisse(grille, i, j, x+1, y+i)) {
                grille[y+i][x] = '.';
                grille[y+i][x+1] = '.';
                grille[y+(2*i)][x] = '[';
                grille[y+(2*i)][x+1] = ']';
                return true;
            }
            else {
                return false;
            }
        }
        if (grille[y+i][x] == ']') {
            if (deplacement_caisse(grille, i, j, x, y+i) && deplacement_caisse(grille, i, j, x-1, y+i)) {
                grille[y+i][x] = '.';
                grille[y+i][x-1] = '.';
                grille[y+(2*i)][x] = ']';
                grille[y+(2*i)][x-1] = '[';
                return true;
            }
            else {
                return false;
            }
        }
        return grille[y+i][x] == '.';
    }
    if (deplacement_caisse(grille, i, j, x+j, y)) {
        grille[y][x+(2*j)] = grille[y][x+j];
        grille[y][x+j] = '.';
        return true;
    }
    return false;
}

void deplacer(char** grille, char** copie, int i, int j, int* x, int* y) {
    int vx = *x;
    int vy = *y;
    printf("Voit : %c\n", grille[vy+i][vx+j]);
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < 2*DIMENSION; j++) {
            copie[i][j] = grille[i][j];
        }
    }
    if (deplacement_caisse(grille, i, j, vx, vy)) {
        *x = vx+j;
        *y = vy+i;
        grille[vy+i][vx+j] = '@';
        grille[vy][vx] = '.';
    }
    else {
        printf("Ne peut pas deplacer\n");
        for (int i = 0; i < DIMENSION; i++) {
            for (int j = 0; j < 2*DIMENSION; j++) {
                grille[i][j] = copie[i][j];
            }
        }
    }
}

void afficher_grille(char** grille, int x, int y) {
    printf("\n");
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < 2*DIMENSION; j++) {
            // printf("%c", grille[i][j]);
            if ((x == j) && (y == i)) {
                printf("\033[47m \033[00m");
            }
            else {
                if (grille[i][j] == '#') {
                    printf("\033[46m \033[00m");
                }
                else if (grille[i][j] == '[') {
                    printf("\033[41m \033[00m");
                }
                else if (grille[i][j] == ']') {
                    printf("\033[45m \033[00m");
                }
                else {
                    printf("\033[00m \033[00m");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void lire_fichier_mouvements(FILE* f, char** grille, int* x, int* y) {
    char scan;
    char** copie = malloc(DIMENSION * sizeof(char*));
    for (int i = 0; i < DIMENSION; i++) {
        copie[i] = malloc(2*DIMENSION * sizeof(char));
    }
    while (fscanf(f, "%c", &scan) == 1) {
        printf("Deplacement : %c\n", scan);
        if (scan == '^') {
            deplacer(grille, copie, -1, 0, x, y);
        }
        else if (scan == '>') {
            deplacer(grille, copie, 0, 1, x, y);
        }
        else if (scan == 'v') {
            deplacer(grille, copie, 1, 0, x, y);
        }
        else if (scan == '<') {
            deplacer(grille, copie, 0, -1, x, y);
        }
        // afficher_grille(grille, *x, *y);
        // system("clear");
    }
}

long long int compter(char** grille) {
    long long int total = 0;
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < 2*DIMENSION; j++) {
            if (grille[i][j] == '[') {
                printf("i = %d, j = %d\n", i, j);
                total += (100*i) + j;
            }
        }
    }
    return total;
}

int main() {
    int x, y;
    FILE* f = fopen("day15.txt", "r");
    char** grille = lire_fichier_grille(f, &x, &y);
    afficher_grille(grille, x, y);
    lire_fichier_mouvements(f, grille, &x, &y);
    afficher_grille(grille, x, y);
    printf("TOTAL : %lld\n", compter(grille));
    fclose(f);
    return 0;
}