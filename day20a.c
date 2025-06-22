#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define TAILLE 15
#define A_SAUVER 64

typedef long long int llint;

struct couple {
    llint i;
    llint j;
};
typedef struct couple couple;

struct file {
    llint i;
    llint j;
    llint h;
    bool cheat1;
    bool cheat2;
    struct file* suiv;
};
typedef struct file file;

file* creer_file(llint i, llint j, llint h, bool cheat1, bool cheat2) {
    file* f = malloc(sizeof(file));
    f->i = i;
    f->j = j;
    f->h = h;
    f->cheat1 = cheat1;
    f->cheat2 = cheat2;
    f->suiv = NULL;
    return f;
}

file* ajouter(file* f, llint i, llint j, llint h, bool cheat1, bool cheat2) {
    if (f == NULL) {
        return creer_file(i, j, h, cheat1, cheat2);
    }
    file* temp = f;
    while (temp->suiv != NULL && temp->suiv->h < h) {
        temp = temp->suiv;
    }
    file* temp2 = temp->suiv;
    temp->suiv = creer_file(i, j, h, cheat1, cheat2);
    temp->suiv->suiv = temp2;
    return f;
}

void afficher_grille(bool** grille) {
    for (llint i = 0; i < TAILLE; i++) {
        for (llint j = 0; j < TAILLE; j++) {
            if (grille[i][j]) {
                printf("\033[00m.\033[00m");
            }
            else {
                printf("\033[46m.\033[00m");
            }
        }
        printf("\n");
    }
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

llint plus_court_chemin(bool** m) {
    llint total = 0;
    for (llint i = 0; i < TAILLE; i++) {
        for (llint j = 0; j < TAILLE; j++) {
            total += m[i][j];
        }
    }
    return total - 1;
}

bool dans_grille(llint i, llint j) {
    return (i >= 0 && j >= 0 && i < TAILLE && j < TAILLE);
}

llint a_star(bool** m, llint si, llint sj, llint ei, llint ej) {
    llint** dist = malloc(TAILLE * sizeof(llint*));
    couple** pred = malloc(TAILLE * sizeof(couple*));
    bool** deja_vu = malloc(TAILLE * sizeof(bool*));
    for (llint i = 0; i < TAILLE; i++) {
        dist[i] = malloc(TAILLE * sizeof(llint));
        pred[i] = malloc(TAILLE * sizeof(couple));
        deja_vu[i] = malloc(TAILLE * sizeof(bool));
        for (llint j = 0; j < TAILLE; j++) {
            dist[i][j] = LLONG_MAX;
            pred[i][j].i = -1;
            pred[i][j].j = -1;
            deja_vu[i][j] = false;
        }
    }
    dist[si][sj] = 0;
    pred[si][sj].i = si;
    pred[si][sj].j = sj;
    llint posi[] = {-1, 0, 1, 0};
    llint posj[] = {0, 1, 0, -1};
    file* a_traiter = creer_file(si, sj, 0, false, false);
    llint chemin = plus_court_chemin(m);
    llint nb = 0;
    while (a_traiter != NULL) {
        file* u = a_traiter;
        a_traiter = a_traiter->suiv;
        if ((u->i == ei) && (u->j == ej)) {
            // recuperer_chemin(pred, TAILLE, TAILLE);
            // afficher_matrice_deja_vu(m, deja_vu);
            printf("Atteint avec %lld\n", u->h);
            if (u->h <= chemin - A_SAUVER) {
                nb++;
            }
        }
        else if (!deja_vu[u->i][u->j]) {
            for (llint k = 0; k < 4; k++) {
                llint i = u->i + posi[k];
                llint j = u->j + posj[k];
                if (dans_grille(i, j)) {
                    if (m[u->i][u->j]) {
                        if (dist[i][j] > dist[u->i][u->j]) {
                            dist[i][j] = dist[u->i][u->j] + 1;
                            pred[i][j].i = u->i;
                            pred[i][j].j = u->j;
                            if (!deja_vu[i][j]) {
                                a_traiter = ajouter(a_traiter, i, j, dist[i][j], u->cheat1, u->cheat2);
                            }
                        }
                    }
                    else if (!u->cheat1) {
                        if (dist[i][j] > dist[u->i][u->j]) {
                            dist[i][j] = dist[u->i][u->j] + 1;
                            pred[i][j].i = u->i;
                            pred[i][j].j = u->j;
                            if (!deja_vu[i][j]) {
                                a_traiter = ajouter(a_traiter, i, j, dist[i][j], true, false);
                            }
                        }
                    }
                    else if (!u->cheat2) {
                        if (dist[i][j] > dist[u->i][u->j]) {
                            dist[i][j] = dist[u->i][u->j] + 1;
                            pred[i][j].i = u->i;
                            pred[i][j].j = u->j;
                            if (!deja_vu[i][j]) {
                                a_traiter = ajouter(a_traiter, i, j, dist[i][j], true, true);
                            }
                        }
                    }
                }
            }
            deja_vu[u->i][u->j] = true;
        }
        free(u);
    }
    afficher_matrice_deja_vu(m, deja_vu);
    return nb;
}

bool** lire_fichier(FILE* f, llint* si, llint* sj, llint* ei, llint* ej) {
    char lu;
    bool** grille = malloc(TAILLE * sizeof(bool*));
    for (llint i = 0; i < TAILLE; i++) {
        grille[i] = malloc(TAILLE * sizeof(bool));
        for (llint j = 0; j < TAILLE; j++) {
            fscanf(f, "%c", &lu);
            grille[i][j] = (lu != '#');
            if (lu == 'S') {
                *si = i;
                *sj = j;
            }
            if (lu == 'E') {
                *ei = i;
                *ej = j;
            }
        }
        fscanf(f, "\n");
    }
    return grille;
}

llint main() {
    FILE* f = fopen("day20.txt", "r");
    llint si, sj, ei, ej;
    bool** grille = lire_fichier(f, &si, &sj, &ei, &ej);
    printf("%lld\n", plus_court_chemin(grille));
    printf("%lld\n", a_star(grille, si, sj, ei, ej));
    // afficher_grille(grille);
    fclose(f);
    return 0;
}