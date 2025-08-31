#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

typedef long long int llint;

struct maillon {
    llint valeur;
    llint nb_occurences;
    struct maillon* prec;
    struct maillon* suiv;
};
typedef struct maillon maillon;

maillon* creer(int val) {
    maillon* m = malloc(sizeof(maillon));
    m->valeur = val;
    m->nb_occurences = 1;
    m->prec = NULL;
    m->suiv = NULL;
    return m;
}

void ajouter(maillon* m, int val) {
    m->suiv = creer(val);
    m->suiv->prec = m;
}

void afficher(maillon* m) {
    maillon* actuel = m;
    while (actuel != NULL) {
        printf("%lld -> ", actuel->valeur);
        actuel = actuel->suiv;
    }
    printf("X\n");
}

void transformer(maillon* pierres) {
    maillon* actuel = pierres;
    maillon* temp;
    llint v_gauche, v_droite, nb_chiffres;
    while (actuel != NULL) {
        nb_chiffres =  (llint)(log10(actuel->valeur)) + 1;
        if (actuel->valeur == 0) {
            actuel->valeur = 1;
            actuel = actuel->suiv;
        }
        else if (nb_chiffres % 2 == 0) {
            temp = actuel->suiv;
            v_gauche = actuel->valeur / pow(10, nb_chiffres/2);
            v_droite = actuel->valeur - (v_gauche * pow(10, nb_chiffres/2));
            actuel->valeur = v_gauche;
            ajouter(actuel, v_droite);
            actuel->suiv->nb_occurences = actuel->nb_occurences;
            actuel->suiv->suiv = temp;
            if (temp != NULL) {
                temp->prec = actuel->suiv;
            }
            actuel = actuel->suiv->suiv;
        }
        else {
            actuel->valeur = actuel->valeur * 2024;
            actuel = actuel->suiv;
        }
    }
}

void enlever_doublons(maillon* m) {
    maillon* actuel = m;
    maillon* parcours;
    maillon* temp;
    while (actuel != NULL) {
        parcours = actuel;
        while (parcours->suiv != NULL) {
            if (parcours->suiv->valeur == actuel->valeur) {
                actuel->nb_occurences += parcours->suiv->nb_occurences;
                temp = parcours->suiv;
                parcours->suiv = parcours->suiv->suiv;
                free(temp);
            }
            else {
                parcours = parcours->suiv;
            }
        }
        actuel = actuel->suiv;
    }
}

llint compter(maillon* m) {
    maillon* actuel = m;
    llint nb = 0;
    while(actuel != NULL) {
        nb += actuel->nb_occurences;
        actuel = actuel->suiv;
    }
    return nb;
}

maillon* lire_fichier(FILE* f) {
    int p;
    fscanf(f, "%d ", &p);
    maillon* pierres = creer(p);
    maillon* actuel = pierres;
    while (fscanf(f, "%d ", &p) == 1) {
        ajouter(actuel, p);
        actuel = actuel->suiv;
    }
    return pierres;
}

int main() {
    FILE* f = fopen("day11.txt", "r");
    maillon* pierres = lire_fichier(f);
    fclose(f);
    // afficher(pierres);
    for (int i = 0; i < 75; i++) {
        transformer(pierres);
        enlever_doublons(pierres);
        // afficher(pierres);
    }
    printf("TOTAL : %lld\n", compter(pierres));
    return 0;
}