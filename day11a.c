#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

struct maillon {
    long long int valeur;
    struct maillon* prec;
    struct maillon* suiv;
};
typedef struct maillon maillon;

maillon* creer(int val) {
    maillon* m = malloc(sizeof(maillon));
    m->valeur = val;
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
    long long int v_gauche, v_droite, nb_chiffres;
    while (actuel != NULL) {
        nb_chiffres =  (long long int)(log10(actuel->valeur)) + 1;
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

int compter(maillon* m) {
    maillon* actuel = m;
    int nb = 0;
    while(actuel != NULL) {
        nb++;
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
    afficher(pierres);
    for (int i = 0; i < 25; i++) {
        transformer(pierres);
        // afficher(pierres);
    }
    printf("TOTAL : %d\n", compter(pierres));
    return 0;
}