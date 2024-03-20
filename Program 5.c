#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

// Function to find modular multiplicative inverse of a modulo m
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse does not exist
}

// Function to encrypt the plaintext using affine Caesar cipher
void affine_caesar_encrypt(char *plaintext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char letter = plaintext[i];
            char base = islower(letter) ? 'a' : 'A';
            int x = letter - base;
            int encrypted = (a * x + b) % ALPHABET_LENGTH;
            plaintext[i] = base + encrypted;
        }
    }
}

// Function to decrypt the ciphertext using affine Caesar cipher
void affine_caesar_decrypt(char *ciphertext, int a, int b) {
    int a_inverse = mod_inverse(a, ALPHABET_LENGTH);
    if (a_inverse == -1) {
        printf("Error: Inverse of 'a' does not exist.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = ciphertext[i];
            char base = islower(letter) ? 'a' : 'A';
            int y = letter - base;
            int decrypted = (a_inverse * (y - b + ALPHABET_LENGTH)) % ALPHABET_LENGTH;
            ciphertext[i] = base + decrypted;
        }
    }
}

int main() {
    char text[1000];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the value of 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of 'b' (any integer): ");
    scanf("%d", &b);

    affine_caesar_encrypt(text, a, b);
    printf("Encrypted text: %s\n", text);

    affine_caesar_decrypt(text, a, b);
    printf("Decrypted text: %s\n", text);

    return 0;
}
