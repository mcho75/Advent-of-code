#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define DIMENSION 50

char** lire_fichier_grille(FILE* f, int* x, int* y) {
    char** tab = malloc(DIMENSION * sizeof(char*));
    for (int i = 0; i < DIMENSION; i++) {
        tab[i] = malloc(DIMENSION * sizeof(char));
        for (int j = 0; j < DIMENSION; j++) {
            fscanf(f, "%c", &tab[i][j]);
            if (tab[i][j] == '@') {
                *x = j;
                *y = i;
            }
        }
        fscanf(f, "\n");
    }
    return tab;
}

bool dans_grille(int i, int j) {
    return ((i >= 0) && (i < DIMENSION) && (j >= 0) && (j < DIMENSION));
}

bool deplacement_caisse(char** grille, int i, int j, int x, int y) {
    if (!dans_grille(y+i, x+j)) {
        return false;
    }
    if (grille[y+i][x+j] == 'O') {
        deplacement_caisse(grille, i, j, x+j, y+i);
        // if (deplacement_caisse(grille, i, j, x+j, y+i)) {
        //     grille[y+i][x+j] = 'O';
        //     grille[y][x] = '.';
        //     return true;
        // }
        // return false;
    }
    if (grille[y+i][x+j] == '.') {
        grille[y+i][x+j] = 'O';
        grille[y][x] = '.';
        return true;
    }
    return false;
}

void deplacer(char** grille, int i, int j, int* x, int* y) {
    int vx = *x;
    int vy = *y;
    printf("Voit : %c\n", grille[vy+i][vx+j]);
    if (deplacement_caisse(grille, i, j, vx, vy)) {
        *x = vx+j;
        *y = vy+i;
        grille[vy+i][vx+j] = '@';
        grille[vy][vx] = '.';
    }
    // else if (grille[vy+i][vx+j] == 'O') {
    //     if ((vy+2*i >= 0) && (vy+2*i >= 0) && (vy+2*i < DIMENSION) && (vx+2*j < DIMENSION)) {
    //         if (grille[vy+(2*i)][vx+(2*j)] == '.') {
    //             *x = vx+j;
    //             *y = vy+i;
    //             grille[vy+(2*i)][vx+(2*j)] = 'O';
    //             grille[vy+i][vx+j] = '@';
    //             grille[vy][vx] = '.';
    //         }
    //     }
    // }
}

void afficher_grille(char** grille, int x, int y) {
    printf("\n");
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            if ((x == j) && (y == i)) {
                printf("\033[47m  \033[00m");
            }
            else {
                if (grille[i][j] == '#') {
                    printf("\033[46m  \033[00m");
                }
                else if (grille[i][j] == 'O') {
                    printf("\033[41m  \033[00m");
                }
                else {
                    printf("\033[00m  \033[00m");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void lire_fichier_mouvements(FILE* f, char** grille, int* x, int* y) {
    char scan;
    while (fscanf(f, "%c", &scan) == 1) {
        printf("Deplacement : %c\n", scan);
        if (scan == '^') {
            deplacer(grille, -1, 0, x, y);
        }
        else if (scan == '>') {
            deplacer(grille, 0, 1, x, y);
        }
        else if (scan == 'v') {
            deplacer(grille, 1, 0, x, y);
        }
        else if (scan == '<') {
            deplacer(grille, 0, -1, x, y);
        }
        afficher_grille(grille, *x, *y);
        // system("clear");
    }
}

int compter(char** grille) {
    int total = 0;
    for (int i = 0; i < DIMENSION; i++) {
        for (int j = 0; j < DIMENSION; j++) {
            if (grille[i][j] == 'O') {
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
    lire_fichier_mouvements(f, grille, &x, &y);
    afficher_grille(grille, x, y);
    printf("TOTAL : %d\n", compter(grille));
    fclose(f);
    return 0;
}