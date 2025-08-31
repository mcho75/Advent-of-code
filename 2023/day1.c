#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

int day_1() {
    FILE* f = NULL;
    char chaine[MAX];
    char* nombres[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int longueurs[9] = {3, 3, 5, 4, 4, 3, 5, 5, 4};
    int actuelles[9];
    int total = 0;
    int cpt;
    bool premiere_lettre;
    f = fopen("advent_1.txt", "r");
    printf("Debut lecture\n");
    for (int k = 0; k < 1000; k++) {
        fscanf(f, "%s\n", &chaine);
        printf("%s : ", chaine);
        premiere_lettre = true;
        cpt = 0;
        for (int i = 0; i < 9; i++) {
            actuelles[i] = 0;
        }
        for (int i = 0; chaine[i] != '\0'; i++) {
            if (((int)chaine[i]) > 47 && ((int)chaine[i] < 58)) {
                if (premiere_lettre) {
                    total = total + (((int)chaine[i] - 48)*10);
                    printf("%d - ", (int)chaine[i]-48);
                    premiere_lettre = false;
                }
                cpt = (int)chaine[i]-48;
            }
            else {
                for (int j = 0; j < 9; j++) {
                    if (nombres[j][actuelles[j]] != chaine[i]) {
                        actuelles[j] = 0;
                    }
                    if (nombres[j][actuelles[j]] == chaine[i]) {
                        actuelles[j]++;
                    }
                    if (actuelles[j] == longueurs[j]) {
                        if (premiere_lettre) {
                            total = total + ((j+1)*10);
                            printf("%d - ", (j+1));
                            premiere_lettre = false;
                        }
                        cpt = j+1;
                        actuelles[j] = 0;
                    }
                }
            }
        }
        printf("%d\n", cpt);
        total = total + cpt;
    }
    printf("Fin lecture\n");
    fclose(f);
    return total;
}