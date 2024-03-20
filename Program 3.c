#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to prepare the key by removing duplicate letters and filling in the rest of the alphabet
void prepare_key(char *key, char *prepared_key) {
    int key_length = strlen(key);
    int prepared_key_index = 0;
    int alphabet[26] = {0}; // Array to keep track of letters already included in the key

    // Include unique letters from the key
    for (int i = 0; i < key_length; i++) {
        if (isalpha(key[i]) && !alphabet[tolower(key[i]) - 'a']) {
            prepared_key[prepared_key_index++] = tolower(key[i]);
            alphabet[tolower(key[i]) - 'a'] = 1;
        }
    }

    // Fill in the rest of the alphabet
    for (int i = 0; i < 26; i++) {
        if (i != ('j' - 'a') && !alphabet[i]) {
            prepared_key[prepared_key_index++] = 'a' + i;
        }
    }

    prepared_key[prepared_key_index] = '\0';
}

// Function to construct the Playfair matrix from the prepared key
void construct_matrix(char *prepared_key, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int index = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = prepared_key[index++];
        }
    }
}

// Function to find the row and column of a letter in the matrix
void find_position(char letter, char matrix[MATRIX_SIZE][MATRIX_SIZE], int *row, int *col) {
    if (letter == 'j')
        letter = 'i'; // treat 'j' and 'i' as the same letter

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt the plaintext using the Playfair cipher
void encrypt(char *plaintext, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int len = strlen(plaintext);
    char ciphertext[len * 2 + 1];
    int index = 0;

    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = (i + 1 < len) ? plaintext[i + 1] : 'x';

        if (a == b) {
            b = 'x';
            i--;
        }

        int row1, col1, row2, col2;
        find_position(a, matrix, &row1, &col1);
        find_position(b, matrix, &row2, &col2);

        if (row1 == row2) {
            ciphertext[index++] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            ciphertext[index++] = matrix[row2][(col2 + 1) % MATRIX_SIZE];
        } else if (col1 == col2) {
            ciphertext[index++] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            ciphertext[index++] = matrix[(row2 + 1) % MATRIX_SIZE][col2];
        } else {
            ciphertext[index++] = matrix[row1][col2];
            ciphertext[index++] = matrix[row2][col1];
        }
    }
    ciphertext[index] = '\0';
    printf("Encrypted text: %s\n", ciphertext);
}

int main() {
    char key[100];
    char plaintext[1000];
    char prepared_key[26];
    char matrix[MATRIX_SIZE][MATRIX_SIZE];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline character

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline character

    prepare_key(key, prepared_key);
    construct_matrix(prepared_key, matrix);
    encrypt(plaintext, matrix);

    return 0;
}
