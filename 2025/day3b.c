#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#define MAX_DIGITS 100
#define NB_BATTERIES 12

int intFromChar(char c) {
    return (int) (c - '0');
}

int getIndex(char* line, int start, int end) {
    uint64_t index = end;
    for (int i = end; i >= start; i--) {
        // start and end are inclusive
        if (intFromChar(line[i]) >= intFromChar(line[index])) {
            index = i;
        }
    }
    return index;
}

uint64_t sumFromArray(char* line, int* indexes, int length) {
    uint64_t sum = 0;
    for (int i = 0; i < length; i++) {
        sum = sum * 10 + intFromChar(line[indexes[i]]);
    }
    return sum;
}

uint64_t readFile(FILE* f) {
    uint64_t total = 0;
    int indexes[NB_BATTERIES];
    char line[MAX_DIGITS];
    while (fscanf(f, "%s\n", line) != EOF) {
        indexes[0] = getIndex(line, 0, MAX_DIGITS - NB_BATTERIES);
        for (int i = 1; i < NB_BATTERIES; i++) {
            indexes[i] = getIndex(line, indexes[i - 1] + 1, MAX_DIGITS - (NB_BATTERIES - i));
        }
        total += sumFromArray(line, indexes, NB_BATTERIES);
        printf("Line: %s -> %lld\n", line, sumFromArray(line, indexes, NB_BATTERIES));
    }
    return total;
}

int main() {
    FILE* f = fopen("inputs/day3.txt", "r");
    uint64_t total = readFile(f);
    fclose(f);
    printf("Total: %lld\n", total);
    return EXIT_SUCCESS;
}