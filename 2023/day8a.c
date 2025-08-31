#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

bool compare(char* chaine1, char* chaine2, int longueur) {
    for (int i = 0; i < longueur; i++) {
        if (chaine1[i] != chaine2[i]) {
            return false;
        }
    }
    return true;
}

int day_8_1() {
    FILE* f = NULL;
    char leftright[264];
    char actuel[3] = {'A', 'A', 'A'};
    int n;
    int N = 702;
    char*** directions = malloc(N * sizeof(char**));
    for (int k = 0; k < N; k++) {
        directions[k] = malloc(3 * sizeof(char*));
        for (int i = 0; i < 3; i++) {
            directions[k][i] = malloc(4 * sizeof(char));
            directions[k][i][3] = '\0';
        }
    }
    f = fopen("advent_8.txt", "r");
    fscanf(f, "%s\n\n", &leftright);
    printf("%s\n", leftright);
    // n = k*(26*26)+i*26+j, n%26, (n/26)%26, ((n/26)/26)%26
    for (int k = 0; k < N; k++) {
        fscanf(f, "%c%c%c = (%c%c%c, %c%c%c)\n", &directions[k][0][0], &directions[k][0][1], &directions[k][0][2],
                                                 &directions[k][1][0], &directions[k][1][1], &directions[k][1][2],
                                                 &directions[k][2][0], &directions[k][2][1], &directions[k][2][2]);
        printf("%s %s %s\n", directions[k][0], directions[k][1], directions[k][2]);
    }
    for (int k = 0; true; k++) {
        //printf("k = %d, actuel = %s\n", k, actuel);
        if (leftright[k%263] == 'L') n = 1;
        if (leftright[k%263] == 'R') n = 2;
        for (int i = 0; i < N; i++) {
            if (compare(directions[i][0], actuel, 3)) {
                //printf("  %d : %s -> %s\n", n, directions[i][0], directions[i][n]);
                actuel[0] = directions[i][n][0];
                actuel[1] = directions[i][n][1];
                actuel[2] = directions[i][n][2];
                i = N;
            }
        }
        if ((actuel[0] == 'Z') && (actuel[1] == 'Z') && (actuel[2] == 'Z')) {
            fclose(f);
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < 3; j++) {
                    free(directions[i][j]);
                }
                free(directions[i]);
            }
            free(directions);
            return (k+1);
        }
    }
}

int convertir(char i, char j, char k) {
    return ((int)i-65)*26*26 + ((int)j-65)*26 + ((int)k-65);
}

int day_8_2() {
    FILE* f = NULL;
    char leftright[264];
    int n;
    int cpt = 0;
    int N = 702;
    int terminent_A = 6;
    int nombre_total = 26*26*26;
    bool tous_en_z;
    char c1, c2, c3, c4, c5, c6, c7, c8, c9;
    int actuels[6];
    int** directions = malloc(nombre_total * sizeof(int*));
    for (int k = 0; k < nombre_total; k++) {
        directions[k] = malloc(2 * sizeof(int));
    }
    f = fopen("advent_8.txt", "r");
    fscanf(f, "%s\n\n", &leftright);
    printf("%s\n", leftright);
    // n = k*(26*26)+i*26+j, n%26, (n/26)%26, ((n/26)/26)%26
    for (int k = 0; k < N; k++) {
        fscanf(f, "%c%c%c = (%c%c%c, %c%c%c)\n", &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9);
        directions[convertir(c1, c2, c3)][0] = convertir(c4, c5, c6);
        directions[convertir(c1, c2, c3)][1] = convertir(c7, c8, c9);
        if (c3 == 'A') {
            actuels[cpt] = convertir(c1, c2, c3);
            printf("%c%c%c\n", c1, c2, c3);
            cpt++;
        }
    }
    for (long long int k = 0; true; k++) {
        if (leftright[k%263] == 'L') n = 0;
        if (leftright[k%263] == 'R') n = 1;
        tous_en_z = true;
        if (k % 10000000 == 0) printf("\nk = %lld : ", k);
        //printf("\nk = %d : ", k);
        for (int i = 0; i < terminent_A; i++) {
            actuels[i] = directions[actuels[i]][n];
            if (k % 10000000 == 0) printf("%d ", actuels[i]);
            //printf("%d ", actuels[i]);
            tous_en_z = tous_en_z && (actuels[i]%26 == 25);
        }
        if (tous_en_z) {
            fclose(f);
            for (int i = 0; i < nombre_total; i++) {
                free(directions[i]);
            }
            free(directions);
            return (k+1);
        }
    }
}

int main() {
    printf("Total : %lld", day_8_2());
    return 0;
}