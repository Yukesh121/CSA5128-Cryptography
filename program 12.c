#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to print a matrix
void print_matrix(int matrix[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to encrypt a message using the Hill cipher
void encrypt_hill(char *plaintext, int key[2][2]) {
    int len = strlen(plaintext);
    int ciphertext[len];

    // Remove non-alphabetic characters and convert to uppercase
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            ciphertext[index++] = toupper(plaintext[i]) - 'A';
        }
    }

    // Padding if the length is odd
    if (index % 2 != 0) {
        ciphertext[index++] = 25; // 'Z'
    }

    // Encrypt the message
    for (int i = 0; i < index; i += 2) {
        int x = ciphertext[i];
        int y = ciphertext[i + 1];
        ciphertext[i] = (key[0][0] * x + key[0][1] * y) % 26;
        ciphertext[i + 1] = (key[1][0] * x + key[1][1] * y) % 26;
    }

    // Print the ciphertext
    for (int i = 0; i < index; i++) {
        printf("%c", ciphertext[i] + 'A');
    }
    printf("\n");
}

int main() {
    // Define the plaintext
    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";

    // Define the encryption key matrix
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };

    // Print the key matrix
    printf("Encryption key matrix:\n");
    print_matrix(key);
    printf("\n");

    // Encrypt the plaintext
    printf("Original plaintext: %s\n", plaintext);
    printf("Encrypted ciphertext: ");
    encrypt_hill(plaintext, key);

    return 0;
}
