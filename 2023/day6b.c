#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

long long int day_6_2() {
    FILE* f = NULL;
    f = fopen("advent_6.txt", "r");
    int times[27];
    int distances[27];
    int longueurs[2] = {0, 0};
    char lettre;
    long long int cpt = 0;
    long long int time = 0;
    long long int distance = 0;
    fscanf(f, "Time:    ");
    for (int k = 0; k < 23; k++) {
        fscanf(f, "%c", &lettre);
        printf("lu : %c qui donne %d\n", lettre, (int)lettre-48);
        if (lettre != ' ') {
            times[longueurs[0]] = ((int)lettre)-48;
            longueurs[0]++;
        }
    }
    for (int k = 0; k < longueurs[0]; k++) {
        printf("%d donne %lld\n", times[k], (times[k]*(long long int)pow(10, longueurs[0]-k-1)));
        time = time + (times[k]*(long long int)pow(10, longueurs[0]-k-1));
    }
    fscanf(f, "\nDistance:");
    for (int k = 0; k < 27; k++) {
        fscanf(f, "%c", &lettre);
        printf("lu : %c qui donne %d\n", lettre, (int)lettre-48);
        if (lettre != ' ') {
            distances[longueurs[1]] = ((int)lettre)-48;
            longueurs[1]++;
        }
    }
    for (int k = 0; k < longueurs[1]; k++) {
        printf("%d donne %lld\n", distances[k], (distances[k]*(long long int)pow(10, longueurs[1]-k-1)));
        distance = distance + (distances[k]*(long long int)pow(10, longueurs[1]-k-1));
    }
    printf("\ntime = %lld\ndistance = %lld\n", time, distance);
    for (long long int i = 0; i < time; i++) {
        if (i%1000000 == 0) {printf("\nPour i = %lld, on avance de %lld ", i, (time-i)*i);}
        if (distance < (time-i)*i) {
            cpt++;
        }
    }
    fclose(f);
    return cpt;
}