#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

// Function to encrypt the plaintext using polyalphabetic substitution cipher with a given key
void polyalphabetic_encrypt(char *plaintext, char *key) {
    int key_length = strlen(key);
    int key_index = 0;
    int shift;

    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            shift = tolower(key[key_index]) - 'a'; // Determine shift amount based on current key character

            if (islower(plaintext[i])) {
                printf("%c", 'a' + (plaintext[i] - 'a' + shift) % ALPHABET_LENGTH);
            } else {
                printf("%c", 'A' + (plaintext[i] - 'A' + shift) % ALPHABET_LENGTH);
            }

            key_index = (key_index + 1) % key_length; // Move to the next character in the key
        } else {
            printf("%c", plaintext[i]); // Keep non-alphabetic characters as they are
        }
    }
    printf("\n");
}

int main() {
    char plaintext[1000];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline character

    polyalphabetic_encrypt(plaintext, key);

    return 0;
}
