#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

struct maillon {
    int id_obj;
    int taille;
    struct maillon* prec;
    struct maillon* suiv;
    struct maillon* vide_prec;
    struct maillon* vide_suiv;
};
typedef struct maillon maillon;

maillon* allouer(int id_obj, int taille) {
    maillon* liste = malloc(sizeof(maillon));
    liste->id_obj = id_obj;
    liste->taille = taille;
    liste->prec = NULL;
    liste->suiv = NULL;
    return liste;
}

maillon* ajouter(maillon* liste, int id_obj, int taille) {
    maillon* nouveau = allouer(id_obj, taille);
    liste->suiv = nouveau;
    nouveau->prec = liste;
    return nouveau;
}

void afficher(maillon* liste) {
    if (liste == NULL) {
        printf("X\n");
        return;
    }
    printf("(%d %d) -> ", liste->id_obj, liste->taille);
    afficher(liste->suiv);
}

void afficher_txt(maillon* liste) {
    if (liste == NULL) {
        printf("\n");
        return;
    }
    for (int i = 0; i < liste->taille; i++) {
        if (liste->id_obj == -1) {
            printf(".");
        }
        else {
            printf("%d", liste->id_obj);
        }
    }
    afficher_txt(liste->suiv);
}

void essayer_de_placer(maillon* a_placer, maillon* debut, maillon* espace_vide, bool* deja_vu) {
    printf("On essaie de placer (%d %d) a la place de (%d %d)\n",
            a_placer->id_obj, a_placer->taille, espace_vide->id_obj, espace_vide->taille);
    if (a_placer == NULL) {
        // On a fini de parcourir la liste des elements a placer
        printf("On a fini le parcours\n");
        return;
    }
    if (deja_vu[a_placer->id_obj] || (espace_vide->prec == a_placer)) {
        // On recompense depuis le debut avec le suivant
        if (deja_vu[a_placer->id_obj]) {
            printf("On a deja vu (%d %d)\n", a_placer->id_obj, a_placer->taille);
        }
        else {
            printf("Impossible de placer (%d %d)\n", a_placer->id_obj, a_placer->taille);
        }
        deja_vu[a_placer->id_obj] = true;
        if (a_placer->prec == NULL) {
            printf("On a fini le parcours\n");
            return;
        }
        essayer_de_placer(a_placer->prec->prec, debut, debut, deja_vu);
        return;
    }
    if (a_placer->taille <= espace_vide->taille) {
        // On place le maillon a cet endroit
        printf("On a place (%d %d) a la place de (%d %d)\n",
                a_placer->id_obj, a_placer->taille, espace_vide->id_obj, espace_vide->taille);
        maillon* temp = espace_vide->suiv;
        ajouter(espace_vide, a_placer->id_obj, a_placer->taille);
        ajouter(espace_vide->suiv, -1, espace_vide->taille - a_placer->taille);
        espace_vide->taille = 0;
        espace_vide->suiv->suiv->suiv = temp;
        temp->prec = espace_vide->suiv->suiv;
        deja_vu[a_placer->id_obj] = true;
        a_placer->id_obj = -1;
        // printf("On obtient : ");
        // afficher_txt(debut->prec);
        essayer_de_placer(a_placer->prec->prec, debut, debut, deja_vu);
    }
    else {
        // On checke l'emplacement libre suivant
        essayer_de_placer(a_placer, debut, espace_vide->suiv->suiv, deja_vu);
    }
}

void essayer_de_placer_iter(maillon* debut, maillon* fin, bool* deja_vu) {
    maillon* a_placer = fin;
    while (a_placer->id_obj != 0) {
        // printf("On essaie de placer (%d %d)\n", a_placer->id_obj, a_placer->taille);
        maillon* espace_vide_actuel = debut->suiv;
        bool fin_de_boucle = false;
        while (!fin_de_boucle) {
            // printf("On essaie de placer (%d %d) a la place de (%d %d)\n",
            //         a_placer->id_obj, a_placer->taille, espace_vide_actuel->id_obj, espace_vide_actuel->taille);
            if (deja_vu[a_placer->id_obj]) {
                fin_de_boucle = true;
            }
            else if (espace_vide_actuel->taille >= a_placer->taille) {
                // printf("On peut mettre (%d %d) a la place de (%d %d)\n",
                //        a_placer->id_obj, a_placer->taille, espace_vide_actuel->id_obj, espace_vide_actuel->taille);
                maillon* temp = espace_vide_actuel->suiv;
                ajouter(espace_vide_actuel, a_placer->id_obj, a_placer->taille);
                ajouter(espace_vide_actuel->suiv, -1, espace_vide_actuel->taille - a_placer->taille);
                espace_vide_actuel->suiv->suiv->suiv = temp;
                espace_vide_actuel->taille = 0;
                temp->prec = espace_vide_actuel->suiv->suiv;
                deja_vu[a_placer->id_obj] = true;
                a_placer->id_obj = -1;
                fin_de_boucle = true;
                // afficher_txt(debut);
            }
            else if (espace_vide_actuel->suiv == a_placer) {
                deja_vu[a_placer->id_obj] = true;
                fin_de_boucle = true;
            }
            espace_vide_actuel = espace_vide_actuel->suiv->suiv;
        }
        if (a_placer->prec != NULL) {
            a_placer = a_placer->prec->prec;
        }
    }
}

void lire_fichier(FILE* f) {
    char c = 'a';
    int id_obj = 1;
    bool est_vide = true;
    fscanf(f, "%c", &c);
    maillon* memoire = allouer(0, c-48);
    maillon* actuel = memoire;
    while (c != '\n') {
        fscanf(f, "%c", &c);
        if (est_vide) {
            actuel = ajouter(actuel, -1, c-48);
        }
        else {
            actuel = ajouter(actuel, id_obj, c-48);
            id_obj++;
        }
        est_vide = !est_vide;
    }
    actuel = actuel->prec;
    free(actuel->suiv);
    actuel->suiv = NULL;
    // afficher(memoire);
    bool* deja_vu = malloc(10000 * sizeof(bool));
    for (int i = 0; i < 10000; i++) {
        deja_vu[i] = false;
    }
    essayer_de_placer_iter(memoire, actuel, deja_vu);
    // afficher_txt(memoire);
    long long int total = 0;
    int pos = 0;
    actuel = memoire;
    while (actuel != NULL) {
        if (actuel->id_obj == -1) {
            pos += actuel->taille;
        }
        else {
            for (int i = 0; i < actuel->taille; i++) {
                // printf("%d + %d * %d\n", total, actuel->id_obj, pos);
                total += actuel->id_obj * pos;
                pos++;
            }
        }
        actuel = actuel->suiv;
    }
    printf("TOTAL : %lld\n", total);
}

int main() {
    FILE* f;
    f = fopen("day9.txt", "r");
    lire_fichier(f);
    fclose(f);
}