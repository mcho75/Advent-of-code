#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define NB_SERVIETTES 447

// 0:w    1:u    2:b    3:r    4:g

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
    a->existe = false;
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

bool backtracking(arbre* a, arbre* r, bool* commencer_par, char* motif, int pos, int taille) {
    int lettre = lettre_vers_int(motif[pos]);
    // printf("Recherche depuis %d\n", pos);
    if (taille > 8) {
        return false;
    }
    if (taille == 1 && !commencer_par[pos]) {
        return false;
    }
    if (motif[pos] == '\0') {
        return (a->existe);
    }
    if (a->fils[lettre] == NULL) {
        return false;
    }
    if (a->fils[lettre]->existe) {
        if (backtracking(r, r, commencer_par, motif, pos+1, 1)) {
            return true;
        }
        commencer_par[pos+1] = false;
        return backtracking(a->fils[lettre], r, commencer_par, motif, pos+1, taille+1);
    }
    return backtracking(a->fils[lettre], r, commencer_par, motif, pos+1, taille+1);
}

int parcours_motifs(FILE* f, arbre* a) {
    int peut_faire = 0;
    char lu[100];
    bool* commencer_par = malloc(100 * sizeof(bool));
    while (fscanf(f, "%s\n", lu) == 1) {
        // printf("Recherche pour %s\n", lu);
        for (int i = 0; i < 100; i++) {
            commencer_par[i] = true;
        }
        if (backtracking(a, a, commencer_par, lu, 0, 1)) {
            peut_faire++;
        }
        else {
            printf("%s\n", lu);
        }
    }
    return peut_faire;
}

int main() {
    FILE* f = fopen("day19.txt", "r");
    arbre* a = serviettes_dispo(f);
    printf("%d\n", parcours_motifs(f, a));
    fclose(f);
    return 0;
}

// 329 : too low