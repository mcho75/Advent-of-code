#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

bool inferieur(int* main1, int* main2) {
    for (int i = 0; i < 5; i++) {
        if (main1[i] < main2[i]) {
            return true;
        }
        if (main1[i] > main2[i]) {
            return false;
        }
    }
    return false;
}

void echanger(int** tab, int i, int j) {
    int temp;
    for (int k = 0; k < 6; k++) {
        temp = tab[i][k];
        tab[i][k] = tab[j][k];
        tab[j][k] = temp;
    }
}

long long int day_7_1() {
    FILE* f = NULL;
    f = fopen("advent_7.txt", "r");
    char valeurs[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    int decompte[13];
    int bid;
    int type[1000];
    char hand[5];
    int hand_nombre[5];
    int taille[7] = {0};
    long long int total = 0;
    int cpt = 1;
    int*** mains_classees = malloc(6*sizeof(int**));
    for (int k = 0; k < 7; k++) {
        mains_classees[k] = malloc(1000*sizeof(int*));
        for (int i = 0; i < 1000; i++) {
            mains_classees[k][i] = malloc(6*sizeof(int));
        }
    }
    for (int k = 0; k < 1000; k++) {
        fscanf(f, "%s %d\n", &hand, &bid);
        for (int i = 0; i < 13; i++) {
            decompte[i] = 0;
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 13; j++) {
                if (valeurs[j] == hand[i]) {
                    decompte[j]++;
                    hand_nombre[i] = j;
                }
            }
        }
        type[k] = 7;
        for (int i = 0; i < 13; i++) {
            if (decompte[i] == 5) {
                type[k] = 1;
            }
            else if (decompte[i] == 4) {
                type[k] = 2;
            }
            else if (decompte[i] == 3) {
                type[k] = 4;
                for (int j = 0; j < 13; j++) {
                    if (decompte[j] == 2) {
                        type[k] = 3;
                    }
                }
            }
            else if ((type[k] == 7) && (decompte[i] == 2)) {
                type[k] = 6;
                for (int j = 0; j < 13; j++) {
                    if ((decompte[j] == 2) && (j != i)) {
                        type[k] = 5;
                    }
                }
            }
        }
        for (int i = 0; i < 5; i++) {
            mains_classees[type[k]-1][taille[type[k]-1]][i] = hand_nombre[i];
        }
        mains_classees[type[k]-1][taille[type[k]-1]][5] = bid;
        taille[type[k]-1]++;
    }
    for (int k = 0; k < 7; k++) {
        for (int i = taille[k]-1; i >=0; i--) {
            for (int j = 0; j < i; j++) {
                if (inferieur(mains_classees[k][j+1], mains_classees[k][j])) {
                    echanger(mains_classees[k], j+1, j);
                }
            }
        }
    }
    for (int k = 6; k >= 0; k--) {
        printf("\nType %d :\n  ", k);
        for (int i = 0; i < taille[k]; i++) {
            printf("%d : ", cpt);
            for (int j = 0; j < 6; j++) {
                printf("%d ", mains_classees[k][i][j]);
            }
            total = total + (mains_classees[k][i][5] * cpt);
            printf("%lld += %d * %d (= %d)", total, mains_classees[k][i][5], cpt, mains_classees[k][i][5] * cpt);
            cpt++;
            printf("\n  ");
        }
    }
    for (int k = 0; k < 7; k++) {
        for (int i = 0; i < 1000; i++) {
            free(mains_classees[k][i]);
        }
        free(mains_classees[k]);
    }
    fclose(f);
    return total;
}