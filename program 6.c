#include <stdio.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

// Function to decrypt the ciphertext using affine cipher with given 'a' and 'b'
void affine_caesar_decrypt(char *ciphertext, int a, int b) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = ciphertext[i];
            char base = islower(letter) ? 'a' : 'A';
            int x = letter - base;
            int a_inverse = -1;

            // Find modular multiplicative inverse of 'a' modulo 26
            for (int j = 1; j < ALPHABET_LENGTH; j++) {
                if ((a * j) % ALPHABET_LENGTH == 1) {
                    a_inverse = j;
                    break;
                }
            }

            if (a_inverse == -1) {
                printf("Error: Inverse of 'a' does not exist.\n");
                return;
            }

            int decrypted = (a_inverse * (x - b + ALPHABET_LENGTH)) % ALPHABET_LENGTH;
            ciphertext[i] = base + decrypted;
        }
    }
}

int main() {
    char ciphertext[] = "BUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUBUB
