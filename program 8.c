#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

// Function to generate the cipher sequence based on the keyword
void generate_cipher_sequence(char *keyword, char *cipher_sequence) {
    int index = 0;
    int used[ALPHABET_LENGTH] = {0};

    // Fill cipher sequence with keyword characters
    for (int i = 0; keyword[i] != '\0'; i++) {
        char letter = toupper(keyword[i]);
        if (isalpha(letter) && !used[letter - 'A']) {
            cipher_sequence[index++] = letter;
            used[letter - 'A'] = 1;
        }
    }

    // Fill remaining unused letters in normal order
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (!used[letter - 'A']) {
            cipher_sequence[index++] = letter;
        }
    }
    cipher_sequence[index] = '\0';
}

// Function to encrypt the plaintext using the generated cipher sequence
void encrypt_monoalphabetic(char *plaintext, char *cipher_sequence) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char letter = toupper(plaintext[i]);
            plaintext[i] = islower(plaintext[i]) ? tolower(cipher_sequence[letter - 'A']) : cipher_sequence[letter - 'A'];
        }
    }
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "This is a sample plaintext to be encrypted using monoalphabetic cipher.";
    char cipher_sequence[ALPHABET_LENGTH + 1];

    // Generate cipher sequence based on the keyword
    generate_cipher_sequence(keyword, cipher_sequence);

    printf("Cipher sequence generated: %s\n", cipher_sequence);

    // Encrypt the plaintext using the generated cipher sequence
    encrypt_monoalphabetic(plaintext, cipher_sequence);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
