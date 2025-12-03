#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

bool isRepeatNb(uint64_t digits) {
    uint64_t length = (uint64_t) log10(digits) + 1;
    if (length < 2) {
        return false;
    }
    for (uint64_t nbDigits = 1; nbDigits <= length / 2; nbDigits++) {
        bool match = true;
        if (length % nbDigits == 0) {
            uint64_t compareDigits = digits % (uint64_t) pow(10, nbDigits);
            for (uint64_t step = 0; step < length; step += nbDigits) {
                if ((digits / (uint64_t) pow(10, step)) % (uint64_t) pow(10, nbDigits) != compareDigits) {
                    match = false;
                }
            }
        }
        else {
            match = false;
        }
        if (match) {
            return true;
        }
    }
    return false;
}

uint64_t fromDigits(uint64_t digits, uint64_t repeatCount) {
    uint64_t length = (uint64_t) log10(digits) + 1;
    uint64_t result = 0;
    for (uint64_t i = 0; i < repeatCount; i++) {
        result = result * pow(10, length) + digits;
    }
    return result;
}

uint64_t getFirstDigits(uint64_t n, uint64_t count) {
    uint64_t length = (uint64_t) log10(n) + 1;
    return n / pow(10, length - count);
}

uint64_t lire_fichier(FILE* f) {
    uint64_t id1, id2;
    uint64_t total = 0;
    while (fscanf(f, "%lld-%lld,", &id1, &id2) != EOF) {
        printf("Checking between %lld and %lld\n", id1, id2);
        uint64_t length1 = (uint64_t) log10(id1) + 1;
        uint64_t length2 = (uint64_t) log10(id2) + 1;
        for (uint64_t i = 1; i <= fmax(1, length2 / 2); i++) {
            uint64_t firstDigits1 = getFirstDigits(id1, i);
            uint64_t firstDigits2 = getFirstDigits(id2, i);
            if (length1 != length2) {
                firstDigits1 = pow(10, i-1);
                firstDigits2 = pow(10, i) - 1;
            }
            for (uint64_t nbRepeat = length1 / i; nbRepeat <= length2 / i; nbRepeat++) {
                for (uint64_t digits = firstDigits1; digits <= firstDigits2; digits++) {
                    if ((uint64_t) log10(digits) == 0 || !isRepeatNb(digits)) {
                        uint64_t candidate = fromDigits(digits, nbRepeat);
                        if (candidate >= id1 && candidate <= id2 && isRepeatNb(candidate)) {
                            printf("    Found repeat number: %lld\n", candidate);
                            total += candidate;
                        }
                    }
                }
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