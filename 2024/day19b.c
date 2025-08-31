#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define NB_SERVIETTES 447

// 0:w    1:u    2:b    3:r    4:g

typedef long long int llint;

struct arbre {
    bool existe;
    struct arbre** fils;
};
typedef struct arbre arbre;

int lettre_vers_int(char lettre) {
    if (lettre == 'w') return 0;
    if (lettre == 'u') return 1;
    if (lettre == 'b') return 2;
    if (lettre == 'r') return 3;
    return 4;
}

arbre* arbre_vide() {
    arbre* a = malloc(sizeof(arbre));
    a->existe = true;
    a->fils = malloc(5 * sizeof(arbre*));
    for (int i = 0; i < 5; i++) {
        a->fils[i] = NULL;
    }
    return a;
}

arbre* ajouter(arbre* a, char* motif) {
    // retourne le noeud ajoute (si ajoute)
    char lettre = motif[0];
    int i = 0;
    arbre* actuel = a;
    while (lettre != ',') {
        int valeur = lettre_vers_int(lettre);
        if (actuel->fils[valeur] == NULL) {
            actuel->fils[valeur] = arbre_vide();
            actuel->fils[valeur]->existe = false;
        }
        actuel = actuel->fils[valeur];
        i++;
        lettre = motif[i];
    }
    actuel->existe = true;
    return actuel;
}

arbre* serviettes_dispo(FILE* f) {
    arbre* a = arbre_vide();
    char lu[10];
    for (int i = 0; i < NB_SERVIETTES; i++) {
        fscanf(f, "%s, ", lu);
        // printf("%s\n", lu);
        ajouter(a, lu);
    }
    return a;
}

char* concat(char lettre, char* chaine) {
    char* nouveau = malloc(100 * sizeof(char));
    int i;
    for (i = 0; chaine[i] != '\0'; i++) {
        nouveau[i] = chaine[i];
    }
    nouveau[i] = lettre;
    return nouveau;
}

void afficher_contenu_arbre(arbre* a, char* acc) {
    if (a == NULL) {
        return;
    }
    if (a->existe) {
        printf("%s\n", acc);
    }
    char lettres[] = {'w','u','b','r','g'};
    for (int i = 0; i < 5; i++) {
        // printf("Depuis %s : %c\n", acc, lettres[i]);
        afficher_contenu_arbre(a->fils[i], concat(lettres[i], acc));
    }
}

llint backtracking(arbre* a, arbre* r, bool* commencer_par, llint* combien, char* motif, int pos, int taille) {
    int lettre = lettre_vers_int(motif[pos]);
    llint total;
    // printf("Recherche depuis %d\n", pos);
    if (taille > 8) {
        return 0;
    }
    if (taille == 1 && !commencer_par[pos]) {
        return 0;
    }
    if (motif[pos] == '\0') {
        return (a->existe);
    }
    if (a->fils[lettre] == NULL) {
        return 0;
    }
    if (a->fils[lettre]->existe) {
        if (combien[pos+1] > 0) {
            total = combien[pos+1];
        }
        else {
            total = backtracking(r, r, commencer_par, combien, motif, pos+1, 1);
            combien[pos+1] = total;
        }
        if (total == 0) {
            commencer_par[pos+1] = false;
        }
        return total + backtracking(a->fils[lettre], r, commencer_par, combien, motif, pos+1, taille+1);
    }
    return backtracking(a->fils[lettre], r, commencer_par, combien, motif, pos+1, taille+1);
}

llint parcours_motifs(FILE* f, arbre* a) {
    char lu[100];
    bool* commencer_par = malloc(100 * sizeof(bool));
    llint total = 0;
    llint valeur;
    llint* combien = malloc(100 * sizeof(llint));
    while (fscanf(f, "%s\n", lu) == 1) {
        for (int i = 0; i < 100; i++) {
            commencer_par[i] = true;
            combien[i] = 0;
        }
        valeur = backtracking(a, a, commencer_par, combien, lu, 0, 1);
        printf("%s : %lld\n", lu, valeur);
        total += valeur;
    }
    return total;
}

int main() {
    FILE* f = fopen("day19.txt", "r");
    arbre* a = serviettes_dispo(f);
    char* chaine = malloc(100 * sizeof(char));
    chaine[0] = '\0';
    afficher_contenu_arbre(a, chaine);
    printf("%lld\n", parcours_motifs(f, a)/2);
    fclose(f);
    return 0;
}

// 329 : too low