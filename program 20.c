#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform ECB encryption
void ecb_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, int block_size) {
    // Perform encryption block by block
    // In ECB mode, each block is encrypted independently
    // Here, we are simulating encryption by simply copying plaintext to ciphertext
    memcpy(ciphertext, plaintext, block_size);
}

// Function to perform CBC encryption
void cbc_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, int block_size, unsigned char *iv) {
    // Perform encryption block by block
    unsigned char previous_cipher_block[block_size];
    memcpy(previous_cipher_block, iv, block_size); // Initialize the previous ciphertext block with IV

    for (int i = 0; i < strlen((char *)plaintext); i += block_size) {
        // XOR plaintext block with previous ciphertext block
        for (int j = 0; j < block_size; j++) {
            ciphertext[i + j] = plaintext[i + j] ^ previous_cipher_block[j];
        }
        // In CBC mode, each block is encrypted using the result of the previous encryption
        memcpy(previous_cipher_block, &ciphertext[i], block_size);
    }
}

int main() {
    // Example plaintext
    unsigned char plaintext[] = "This is a secret message.";

    // Example key and IV (Initialization Vector)
    unsigned char iv[16] = "1234567890123456";

    // Allocate memory for ciphertexts
    unsigned char *ecb_ciphertext = malloc(strlen((char *)plaintext));
    unsigned char *cbc_ciphertext = malloc(strlen((char *)plaintext));

    // Encrypt the plaintext using ECB mode
    ecb_encrypt(plaintext, ecb_ciphertext, 16);

    // Encrypt the plaintext using CBC mode
    cbc_encrypt(plaintext, cbc_ciphertext, 16, iv);

    // Print the ciphertexts
    printf("ECB ciphertext: %s\n", ecb_ciphertext);
    printf("CBC ciphertext: %s\n", cbc_ciphertext);

    // Free allocated memory
    free(ecb_ciphertext);
    free(cbc_ciphertext);

    return 0;
}
