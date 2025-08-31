#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define WIDE 101
#define TALL 103
#define NB_ROBOTS 500

// #define WIDE 11
// #define TALL 7
// #define NB_ROBOTS 12

struct robot {
    int posx;
    int posy;
    int vx;
    int vy;
};
typedef struct robot robot;

void actualiser(robot* robots) {
    for (int i = 0; i < NB_ROBOTS; i++) {
        robots[i].posx = (robots[i].posx + robots[i].vx) % WIDE;
        robots[i].posy = (robots[i].posy + robots[i].vy) % TALL;
        if (robots[i].posx < 0) {
            robots[i].posx += WIDE;
        }
        if (robots[i].posy < 0) {
            robots[i].posy += TALL;
        }
    }
}

int compter(robot* robots) {
    int qnw = 0;
    int qne = 0;
    int qsw = 0;
    int qse = 0;
    for (int i = 0; i < NB_ROBOTS; i++) {
        if (robots[i].posx < WIDE / 2) {
            if (robots[i].posy < TALL / 2) {
                qnw++;
            }
            else if (robots[i].posy > TALL / 2) {
                qne++;
            }
        }
        else if (robots[i].posx > WIDE / 2) {
            if (robots[i].posy < TALL / 2) {
                qsw++;
            }
            else if (robots[i].posy > TALL / 2) {
                qse++;
            }
        }
    }
    printf("%d %d %d %d\n", qnw, qne, qsw, qse);
    return qnw * qne * qsw * qse;
}

void afficher_grille(robot* robots, int** positions) {
    printf("\n");
    for (int i = 0; i < TALL; i++) {
        for (int j = 0; j < WIDE; j++) {
            positions[i][j] = 0;
        }
    }
    for (int i = 0; i < NB_ROBOTS; i++) {
        // printf("%d %d\n", robots[i].posy, robots[i].posx);
        positions[robots[i].posy][robots[i].posx]++;
    }
    for (int i = 0; i < TALL; i++) {
        if (i == TALL / 2) {
            printf("\033[42m");
            for (int j = 0; j < WIDE+1; j++) {
                printf(" ");
            }
            printf("\033[00m\n");
        }
        else {
            for (int j = 0; j < WIDE; j++) {
                if (j == WIDE / 2) {
                    printf("\033[42m \033[00m");
                }
                else {
                    if (positions[i][j] == 0) {
                        printf(".");
                    }
                    else {
                        printf("%d", positions[i][j]);
                    }
                }
            }
            printf("\n");
        }
    }
}

robot* lire_fichier(FILE* f) {
    robot* robots = malloc(NB_ROBOTS * sizeof(robot));
    int posx, posy, vx, vy;
    for (int i = 0; i < NB_ROBOTS; i++) {
        fscanf(f, "p=%d,%d v=%d,%d\n", &posx, &posy, &vx, &vy);
        robots[i].posx = posx;
        robots[i].posy = posy;
        robots[i].vx = vx;
        robots[i].vy = vy;
    }
    return robots;
}

int main() {
    FILE* f = fopen("day14.txt", "r");
    robot* robots = lire_fichier(f);
    int** positions = malloc(TALL * sizeof(int*));
    for (int i = 0; i < TALL; i++) {
        positions[i] = malloc(WIDE * sizeof(int));
    }
    // afficher_grille(robots, positions);
    for (int i = 0; i < 100; i++) {
        actualiser(robots);
    }
    afficher_grille(robots, positions);
    printf("TOTAL : %d\n", compter(robots));
    fclose(f);
    return 0;
}