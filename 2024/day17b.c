#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

typedef long long int llint;

llint max(llint a, llint b) {
    if (a >= b) return a;
    return b;
}

llint puissance(llint x, llint n) {
    if (n == 0) {
        return 1;
    }
    if (n % 2 == 0) {
        return puissance(x * x, n / 2);
    }
    return x * puissance(x * x, (n - 1) / 2);
}

llint xor(llint a, llint b, llint taille) {
    llint reponse = 0;
    // llint taille = max((llint)log2(a)+1, (llint)log2(b)+1);
    llint i = 0;
    // reponse += (a % 2 != b % 2);
    // a /= 2;
    // b /= 2;
    //printf("\n");
    while (i < taille) {
        //printf("i = %lld\t a % 2 = %lld\t b % 2 = %lld\t res = %lld\t", i, a % 2, b % 2, a % 2 != b % 2);
        reponse += (a % 2 != b % 2) * (puissance(2, i));
        //afficher_binaire(reponse);
        //printf("\n");
        a /= 2;
        b /= 2;
        i++;
    }
    return reponse;
}

llint and(llint a, llint b, llint taille) {
    llint reponse = 0;
    // llint taille = max((llint)log2(a)+1, (llint)log2(b)+1);
    llint i = 0;
    reponse += (a % 2 == 1 && b % 2 == 1);
    a /= 2;
    b /= 2;
    while (i <= taille) {
        reponse += (a % 2 == 1 && b % 2 == 1) * (2<<i);
        a /= 2;
        b /= 2;
        i++;
    }
    return reponse;
}

void afficher_binaire(llint A) {
    llint i = 0;
    while (A != 0) {
        printf("%lld", A % 2);
        if (i % 3 == 2) {
            printf(" ");
        }
        i++;
        A /= 2;
    }
}

bool specifique(llint A_actuel, llint longueur) {
    llint INSTRUCTIONS[] = {2,4,1,1,7,5,0,3,4,3,1,6,5,5,3,0};
    llint A = A_actuel * 8;
    llint B;
    llint C;
    if (longueur == 0) {
        printf("On a terminé sur %lld\n", A_actuel);
        return true;
    }
    for (llint k = 0; k < 8; k++) {
        B = k;
        B = xor(B, 1, 3*16);
        C = A / puissance(2, B);
        B = xor(B, C, 3*16);
        B = xor(B, 6, 3*16);
        B = B % 8;
        afficher_binaire(A);
        printf(": on trouve B = %lld (reste %lld)\n", B, longueur);
        if (INSTRUCTIONS[longueur-1] == B) {
            if (specifique(A, longueur-1)) {
                return true;
            }
        }
        A++;
    }
    // afficher_binaire(A_actuel);
    // printf(": en vain\n");
    return false;
}

// bool lire_instructions(llint LONGUEUR, llint A, llint B, llint C) {
//     llint INSTRUCTIONS[] = {2,4,1,1,7,5,0,3,4,3,1,6,5,5,3,0};
//     llint opcode = INSTRUCTIONS[0];
//     llint pointeur_id = 0;
//     llint operand, combo;
//     llint cpt = 0;
//     while (pointeur_id < LONGUEUR) {
//         operand = INSTRUCTIONS[pointeur_id + 1];
//         if (operand <= 3) combo = operand;
//         else if (operand == 4) combo = A;
//         else if (operand == 5) combo = B;
//         else combo = C;
//         opcode = INSTRUCTIONS[pointeur_id];
//         // printf("Pointeur: %lld\tOperand: %lld\tA: %lld\tB: %lld\tC: %lld\n", opcode, operand, A, B, C);
//         if (opcode == 0) {
//             A = A / (1<<combo);
//             pointeur_id += 2;
//         }
//         else if (opcode == 1) {
//             B = xor(B, operand);
//             pointeur_id += 2;
//         }
//         else if (opcode == 2) {
//             B = combo % 8;
//             pointeur_id += 2;
//         }
//         else if (opcode == 3) {
//             if (A == 0) {
//                 pointeur_id += 2;
//             }
//             else {
//                 pointeur_id = operand;
//             }
//         }
//         else if (opcode == 4) {
//             B = xor(B, C);
//             pointeur_id += 2;
//         }
//         else if (opcode == 5) {
//             if (cpt > LONGUEUR || INSTRUCTIONS[cpt] != combo % 8) {
//                 return false;
//             }
//             // printf("%lld,", combo % 8);
//             cpt++;
//             pointeur_id += 2;
//         }
//         else if (opcode == 6) {
//             B = A / (1<<combo);
//             pointeur_id += 2;
//         }
//         else {
//             C = A / (1<<combo);
//             pointeur_id += 2;
//         }
//     }
//     // printf("\n");
//     return cpt == LONGUEUR;
// }

llint main() {
    // printf("<< : %lld\npow : %lld\n", 1<<3, (int)pow(2, 3));
    llint LONGUEUR = 16;
    specifique(0, LONGUEUR);
    llint valeur = 3872492645527; // B = 4 ?
    afficher_binaire(valeur);
    printf("\n");
    llint B = valeur % 8;
    afficher_binaire(B);
    printf("\nB   = ");
    B = xor(B, 1, 3*16);
    afficher_binaire(B);
    printf("\nC   = ");
    llint C = valeur / puissance(2, B);
    // printf("\n%lld %lld\n", (B/2) % 2, (C/2) % 2);
    afficher_binaire(C);
    printf("\nXOR = ");
    B = xor(B, C, 3*16);
    afficher_binaire(B);
    printf("\n");
    B = xor(B, 6, 3*16);
    afficher_binaire(B);
    printf("\n");
    B = B % 8;
    afficher_binaire(B);
    printf("\n");
    return 0;
}