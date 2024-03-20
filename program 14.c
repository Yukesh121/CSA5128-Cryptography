#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to encrypt the plaintext using the one-time pad Vigenère cipher
void encrypt_vigenere(char *plaintext, char *ciphertext, int *key, int key_length) {
    int plaintext_length = strlen(plaintext);
    for (int i = 0; i < plaintext_length; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a'; // Determine the base character 'A' or 'a'
            ciphertext[i] = (plaintext[i] - base + key[i % key_length]) % 26 + base; // Apply the Vigenère encryption
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[plaintext_length] = '\0'; // Null-terminate the ciphertext string
}

// Function to decrypt the ciphertext and find the key to produce the desired plaintext
void decrypt_vigenere(char *ciphertext, char *plaintext, char *desired_plaintext, int *key, int key_length) {
    int ciphertext_length = strlen(ciphertext);
    int desired_plaintext_length = strlen(desired_plaintext);

    // Determine the key by decrypting the ciphertext
    for (int i = 0; i < ciphertext_length; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a'; // Determine the base character 'A' or 'a'
            key[i % key_length] = (ciphertext[i] - base - (desired_plaintext[i % desired_plaintext_length] - base) + 26) % 26; // Apply the Vigenère decryption
        }
    }
}

int main() {
    // Define the plaintext
    char plaintext[] = "send more money";
    int plaintext_length = strlen(plaintext);

    // Define the key length (stream of random numbers)
    int key_length = plaintext_length;
    int key[key_length] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; // Define the key stream

    // Encrypt the plaintext using the one-time pad Vigenère cipher
    char ciphertext[plaintext_length + 1];
    encrypt_vigenere(plaintext, ciphertext, key, key_length);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    // Define the desired plaintext
    char desired_plaintext[] = "cash not needed";

    // Find the key to produce the desired plaintext
    int found_key[key_length];
    decrypt_vigenere(ciphertext, plaintext, desired_plaintext, found_key, key_length);

    // Print the found key
    printf("Found key: ");
    for (int i = 0; i < key_length; i++) {
        printf("%d ", found_key[i]);
    }
    printf("\n");

    return 0;
}
