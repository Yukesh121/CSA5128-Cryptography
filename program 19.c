#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

// Function to perform 3DES encryption in CBC mode
void des_encrypt_cbc(const unsigned char *plaintext, unsigned char *ciphertext, const unsigned char *key, const unsigned char *iv) {
    DES_cblock des_key1, des_key2, des_key3, des_iv;
    DES_key_schedule ks1, ks2, ks3;

    // Set the keys
    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key + 16, 8);

    // Set the IV
    memcpy(des_iv, iv, 8);

    // Set encryption key schedules
    DES_set_key_unchecked(&des_key1, &ks1);
    DES_set_key_unchecked(&des_key2, &ks2);
    DES_set_key_unchecked(&des_key3, &ks3);

    // Encrypt the data in CBC mode
    DES_ede3_cbc_encrypt(plaintext, ciphertext, strlen((char *)plaintext), &ks1, &ks2, &ks3, &des_iv, DES_ENCRYPT);
}

// Function to perform 3DES decryption in CBC mode
void des_decrypt_cbc(const unsigned char *ciphertext, unsigned char *plaintext, const unsigned char *key, const unsigned char *iv) {
    DES_cblock des_key1, des_key2, des_key3, des_iv;
    DES_key_schedule ks1, ks2, ks3;

    // Set the keys
    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key + 16, 8);

    // Set the IV
    memcpy(des_iv, iv, 8);

    // Set decryption key schedules
    DES_set_key_unchecked(&des_key1, &ks1);
    DES_set_key_unchecked(&des_key2, &ks2);
    DES_set_key_unchecked(&des_key3, &ks3);

    // Decrypt the data in CBC mode
    DES_ede3_cbc_encrypt(ciphertext, plaintext, strlen((char *)ciphertext), &ks1, &ks2, &ks3, &des_iv, DES_DECRYPT);
}

int main() {
    // Example key and IV (Initialization Vector)
    unsigned char key[24] = "123456789012345678901234";
    unsigned char iv[8] = "12345678";

    // Example plaintext
    unsigned char plaintext[] = "This is a secret message.";

    // Allocate memory for ciphertext
    unsigned char *ciphertext = malloc(strlen((char *)plaintext));

    // Encrypt the plaintext
    des_encrypt_cbc(plaintext, ciphertext, key, iv);

    // Print the ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    // Allocate memory for decrypted plaintext
    unsigned char *decrypted_plaintext = malloc(strlen((char *)ciphertext) + 1);

    // Decrypt the ciphertext
    des_decrypt_cbc(ciphertext, decrypted_plaintext, key, iv);

    // Print the decrypted plaintext
    printf("Decrypted plaintext: %s\n", decrypted_plaintext);

    // Free allocated memory
    free(ciphertext);
    free(decrypted_plaintext);

    return 0;
}
