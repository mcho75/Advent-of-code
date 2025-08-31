#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define MAX 100

long long int day_5_1() {
    FILE* f = NULL;
    long long int seeds[20];
    bool deja_vu[20];
    char chaine[MAX];
    long long int n1, n2, n3;
    f = fopen("advent_5.txt", "r");
    fscanf(f, "seeds:");
    for (int k = 0; k < 20; k++) {
        fscanf(f, "%lld", &seeds[k]);
        printf("%lld ", seeds[k]);
    }
    for (int k = 0; k < 7; k++) {
        for (int i = 0; i < 20; i++) {
            deja_vu[i] = false;
        }
        fscanf(f, "\n");
        fscanf(f, "%s map:\n", chaine);
        printf("\n%s :\n", chaine);
        while (fscanf(f, "%lld %lld %lld\n", &n1, &n2, &n3) == 3) {
            printf(" %lld %lld %lld\n", n1, n2, n3);
            for (int i = 0; i < 20; i++) {
                if ((!deja_vu[i]) && (seeds[i] >= n2) && (seeds[i] < n2 + n3)) {
                    printf("  Graine %lld : %lld -> %lld\n", i, seeds[i], n1 + seeds[i] - n2);
                    seeds[i] = n1 + seeds[i] - n2;
                    deja_vu[i] = true;
                }
            }
        }
        printf("Fin du while\n");
    }
    long long int total = seeds[0];
    for (int k = 0; k < 20; k++) {
        if (seeds[k] < total) {
            total = seeds[k];
        }
    }
    fclose(f);
    return total;
}
