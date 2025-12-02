#include <stdio.h>
#include <stdlib.h>

#define NBLINES 4393

int lire_fichier(FILE* f) {
    int position = 50;
    int total = 0;
    int mouvement;
    char direction;
    for (int i = 0; i < NBLINES; i++) {
        fscanf(f, "%c%d\n", &direction, &mouvement);
        if (direction == 'L') {
            position = (position - mouvement) % 100;
        } else if (direction == 'R') {
            position = (position + mouvement) % 100;
        }
        if (position == 0) {
            total++;
        }
    }
    return total;
}

int main() {
    FILE* f = fopen("inputs/day1.txt", "r");
    int total = lire_fichier(f);
    fclose(f);
    printf("Total crossings at position 0: %d\n", total);
    return EXIT_SUCCESS;
}