#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#define MAX_DIGITS 100

uint64_t intFromChar(char c) {
    return (uint64_t) (c - '0');
}

uint64_t readFile(FILE* f) {
    uint64_t index1, index2;
    uint64_t total = 0;
    char line[MAX_DIGITS];
    while (fscanf(f, "%s\n", line) != EOF) {
        // searching the first digit
        index1 = MAX_DIGITS - 2;
        for (int i = MAX_DIGITS - 2; i >= 0; i--) {
            if (intFromChar(line[i]) >= intFromChar(line[index1])) {
                index1 = i;
            }
        }
        // searching the last digit
        index2 = index1 + 1;
        for (int i = index1 + 1; i < MAX_DIGITS; i++) {
            if (intFromChar(line[i]) >= intFromChar(line[index2])) {
                index2 = i;
            }
        }
        total += intFromChar(line[index1]) * 10 + intFromChar(line[index2]);
        printf("Line: %s -> %lld\n", line, intFromChar(line[index1]) * 10 + intFromChar(line[index2]));
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