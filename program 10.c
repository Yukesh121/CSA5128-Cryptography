#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to find the position of a letter in the Playfair matrix
void find_position(char key_matrix[MATRIX_SIZE][MATRIX_SIZE], char letter, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (key_matrix[i][j] == letter || (key_matrix[i][j] == 'I' && letter == 'J')) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a pair of letters using the Playfair matrix
void encrypt_pair(char key_matrix[MATRIX_SIZE][MATRIX_SIZE], char first, char second) {
    int row1, col1, row2, col2;
    find_position(key_matrix, first, &row1, &col1);
    find_position(key_matrix, second, &row2, &col2);

    // Handle same row
    if (row1 == row2) {
        printf("%c%c", key_matrix[row1][(col1 + 1) % MATRIX_SIZE], key_matrix[row2][(col2 + 1) % MATRIX_SIZE]);
    }
    // Handle same column
    else if (col1 == col2) {
        printf("%c%c", key_matrix[(row1 + 1) % MATRIX_SIZE][col1], key_matrix[(row2 + 1) % MATRIX_SIZE][col2]);
    }
    // Handle different row and column
    else {
        printf("%c%c", key_matrix[row1][col2], key_matrix[row2][col1]);
    }
}

// Function to remove spaces and non-alphabetic characters from the plaintext
void sanitize_plaintext(char *plaintext) {
    int index = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            plaintext[index++] = toupper(plaintext[i]);
        }
    }
    plaintext[index] = '\0';
}

// Function to encrypt the plaintext using the Playfair matrix
void encrypt_playfair(char *plaintext, char key_matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    // Remove spaces and non-alphabetic characters from the plaintext
    sanitize_plaintext(plaintext);

    int len = strlen(plaintext);
    // Encrypt the plaintext by pairs of letters
    for (int i = 0; i < len; i += 2) {
        char first = plaintext[i];
        char second = (i + 1 < len) ? plaintext[i + 1] : 'X'; // Use 'X' if there's only one character left
        encrypt_pair(key_matrix, first, second);
    }
    printf("\n");
}

int main() {
    // Define the Playfair matrix
    char key_matrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    // Define the plaintext to be encrypted
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";

    // Encrypt the plaintext using the Playfair matrix
    encrypt_playfair(plaintext, key_matrix);

    return 0;
}
