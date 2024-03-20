#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

// Function to encrypt the plaintext using Caesar cipher with a given shift
void caesar_encrypt(char *plaintext, int shift) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                printf("%c", 'a' + (plaintext[i] - 'a' + shift) % ALPHABET_LENGTH);
            } else {
                printf("%c", 'A' + (plaintext[i] - 'A' + shift) % ALPHABET_LENGTH);
            }
        } else {
            printf("%c", plaintext[i]); // Keep non-alphabetic characters as they are
        }
    }
    printf("\n");
}

int main() {
    char plaintext[1000];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline character

    printf("Encrypted texts for Caesar cipher (shifts 1 to 25):\n");
    for (int shift = 1; shift <= 25; shift++) {
        printf("Shift %d: ", shift);
        caesar_encrypt(plaintext, shift);
    }

    return 0;
}
