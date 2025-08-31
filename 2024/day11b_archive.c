#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define NB_SOMMETS 1000

typedef long long int llint;

struct triplet {
    llint n;
    int dist;
    int nb_occ;
    struct triplet* suiv;
};
typedef struct triplet triplet;

int nb_chiffres(llint n) {
    return (int)(log10(n)) + 1;
}

void afficher_triplets(triplet* t) {
    while (t != NULL) {
        printf("(%lld %d %d) ", t->n, t->dist, t->nb_occ);
        t = t->suiv;
    }
    printf("\n");
}

triplet* atteindre_1_ou_3_chiffres(triplet* actuel, bool commence) {
    if (actuel == NULL) {
        return NULL;
    }
    llint v_droite, v_gauche;
    triplet* temp;
    llint n = actuel->n;
    if ((n == 0) && commence) {
        actuel->n = 1;
    }
    if (((n < 10) || ((n > 99) && (n < 1000))) && !commence) {
        // printf("Cas 1 pour %lld\n", n);
        actuel = actuel->suiv;
    }
    else if (nb_chiffres(n) % 2 == 0) {
        // printf("Cas 2 pour %lld\n", n);
        v_gauche = n / pow(10, nb_chiffres(n)/2);
        v_droite = n - (v_gauche * pow(10, nb_chiffres(n)/2));
        // printf("%lld donne %lld %lld\n", n, v_gauche, v_droite);
        actuel->n = v_gauche;
        actuel->dist++;
        temp = actuel->suiv;
        actuel->suiv = malloc(sizeof(triplet));
        actuel->suiv->n = v_droite;
        actuel->suiv->dist = actuel->dist;
        actuel->suiv->suiv = temp;
    }
    else {
        // printf("Cas 3 pour %lld\n", n);
        actuel->n = 2024 * n;
        actuel->dist++;
    }
    return atteindre_1_ou_3_chiffres(actuel, false);
}

triplet* tout_atteignable(triplet* actuel, int pas_restants) {
    if (actuel == NULL) {
        return NULL;
    }
    if (actuel->dist == pas_restants) {
        return actuel;
    }
    llint v_gauche, v_droite;
    triplet* temp;
    int n = actuel->n;
    if (n == 0) {
        // printf("Cas 1 pour %lld\n", n);
        actuel->n = 1;
    }
    else if (nb_chiffres(n) % 2 == 0) {
        // printf("Cas 2 pour %lld\n", n);
        v_gauche = n / pow(10, nb_chiffres(n)/2);
        v_droite = n - (v_gauche * pow(10, nb_chiffres(n)/2));
        // printf("%lld donne %lld %lld\n", n, v_gauche, v_droite);
        actuel->n = v_gauche;
        actuel->dist++;
        temp = actuel->suiv;
        actuel->suiv = malloc(sizeof(triplet));
        actuel->suiv->n = v_droite;
        actuel->suiv->dist = actuel->dist;
        actuel->suiv->suiv = temp;
    }
    else {
        // printf("Cas 3 pour %lld\n", n);
        actuel->n = 2024 * n;
        actuel->dist++;
    }
    tout_atteignable(actuel, pas_restants);
}

void enlever_doublons(triplet* t) {
    triplet* actuel = t;
    triplet* parcours;
    triplet* temp;
    while (actuel != NULL) {
        actuel->nb_occ = 1;
        parcours = actuel;
        while (parcours->suiv != NULL) {
            if ((parcours->suiv->n == actuel->n) && (parcours->suiv->dist == actuel->dist)) {
                temp = parcours->suiv;
                parcours->suiv = parcours->suiv->suiv;
                actuel->nb_occ++;
                free(temp);
            }
            else {
                parcours = parcours->suiv;
            }
        }
        actuel = actuel->suiv;
    }
}

llint parcours_graphe(llint n_actuel, int pas_restants, triplet** liste) {
    // printf("Parcours depuis %d avec %d restants\n", n_actuel, pas_restants);
    if (pas_restants < 0) {
        return 1;
    }
    llint total = 0;
    triplet* voisin = malloc(sizeof(triplet));
    voisin->n = n_actuel;
    voisin->dist = 0;
    voisin->suiv = NULL;
    if (n_actuel < 1000) {
        voisin = liste[n_actuel];
    }
    else {
        atteindre_1_ou_3_chiffres(voisin, false);
        enlever_doublons(voisin);
    }
    // afficher_triplets(voisin);
    triplet* temp = voisin;
    bool possible = true;
    while (temp != NULL) {
        if (pas_restants - temp->dist <= 0) {
            possible = false;
        }
        temp = temp->suiv;
    }
    if (possible) {
        while (voisin != NULL) {
            total = total + (voisin->nb_occ * parcours_graphe(voisin->n, pas_restants-voisin->dist, liste));
            voisin = voisin->suiv;
        }
    }
    else {
        // printf("Impossible de continuer depuis %d avec %d pas\n", n_actuel, pas_restants);
        voisin->n = n_actuel;
        voisin->dist = 0;
        voisin->suiv = NULL;
        triplet* restants = tout_atteignable(voisin, pas_restants);
        while (restants != NULL) {
            total++;
            restants = restants->suiv;
        }
        // afficher_triplets(restants);
    }
    return total;
}

int main() {
    triplet* t;
    int liste_pierres[] = {9694820, 93, 54276, 1304, 314, 664481, 0, 4};
    triplet** liste_triplets = malloc(NB_SOMMETS * sizeof(triplet*));
    for (int i = 0; i < NB_SOMMETS; i++) {
        t = malloc(sizeof(triplet));
        liste_triplets[i] = t;
        t->n = i;
        t->dist = 1;
        t->suiv = NULL;
        atteindre_1_ou_3_chiffres(t, true);
        enlever_doublons(t);
    }
    llint total = 0;
    for (int i = 0; i < 8; i++) {
        total = total + parcours_graphe(liste_pierres[i], 25, liste_triplets);
    }
    return 0;
}