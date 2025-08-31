// 18446744072854832140 : trop grand

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define COUT_A 3
#define COUT_B 1
#define A_AJOUTER 10000000000000

typedef long long int llint;
typedef unsigned long long int ullint;

bool divise(ullint num, ullint denom) {
    return denom * (num / denom) == num;
}

ullint min_tokens(ullint xA, ullint yA, ullint xB, ullint yB, ullint px, ullint py) {
    ullint det = (xA * yB) - (xB * yA);
    ullint numA, numB;
    if (det < 0) {
        numA = - (yB * px) + (xB * py);
        numB = - (xA * py) + (yA * px);
    }
    else {
        numA = (yB * px) - (xB * py);
        numB = (xA * py) - (yA * px);
    }
    printf("   Pour %llu %llu : %llu %llu\n", px, py, numA, numB);
    if (divise(numA, det) && divise(numB, det)) {
        return (COUT_A * numA / det) + (COUT_B * numB / det);
    }
    return 1;
}

int lire_machine_suivante(FILE* f) {
    ullint xA, yA, xB, yB, px, py;
    if (fscanf(f, "Button A: X+%llu, Y+%llu\n", &xA, &yA) != 2) {
        return 2;
    }
    fscanf(f, "Button B: X+%llu, Y+%llu\n", &xB, &yB);
    fscanf(f, "Prize: X=%llu, Y=%llu\n", &px, &py);
    fscanf(f, "\n");
    return min_tokens(xA, yA, xB, yB, px+A_AJOUTER, py+A_AJOUTER);
}

int main() {
    FILE* f = fopen("day13.txt", "r");
    ullint total = 0;
    ullint val = 0;
    while (val != 2) {
        if (val != 1) total += val;
        val = lire_machine_suivante(f);
        printf("%llu\n", val);
    }
    fclose(f);
    printf("TOTAL : %llu\n", total);
    return 0;
}