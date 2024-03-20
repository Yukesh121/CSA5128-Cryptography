#include <stdio.h>
#include <stdlib.h>

#define MOD 26

// Function to calculate the modular inverse of a number
int mod_inverse(int a, int m) {
    a %= m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse does not exist
}

// Function to perform matrix multiplication
void matrix_multiply(int key[2][2], int plaintext[2], int result[2]) {
    result[0] = (key[0][0] * plaintext[0] + key[0][1] * plaintext[1]) % MOD;
    result[1] = (key[1][0] * plaintext[0] + key[1][1] * plaintext[1]) % MOD;
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int key[2][2]) {
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
}

// Function to calculate the adjugate of a 2x2 matrix
void adjugate(int key[2][2], int adj[2][2]) {
    adj[0][0] = key[1][1];
    adj[0][1] = -key[0][1];
    adj[1][0] = -key[1][0];
    adj[1][1] = key[0][0];
}

// Function to recover the key matrix using plaintext-ciphertext pairs
void recover_key(int plaintexts[][2], int ciphertexts[][2], int num_pairs, int key[2][2]) {
    int d, adj[2][2], inverse_d;

    // Construct the coefficient matrix A
    int A[4][4] = {0};
    for (int i = 0; i < num_pairs; i++) {
        A[i][0] = plaintexts[i][0];
        A[i][1] = plaintexts[i][1];
        A[i][2] = ciphertexts[i][0];
        A[i][3] = ciphertexts[i][1];
    }

    // Calculate the determinant of A
    d = determinant(key);

    // Calculate the adjugate of A
    adjugate(key, adj);

    // Calculate the inverse of the determinant
    inverse_d = mod_inverse(d, MOD);
    if (inverse_d == -1) {
        printf("Inverse does not exist.\n");
        return;
    }

    // Calculate the inverse of the key matrix
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            key[i][j] = (adj[i][j] * inverse_d) % MOD;
            if (key[i][j] < 0) {
                key[i][j] += MOD; // Ensure positive result
            }
        }
    }
}

int main() {
    // Example chosen plaintext-ciphertext pairs
    int plaintexts[][2] = {{0, 0}, {1, 1}}; // Plaintexts
    int ciphertexts[][2] = {{5, 5}, {6, 2}}; // Corresponding ciphertexts
    int num_pairs = sizeof(plaintexts) / sizeof(plaintexts[0]);

    // Initialize the key matrix
    int key[2][2] = {{1, 0}, {0, 1}}; // Initialize with identity matrix

    // Recover the key matrix
    recover_key(plaintexts, ciphertexts, num_pairs, key);

    // Print the recovered key matrix
    printf("Recovered key matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}
