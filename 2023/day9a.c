#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define N 200
#define LONGUEUR_MAX 21

int trouver_suivant(int* chaine, int cpt) {
    bool tous_nuls = false;
    int k;
    for (k = cpt-1; !tous_nuls; k--) {
        tous_nuls = true;
        for (int i = 0; i < k; i++) {
            chaine[i] = abs(chaine[i+1] - chaine[i]);
            if (chaine[i] != 0) tous_nuls = false;
        }
    }
    return 0;
}

void lire_fichier(FILE* f) {
    int chaine[LONGUEUR_MAX];
    int n, cpt;
    int total = 0;
    char c;
    for (int k = 0; k < N; k++) {
        cpt = 0;
        c = ' ';
        while(c == ' ') {
            fscanf(f, "%d%c", &n, &c);
            chaine[cpt] = n;
            printf("%d ", n);
            cpt++;
        }
        total = total + trouver_suivant(chaine, cpt);
        printf("\n\n");
    }
    return total;
}

long long int day_9_1() {

    // definition des variables
    FILE* f = NULL;

    // lecture du fichier
    f = fopen("advent_9.txt", "r");
    lire_fichier(f);
    fclose(f);
    return 0;
}

int main() {
    printf("Total : %lld", day_9_1());
    return 0;
}