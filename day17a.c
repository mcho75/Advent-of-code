#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

// 2,0,6,6,0,0,0,6,6 : non

typedef long long int llint;

struct maillon {
    llint valeur;
    struct maillon* suiv;
};
typedef struct maillon maillon;

maillon* ajouter(maillon* c, llint valeur) {
    maillon* temp = c;
    if (temp == NULL) {
        maillon* nouveau = malloc(sizeof(maillon));
        nouveau->valeur = valeur;
        nouveau->suiv = NULL;
        return nouveau;
    }
    while (temp->suiv != NULL) {
        temp = temp->suiv;
    }
    temp->suiv = malloc(sizeof(maillon));
    temp->suiv->valeur = valeur;
    temp->suiv->suiv = NULL;
    return c;
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

void afficher_chaine(maillon* c) {
    maillon* temp = c;
    while (temp != NULL) {
        printf("%lld,", temp->valeur);
        temp = temp->suiv;
    }
    printf("\n");
}

maillon* lire_fichier(FILE* f, llint* A, llint* B, llint* C) {
    fscanf(f, "Register A: %lld\nRegister B: %lld\nRegister C: %lld\n\nProgram: ", A, B, C);
    maillon* instructions = NULL;
    llint lu;
    llint reponse = fscanf(f, "%lld,", &lu);
    while (reponse == 1) {
        instructions = ajouter(instructions, lu);
        reponse = fscanf(f, "%lld,", &lu);
    }
    afficher_chaine(instructions);
    return instructions;
}

llint max(llint a, llint b) {
    if (a >= b) return a;
    return b;
}

llint xor(llint a, llint b) {
    llint reponse = 0;
    llint taille = max(log2(a)+1, log2(b)+1);
    llint i = 0;
    // reponse += (a % 2 != b % 2);
    // a /= 2;
    // b /= 2;
    while (i <= taille) {
        reponse += (a % 2 != b % 2) * (puissance(2, i));
        a /= 2;
        b /= 2;
        i++;
    }
    return reponse;
}

void lire_instructions(maillon* instructions, llint A, llint B, llint C) {
    maillon* pointeur = instructions;
    llint operand, combo, opcode;
    while (pointeur != NULL) {
        operand = pointeur->suiv->valeur;
        if (operand <= 3) combo = operand;
        else if (operand == 4) combo = A;
        else if (operand == 5) combo = B;
        else combo = C;
        opcode = pointeur->valeur;
        // printf("Pointeur: %lld\tOperand: %lld\tA: %lld\tB: %lld\tC: %lld\n", opcode, operand, A, B, C);
        if (opcode == 0) {
            A = A / (1<<combo);
            pointeur = pointeur->suiv->suiv;
        }
        else if (opcode == 1) {
            B = xor(B, operand);
            pointeur = pointeur->suiv->suiv;
        }
        else if (opcode == 2) {
            B = combo % 8;
            pointeur = pointeur->suiv->suiv;
        }
        else if (opcode == 3) {
            if (A == 0) {
                pointeur = pointeur->suiv->suiv;
            }
            else {
                pointeur = instructions;
                for (llint i = 0; i < operand; i++) {
                    pointeur = pointeur->suiv;
                }
            }
        }
        else if (opcode == 4) {
            B = xor(B, C);
            pointeur = pointeur->suiv->suiv;
        }
        else if (opcode == 5) {
            printf("%lld,", combo % 8);
            pointeur = pointeur->suiv->suiv;
        }
        else if (opcode == 6) {
            B = A / (1<<combo);
            pointeur = pointeur->suiv->suiv;
        }
        else {
            C = A / (1<<combo);
            pointeur = pointeur->suiv->suiv;
        }
    }
    printf("\n");
}

llint main() {
    FILE* f = fopen("day17.txt", "r");
    llint A, B, C;
    maillon* instructions = lire_fichier(f, &A, &B, &C);
    fclose(f);
    lire_instructions(instructions, A, B, C);
    printf("%lld\n", xor(1, 0));
    printf("%lld\n", xor(2024, 43690));
    return 0;
}

// 247839539763386