#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

uint64_t fromUpperDigits(uint64_t digits) {
    int length = (int) log10(digits) + 1;
    return digits * pow(10, length) + digits;
}

bool isRepeatNb(int n) {
    int length = (int) log10(n) + 1;
    if (length % 2 != 0) {
        return false;
    }
    int pow10first = 1;
    int pow10second = pow(10, length / 2);
    for (int i = 0; i < length / 2; i++) {
        if (n / pow10first % 10 != n / pow10second % 10) {
            return false;
        }
        pow10first *= 10;
        pow10second *= 10;
    }
    return true;
}

uint64_t lire_fichier(FILE* f) {
    uint64_t id1, id2;
    uint64_t total = 0;
    while (fscanf(f, "%lld-%lld,", &id1, &id2) != EOF) {
        printf("Checking between %lld and %lld\n", id1, id2);
        uint64_t upperDigits1 = id1 / pow(10, (int) log10(id1) / 2 + 1);
        uint64_t upperDigits2 = id2 / pow(10, (int) (log10(id2) + 1) / 2);
        printf("  Upper digits between %lld and %lld\n", upperDigits1, upperDigits2);
        for (uint64_t i = upperDigits1; i <= upperDigits2; i++) {
            uint64_t candidate = fromUpperDigits(i);
            if (candidate >= id1 && candidate <= id2) {
                printf("    Found repeat number: %lld\n", candidate);
                total += candidate;
            }
        }
    }
    return total;
}

int main() {
    FILE* f = fopen("inputs/day2.txt", "r");
    uint64_t total = lire_fichier(f);
    fclose(f);
    printf("Total: %lld\n", total);
    return EXIT_SUCCESS;
}