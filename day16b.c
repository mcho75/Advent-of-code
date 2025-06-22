#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define HAUTEUR 141
#define LARGEUR 141

// ]530, 540[

typedef long long int llint;

struct couple {
    llint i;
    llint j;
    llint val;
    struct couple* suiv;
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

couple* ajouter_maillon(couple* liste, int i, int j, llint val) {
    couple* nouveau = malloc(sizeof(couple));
    nouveau->i = i;
    nouveau->j = j;
    nouveau->val = val;
    nouveau->suiv = liste;
    return nouveau;
}

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

void afficher_couples(couple* c) {
    couple* temp = c;
    while (temp != NULL) {
        printf("(%lld, %lld) -> ", temp->i, temp->j);
        temp = temp->suiv;
    }
    printf("X\n");
}

void afficher_file(file* f) {
    file* temp = f;
    while (temp != NULL) {
        printf("(%lld, %lld, %lld, %lld) -> ", temp->i, temp->j, temp->h, temp->orient);
        temp = temp->suiv;
    }
    printf("X\n");
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

llint h(llint i, llint j, llint si, llint sj) {
    return 0;
    return abs(si-i) + abs(sj-j);
}

llint decompte_cases(couple*** pred, bool** cases, llint ei, llint ej, llint si, llint sj) {
    // printf("Decompte depuis (%lld, %lld) : ", ei, ej);
    if (si == ei && sj == ej) {
        return 1;
    }
    llint total = 1;
    couple* temp = pred[ei][ej];
    while (temp != NULL) {
        if (!cases[temp->i][temp->j]) {
            cases[temp->i][temp->j] = true;
            total += decompte_cases(pred, cases, temp->i, temp->j, si, sj);
        }
        temp = temp->suiv;
    }
    return total;
}

llint decompte_cases2(bool** cases) {
    llint total = 0;
    for (llint i = 0; i < HAUTEUR; i++) {
        for (llint j = 0; j < LARGEUR; j++) {
            if (cases[i][j]) {
                total++;
            }
        }
    }
    return total;
}

bool dans_pred(couple* pred, llint valeur) {
    couple* temp = pred;
    while (temp != NULL) {
        if (temp->val = valeur) {
            return true;
        }
        temp = temp->suiv;
    }
    return false;
}

llint a_star(bool** grille, llint ei, llint ej, llint si, llint sj) {
    printf("Debut a* de (%lld, %lld) vers (%lld, %lld)\n", si, sj, ei, ej);
    llint** dist = malloc(HAUTEUR * sizeof(llint*));
    couple*** pred = malloc(HAUTEUR * sizeof(couple**));
    bool** deja_vu = malloc(HAUTEUR * sizeof(bool*));
    for (llint i = 0; i < HAUTEUR; i++) {
        dist[i] = malloc(LARGEUR * sizeof(llint));
        pred[i] = malloc(LARGEUR * sizeof(couple*));
        deja_vu[i] = malloc(LARGEUR * sizeof(bool));
        for (llint j = 0; j < LARGEUR; j++) {
            dist[i][j] = LLONG_MAX;
            pred[i][j] = NULL;
            deja_vu[i][j] = false;
        }
    }
    dist[si][sj] = 0;
    pred[si][sj] = ajouter_maillon(pred[si][sj], si, sj, -1);
    // haut:0; droite:1; bas:2; gauche:3
    llint posi[] = {-1, 0, 1, 0};
    llint posj[] = {0, 1, 0, -1};
    file* a_traiter = creer_file(si, sj, 0, 1);
    while (a_traiter != NULL) {
        file* u = a_traiter;
        // printf("On sort (%lld, %lld) oriente %lld de poids %lld\n", u->i, u->j, u->orient, u->h);
        if (!deja_vu[u->i][u->j]) {
            for (llint k = 0; k < 4; k++) {
                llint i = u->i + posi[k];
                llint j = u->j + posj[k];
                if (grille[i][j]) {
                    llint valeur = dist[u->i][u->j] + 1;
                    if (u->orient != k) {
                        valeur += 1000;
                    }
                    if (dist[i][j] >= valeur || dist[i][j] == valeur-1000) {
                        if (dist[i][j] == valeur || (dans_pred(pred[i][j], valeur-1000) && ((i != ei) || (j != ej)))) {
                            // printf("Regroupement en (%lld, %lld)\n", i, j);
                            pred[i][j] = ajouter_maillon(pred[i][j], u->i, u->j, valeur-1000);
                        }
                        else if (dist[i][j] > valeur) {
                            pred[i][j] = ajouter_maillon(NULL, u->i, u->j, valeur);
                            dist[i][j] = valeur;
                        }
                        if (!deja_vu[i][j]) {
                            a_traiter = ajouter(a_traiter, i, j, dist[i][j], k);
                            // afficher_file(a_traiter);
                        }
                    }
                }
            }
            deja_vu[u->i][u->j] = true;
        }
        a_traiter = a_traiter->suiv;
        free(u);
    }
    bool** cases = malloc(HAUTEUR * sizeof(bool*));
    for (llint i = 0; i < HAUTEUR; i++) {
        cases[i] = malloc(LARGEUR * sizeof(bool));
        for (llint j = 0; j < LARGEUR; j++) {
            cases[i][j] = false;
            // printf("pred[%lld][%lld] : ", i, j);
            // afficher_couples(pred[i][j]);
        }
    }
    cases[ei][ej] = true;
    llint decompte = decompte_cases(pred, cases, ei, ej, si, sj);
    llint decompte2 = decompte_cases2(cases);
    afficher_grille(cases);
    return decompte2;
}

bool atteint(bool** grille, bool** cases, llint ei, llint ej, llint si, llint sj, llint orient, llint d_min) {
    if (ei == si && ej == sj) {
        return d_min == 0;
    }
    if (!grille[si][sj] || d_min <= 0) {
        return false;
    }
    printf("Recherche depuis (%lld %lld) avec d = %lld\n", si, sj, d_min);
    bool a_atteint = false;
    llint posi[] = {-1, 0, 1, 0};
    llint posj[] = {0, 1, 0, -1};
    for (llint k = 0; k < 4; k++) {
        llint i = posi[k];
        llint j = posj[k];
        if (orient == k) {
            a_atteint = a_atteint || atteint(grille, cases, ei, ej, si+i, sj+j, k, d_min-1);
        }
        else {
            a_atteint = a_atteint || atteint(grille, cases, ei, ej, si+i, sj+j, k, d_min-1001);
        }
    }
    cases[si][sj] = true;
    return a_atteint;
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

llint main() {
    llint ei, ej, si, sj;
    FILE* f = fopen("day16.txt", "r");
    bool** grille = lire_fichier(f, &ei, &ej, &si, &sj);
    fclose(f);
    afficher_grille(grille);
    bool** cases = malloc(HAUTEUR * sizeof(bool*));
    for (llint i = 0; i < LARGEUR; i++) {
        cases[i] = malloc(LARGEUR * sizeof(bool));
        for (llint j = 0; j < LARGEUR; j++) {
            cases[i][j] = false;
        }
    }
    // atteint(grille, cases, ei, ej, si, sj, 1, 11048);
    afficher_grille(cases);
    printf("TOTAL : %lld\n", a_star(grille, ei, ej, si, sj));
    return 0;
}