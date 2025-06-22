#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#define COUT_A 3
#define COUT_B 1

// int min_tokens(int xA, int yA, int xB, int yB, int px, int py) {
//     if (px == 0 && py == 0) {
//         return 0;
//     }
//     if (px < 0 || py < 0) {
//         return -1;
//     }
//     printf("    %d %d\n", px, py);
//     int appui_A = COUT_A + min_tokens(xA, yA, xB, yB, px-xA, py-yA);
//     int appui_B = COUT_B + min_tokens(xA, yA, xB, yB, px-xB, py-xB);
//     if (appui_B == -1 || appui_A < appui_B) {
//         return appui_A;
//     }
//     return appui_B;
// }

bool divise(int num, int denom) {
    return denom * (num / denom) == num;
}

int min_tokens(int xA, int yA, int xB, int yB, int px, int py) {
    int det = (xA * yB) - (xB * yA);
    int numA = (yB * px) - (xB * py);
    int numB = (xA * py) - (yA * px);
    if (divise(numA, det) && divise(numB, det)) {
        return (COUT_A * numA / det) + (COUT_B * numB / det);
    }
    return -1;
}

int lire_machine_suivante(FILE* f) {
    int xA, yA, xB, yB, px, py;
    if (fscanf(f, "Button A: X+%d, Y+%d\n", &xA, &yA) != 2) {
        return -2;
    }
    fscanf(f, "Button B: X+%d, Y+%d\n", &xB, &yB);
    fscanf(f, "Prize: X=%d, Y=%d\n", &px, &py);
    fscanf(f, "\n");
    return min_tokens(xA, yA, xB, yB, px, py);
}

int main() {
    FILE* f = fopen("day13.txt", "r");
    int total = 0;
    int val = 0;
    printf("DIVISE : %d\n", divise(12, 4));
    while (val != -2) {
        if (val != -1) total += val;
        printf("%d\n", val);
        val = lire_machine_suivante(f);
    }
    fclose(f);
    printf("TOTAL : %d\n", total);
    return 0;
}