#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

// Function to encrypt the plaintext using monoalphabetic substitution cipher
void encrypt(char *plaintext, char *ciphertext, char *key) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(key[plaintext[i] - 'a']);
            } else {
                ciphertext[i] = toupper(key[plaintext[i] - 'A']);
            }
        } else {
            ciphertext[i] = plaintext[i]; // Keep non-alphabetic characters as they are
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[1000];
    char ciphertext[1000];
    char key[ALPHABET_LENGTH + 1]; // The key should contain all letters of the alphabet

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter the key (26 unique letters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline character

    if (strlen(key) != ALPHABET_LENGTH) {
        printf("Error: Key length should be 26 characters.\n");
        return 1;
    }

    // Check if the key contains all unique letters
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        if (!isalpha(key[i])) {
            printf("Error: Key should contain only letters of the alphabet.\n");
            return 1;
        }
        for (int j = i + 1; j < ALPHABET_LENGTH; j++) {
            if (tolower(key[i]) == tolower(key[j])) {
                printf("Error: Key should contain all unique letters.\n");
                return 1;
            }
        }
    }

    encrypt(plaintext, ciphertext, key);

    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}
