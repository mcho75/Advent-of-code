#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define N 702     // nombre de valeurs
#define P 263     // longueur du pattern
#define T 17576   // pour coder les ABC

struct pointeur {
    int position;   // position dans le pattern
    int ecart;      // distance au premier __Z
    int prochain;   // __Z suivant
};
typedef struct pointeur pointeur;

int convertir(char i, char j, char k) {
    return ((int)i-65)*26*26 + ((int)j-65)*26 + ((int)k-65);
}

void trouver_prochain(pointeur* p, int** directions, int* leftright, int val, int pos) {
    int suivant = val;
    p->position = pos;
    p->prochain = -1;
    for (int k = 1; p->prochain == -1; k++) {
        //if (val == 834 && pos == 60) printf("%d -> %d\n", suivant, directions[suivant][leftright[(pos+k)%P]]);
        suivant = directions[suivant][leftright[(pos+k)%P]];
        if (suivant == -1) {
            p->ecart = -1;
            p->prochain = -2;
        }
        else if (suivant % 26 == 25) {
            p->ecart = k;
            p->prochain = suivant;
        }
    }
    //if (p.prochain == 11335) printf("%d : %d %d %d\n", val, pos, p.ecart, p.prochain);
}

void lire_fichier(FILE* f, int* association, int* leftright, int** directions) {
    char c1, c2, c3, c4, c5, c6, c7, c8, c9;
    for (int k = 0; k < P; k++) {
        fscanf(f, "%c", &c1);
        if (c1 == 'L') leftright[k] = 0;
        if (c1 == 'R') leftright[k] = 1;
        printf("%d", leftright[k]);
    }
    printf("\n");
    fscanf(f, "\n\n");
    // n = k*(26*26)+i*26+j, n%26, (n/26)%26, ((n/26)/26)%26
    for (int k = 0; k < N; k++) {
        fscanf(f, "%c%c%c = (%c%c%c, %c%c%c)\n", &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9);
        //association[k] = convertir(c1, c2, c3);
        directions[convertir(c1, c2, c3)][0] = convertir(c4, c5, c6);
        directions[convertir(c1, c2, c3)][1] = convertir(c7, c8, c9);
        if (convertir(c1, c2, c3) % 26 == 0) {
            printf("Finit en A : %c%c%c (%d)\n", c1, c2, c3, convertir(c1, c2, c3));
        }
        if (convertir(c1, c2, c3) % 26 == 25) {
            printf("Finit en Z : %c%c%c (%d)\n", c1, c2, c3, convertir(c1, c2, c3));
        }
    }
}

long long int day_8_2() {

    // allocation des variables
    FILE* f = NULL;
    int leftright[P];
    int terminent_A = 6;
    pointeur actuels[6];
    int association[N];
    pointeur** pointeurs = malloc(P * sizeof(pointeur*));
    for (int k = 0; k < P; k++) {
        pointeurs[k] = malloc(T * sizeof(pointeur));
        for (int i = 0; i < T; i++) {
            pointeurs[k][i].ecart = -1;
            pointeurs[k][i].position = -1;
            pointeurs[k][i].prochain = -1;
        }
    }
    int** directions = malloc(T * sizeof(int*));
    for (int k = 0; k < T; k++) {
        directions[k] = malloc(2 * sizeof(int));
        directions[k][0] = -1;
        directions[k][1] = -1;
    }

    // lecture du fichier
    f = fopen("advent_8.txt", "r");
    lire_fichier(f, association, leftright, directions);
    fclose(f);

    // creation du tableau de pointeurs
    int cpt = 0;
    for (int k = 0; k < T; k++) {
        for (int i = 0; i < P; i++) {
            //if (k == 834) printf("Debut %d %d\n", k, i);
            trouver_prochain(&pointeurs[i][k], directions, leftright, k, i);
            //if (k == 834) printf("Fin   %d %d\n", k, i);
        }
        if ((pointeurs[0][k].ecart != -1) && (k % 26 == 0)) {
            printf("%d est dedans\n", k);
            actuels[cpt].position = 0;
            actuels[cpt].ecart = pointeurs[0][k].ecart;
            actuels[cpt].prochain = pointeurs[0][k].prochain;
            cpt++;
        }
    }

    // parcours du tableau
    int le_plus_proche;
    bool tous_arrives;
    long long int compteur = 0;
    while (!tous_arrives) {
        le_plus_proche = 0;
        tous_arrives = true;
        for (int k = 0; k < 6; k++) {
            if (compteur % 1000000 == 0) (" %d %d %d\n", actuels[k].ecart, actuels[k].position, actuels[k].prochain);
            if (actuels[le_plus_proche].ecart > actuels[k].ecart) {
                le_plus_proche = k;
            }
        }
        for (int k = 0; k < 6; k++) {
            if (k != le_plus_proche) {
                actuels[k].ecart = actuels[k].ecart - actuels[le_plus_proche].ecart;
                actuels[k].position = (actuels[k].position + actuels[le_plus_proche].ecart) % P;
            }
            if (actuels[k].ecart != 0) {
                tous_arrives = false;
            }
        }
        compteur = compteur + actuels[le_plus_proche].ecart;
        if (compteur % 1000000 == 0) printf("%lld\n", compteur);
        actuels[le_plus_proche].ecart = pointeurs[actuels[le_plus_proche].position][actuels[le_plus_proche].prochain].ecart;
        actuels[le_plus_proche].prochain = pointeurs[actuels[le_plus_proche].position][actuels[le_plus_proche].prochain].prochain;
    }
    printf("Total : %lld\n", compteur);

    // liberation des variables
    for (int i = 0; i < P; i++) {
        free(pointeurs[i]);
    }
    free(pointeurs);
    for (int i = 0; i < T; i++) {
        free(directions[i]);
    }
    free(directions);
    return compteur;
}

int main() {
    printf("Total : %lld", day_8_2());
    return 0;
}