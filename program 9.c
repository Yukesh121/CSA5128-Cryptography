#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 5

// Function to find the position of a letter in the key matrix
void find_position(char key_matrix[MATRIX_SIZE][MATRIX_SIZE], char letter, int *row, int *col) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (key_matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to decrypt a pair of letters using the key matrix
void decrypt_pair(char key_matrix[MATRIX_SIZE][MATRIX_SIZE], char first, char second) {
    int row1, col1, row2, col2;
    find_position(key_matrix, first, &row1, &col1);
    find_position(key_matrix, second, &row2, &col2);

    // Handle same row
    if (row1 == row2) {
        printf("%c%c", key_matrix[row1][(col1 - 1 + MATRIX_SIZE) % MATRIX_SIZE], key_matrix[row2][(col2 - 1 + MATRIX_SIZE) % MATRIX_SIZE]);
    }
    // Handle same column
    else if (col1 == col2) {
        printf("%c%c", key_matrix[(row1 - 1 + MATRIX_SIZE) % MATRIX_SIZE][col1], key_matrix[(row2 - 1 + MATRIX_SIZE) % MATRIX_SIZE][col2]);
    }
    // Handle different row and column
    else {
        printf("%c%c", key_matrix[row1][col2], key_matrix[row2][col1]);
    }
}

// Function to decrypt the Playfair-encoded message
void decrypt_playfair(char *message, char key_matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int len = strlen(message);
    for (int i = 0; i < len; i += 2) {
        decrypt_pair(key_matrix, message[i], message[i + 1]);
    }
    printf("\n");
}

int main() {
    // Define the keyword for the Playfair cipher
    char keyword[] = "PT109";

    // Construct the key matrix using the keyword
    char key_matrix[MATRIX_SIZE][MATRIX_SIZE] = {0};
    int row = 0, col = 0;
    int used[26] = {0};

    for (int i = 0; keyword[i] != '\0'; i++) {
        if (!used[tolower(keyword[i]) - 'a']) {
            key_matrix[row][col++] = tolower(keyword[i]);
            used[tolower(keyword[i]) - 'a'] = 1;
            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch != 'q' && !used[ch - 'a']) {
            key_matrix[row][col++] = ch;
            if (col == MATRIX_SIZE) {
                col = 0;
                row++;
            }
        }
    }

    // Decrypt the Playfair-encoded message
    char message[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    decrypt_playfair(message, key_matrix);

    return 0;
}
