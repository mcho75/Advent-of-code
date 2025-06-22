#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define TAILLE 71

typedef long long int llint;

struct couple {
    llint x;
    llint y;
};
typedef struct couple couple;

struct file {
    llint x;
    llint y;
    llint h;
    struct file* suiv;
};
typedef struct file file;

file* creer_file(llint x, llint y, llint h) {
    file* f = malloc(sizeof(file));
    f->x = x;
    f->y = y;
    f->h = h;
    f->suiv = NULL;
    return f;
}

file* ajouter(file* f, llint x, llint y, llint h) {
    if (f == NULL) {
        return creer_file(x, y, h);
    }
    file* temp = f;
    while (temp->suiv != NULL && temp->suiv->h < h) {
        temp = temp->suiv;
    }
    file* temp2 = temp->suiv;
    temp->suiv = creer_file(x, y, h);
    temp->suiv->suiv = temp2;
    return f;
}

void afficher_matrice(bool** m) {
    printf("\n");
    for (llint i = 0; i < TAILLE; i++) {
        for (llint j = 0; j < TAILLE; j++) {
            if (m[i][j]) {
                printf("\033[00m.\033[00m");
            }
            else {
                printf("\033[46m.\033[00m");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void afficher_matrice_deja_vu(bool** m, bool** deja_vu) {
    printf("\n");
    for (llint i = 0; i < TAILLE; i++) {
        for (llint j = 0; j < TAILLE; j++) {
            if (m[i][j]) {
                if (deja_vu[i][j]) {
                    printf("\033[45m.\033[00m");
                }
                else {
                    printf("\033[00m.\033[00m");
                }
            }
            else {
                printf("\033[46m.\033[00m");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void afficher_file(file* f) {
    file* temp = f;
    while (temp != NULL) {
        printf("(%lld, %lld, %lld) -> ", temp->x, temp->y, temp->h);
        temp = temp->suiv;
    }
    printf("X\n");
}

bool dans_grille(llint x, llint y) {
    return (x >= 0 && y >= 0 && x < TAILLE && y < TAILLE);
}

llint a_star(bool** m) {
    llint** dist = malloc(TAILLE * sizeof(llint*));
    couple** pred = malloc(TAILLE * sizeof(couple*));
    bool** deja_vu = malloc(TAILLE * sizeof(bool*));
    for (llint i = 0; i < TAILLE; i++) {
        dist[i] = malloc(TAILLE * sizeof(llint));
        pred[i] = malloc(TAILLE * sizeof(couple));
        deja_vu[i] = malloc(TAILLE * sizeof(bool));
        for (llint j = 0; j < TAILLE; j++) {
            dist[i][j] = LLONG_MAX;
            pred[i][j].x = -1;
            pred[i][j].y = -1;
            deja_vu[i][j] = false;
        }
    }
    dist[0][0] = 0;
    pred[0][0].x = 0;
    pred[0][0].y = 0;
    llint posx[] = {-1, 0, 1, 0};
    llint posy[] = {0, 1, 0, -1};
    file* a_traiter = creer_file(0, 0, 0);
    while (a_traiter != NULL) {
        file* u = a_traiter;
        a_traiter = a_traiter->suiv;
        if ((u->x == TAILLE-1) && (u->y == TAILLE-1)) {
            // afficher_matrice_deja_vu(m, deja_vu);
            return u->h;
        }
        if (!deja_vu[u->y][u->x] && m[u->y][u->x]) {
            for (llint k = 0; k < 4; k++) {
                llint x = u->x + posx[k];
                llint y = u->y + posy[k];
                if (dans_grille(x, y)) {
                    if (dist[y][x] > dist[u->y][u->x]) {
                        dist[y][x] = dist[u->y][u->x] + 1;
                        pred[y][x].x = u->x;
                        pred[y][x].y = u->y;
                        if (!deja_vu[y][x]) {
                            a_traiter = ajouter(a_traiter, x, y, dist[y][x]);
                        }
                    }
                }
            }
            deja_vu[u->y][u->x] = true;
        }
        free(u);
    }
    // afficher_matrice_deja_vu(m, deja_vu);
    return -1;
}

bool** lire_fichier(FILE* f) {
    bool** memoire = malloc(TAILLE * sizeof(bool*));
    for (llint i = 0; i < TAILLE; i++) {
        memoire[i] = malloc(TAILLE * sizeof(bool));
        for (llint j = 0; j < TAILLE; j++) {
            memoire[i][j] = true;
        }
    }
    llint v1, v2;
    //while (fscanf(f, "%lld,%lld\n", &v1, &v2) == 2) {
    while (a_star(memoire) != -1) {
        fscanf(f, "%lld,%lld\n", &v1, &v2);
        memoire[v2][v1] = false;
        printf("%lld,%lld\n", v1, v2);
    }
    // afficher_matrice(memoire);
    return memoire;
}

llint main() {
    FILE* f = fopen("day18.txt", "r");
    bool** memoire = lire_fichier(f);
    fclose(f);
    return 0;
}