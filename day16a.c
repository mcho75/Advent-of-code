#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define HAUTEUR 141
#define LARGEUR 141

// 109504 : trop grand

typedef long long int llint;

struct couple {
    llint i;
    llint j;
};
typedef struct couple couple;

struct file {
    llint i;
    llint j;
    llint orient;
    llint h;
    struct file* suiv;
};
typedef struct file file;

file* creer_file(llint i, llint j, llint h, llint orient) {
    file* f = malloc(sizeof(file));
    f->i = i;
    f->j = j;
    f->orient = orient;
    f->h = h;
    f->suiv = NULL;
    return f;
}

file* ajouter(file* f, llint i, llint j, llint h, llint orient) {
    if (f == NULL) {
        return creer_file(i, j, h, orient);
    }
    file* temp = f;
    while (temp->suiv != NULL && temp->suiv->h < h) {
        temp = temp->suiv;
    }
    file* temp2 = temp->suiv;
    temp->suiv = creer_file(i, j, h, orient);
    temp->suiv->suiv = temp2;
    return f;
}

void afficher_file(file* f) {
    file* temp = f;
    while (temp != NULL) {
        printf("(%lld, %lld, %lld, %lld) -> ", temp->i, temp->j, temp->h, temp->orient);
        temp = temp->suiv;
    }
    printf("X\n");
}

void recuperer_chemin(couple** pred, llint ei, llint ej, llint si, llint sj) {
    bool** cases = malloc(HAUTEUR * sizeof(bool*));
    for (llint i = 0; i < HAUTEUR; i++) {
        cases[i] = malloc(LARGEUR * sizeof(bool));
        for (llint j = 0; j < LARGEUR; j++) {
            cases[i][j] = false;
        }
    }
    couple temp = pred[ei][ej];
    while (temp.i != si || temp.j != sj) {
        cases[temp.i][temp.j] = true;
        temp = pred[temp.i][temp.j];
    }
    afficher_grille(cases);
}

llint h(llint i, llint j, llint si, llint sj) {
    return 0;
    return abs(si-i) + abs(sj-j);
}

llint a_star(bool** grille, llint ei, llint ej, llint si, llint sj) {
    printf("Debut a* de (%lld, %lld) vers (%lld, %lld)\n", si, sj, ei, ej);
    llint** dist = malloc(HAUTEUR * sizeof(llint*));
    couple** pred = malloc(HAUTEUR * sizeof(couple*));
    bool** deja_vu = malloc(HAUTEUR * sizeof(bool*));
    for (llint i = 0; i < HAUTEUR; i++) {
        dist[i] = malloc(LARGEUR * sizeof(llint));
        pred[i] = malloc(LARGEUR * sizeof(couple));
        deja_vu[i] = malloc(LARGEUR * sizeof(bool));
        for (llint j = 0; j < LARGEUR; j++) {
            dist[i][j] = LLONG_MAX;
            pred[i][j].i = -1;
            pred[i][j].j = -1;
            deja_vu[i][j] = false;
        }
    }
    dist[si][sj] = 0;
    pred[si][sj].i = si;
    pred[si][sj].j = sj;
    // haut:0; droite:1; bas:2; gauche:3
    llint posi[] = {-1, 0, 1, 0};
    llint posj[] = {0, 1, 0, -1};
    file* a_traiter = creer_file(si, sj, 0, 1);
    while (a_traiter != NULL) {
        file* u = a_traiter;
        // printf("On sort (%lld, %lld) oriente %lld de poids %lld\n", u->i, u->j, u->orient, u->h);
        a_traiter = a_traiter->suiv;
        if ((u->i == ei) && (u->j == ej)) {
            recuperer_chemin(pred, ei, ej, si, sj);
            return u->h;
        }
        if (!deja_vu[u->i][u->j]) {
            for (llint k = 0; k < 4; k++) {
                llint i = u->i + posi[k];
                llint j = u->j + posj[k];
                if (grille[i][j]) {
                    if (dist[i][j] > dist[u->i][u->j]) {
                        dist[i][j] = dist[u->i][u->j] + 1;
                        if (u->orient != k) {
                            dist[i][j] += 1000;
                        }
                        pred[i][j].i = u->i;
                        pred[i][j].j = u->j;
                        if (!deja_vu[i][j]) {
                            a_traiter = ajouter(a_traiter, i, j, dist[i][j] + h(i, j, ei, ej), k);
                            // afficher_file(a_traiter);
                        }
                    }
                }
            }
            deja_vu[u->i][u->j] = true;
        }
        free(u);
    }
    return dist[si][sj];
}

bool** lire_fichier(FILE* f, llint* ei, llint* ej, llint* si, llint* sj) {
    char lu;
    bool** grille = malloc(HAUTEUR * sizeof(bool*));
    for (llint i = 0; i < HAUTEUR; i++) {
        grille[i] = malloc(LARGEUR * sizeof(bool));
        for (llint j = 0; j < LARGEUR; j++) {
            fscanf(f, "%c", &lu);
            grille[i][j] = (lu != '#');
            if (lu == 'E') {
                *ei = i;
                *ej = j;
            }
            if (lu == 'S') {
                *si = i;
                *sj = j;
            }
        }
        fscanf(f, "\n");
    }
    return grille;
}

void afficher_grille(bool** grille) {
    for (llint i = 0; i < HAUTEUR; i++) {
        for (llint j = 0; j < LARGEUR; j++) {
            if (grille[i][j]) {
                printf(".");
            }
            else {
                printf("#");
            }
        }
        printf("\n");
    }
}

llint main() {
    llint ei, ej, si, sj;
    FILE* f = fopen("day16.txt", "r");
    bool** grille = lire_fichier(f, &ei, &ej, &si, &sj);
    fclose(f);
    afficher_grille(grille);
    printf("TOTAL : %lld\n", a_star(grille, ei, ej, si, sj));
    return 0;
}