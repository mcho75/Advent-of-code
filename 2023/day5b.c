#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

long long int day_5_2() {
    FILE* f = NULL;
    long long int n1, n2, n3;
    char chaine[MAX];
    int longueurs[7];
    long long int seeds[20];
    long long int*** tableaux = malloc(7 * sizeof(long long int*));
    int cpt;
    long long int act;
    bool fait;
    for (int i = 0; i < 7; i++) {
        tableaux[i] = malloc(35 * sizeof(long long int*));
        for (int j = 0; j < 35; j++) {
            tableaux[i][j] = malloc(3 * sizeof(long long int));
        }
    }
    f = fopen("advent_5.txt", "r");
    fscanf(f, "seeds:");
    for (int k = 0; k < 20; k++) {
        fscanf(f, "%lld", &n1);
        seeds[k] = n1;
    }
    for (int k = 0; k < 7; k++) {
        cpt = 0;
        fscanf(f, "\n");
        fscanf(f, "%s map:\n", chaine);
        while (fscanf(f, "%lld %lld %lld\n", &n1, &n2, &n3) == 3) {
            tableaux[k][cpt][0] = n1;
            tableaux[k][cpt][1] = n2;
            tableaux[k][cpt][2] = n3;
            cpt++;
        }
        longueurs[k] = cpt;
        printf("Fin du while : %d\n", cpt);
    }
    for (long long int k = 0; true; k++) {
        if (k%1000 == 0) {printf("%d\n", k);}
        act = k;
        for (int i = 6; i >= 0; i--) {
            fait = false;
            for (int j = 0; j < longueurs[i]; j++) {
                if ((!fait) && (tableaux[i][j][0] <= act) && (tableaux[i][j][0] + tableaux[i][j][2] > act)) {
                    act = tableaux[i][j][1] + act - tableaux[i][j][0];
                    fait = true;
                }
            }
        }
        for (int i = 0; i < 20; i = i+2) {
            if ((act >= seeds[i]) && (act < seeds[i] + seeds[i+1])) {
                for (int i = 0; i < 7; i++) {
                    for (int j = 0; j < 35; j++) {
                        free(tableaux[i][j]);
                    }
                    free(tableaux[i]);
                }
                free(tableaux);
                fclose(f);
                return k;
            }
        }
    }
}