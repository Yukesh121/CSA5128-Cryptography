#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to calculate the frequency of letters in the text
void calculate_frequency(char *text, int *frequency) {
    int i = 0;
    while (text[i]) {
        if (isalpha(text[i])) {
            char c = toupper(text[i]);
            frequency[c - 'A']++;
        }
        i++;
    }
}

// Function to decrypt the ciphertext using a given key
void decrypt(char *ciphertext, char *plaintext, int key) {
    int i = 0;
    while (ciphertext[i]) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - key + 26) % 26) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0';
}

// Function to perform a letter frequency attack on the additive cipher
void frequency_attack(char *ciphertext, int top_results) {
    int frequency[26] = {0}; // Array to store frequency of letters in ciphertext
    calculate_frequency(ciphertext, frequency);

    printf("Possible plaintexts in rough order of likelihood:\n");

    for (int key = 0; key < 26; key++) {
        char plaintext[strlen(ciphertext) + 1];
        decrypt(ciphertext, plaintext, key);

        // Calculate frequency of letters in plaintext
        int plaintext_frequency[26] = {0};
        calculate_frequency(plaintext, plaintext_frequency);

        // Calculate a score based on the frequency of common English letters
        int score = 0;
        score += plaintext_frequency['E' - 'A'] + plaintext_frequency['T' - 'A'] + plaintext_frequency['A' - 'A'];
        score += plaintext_frequency['O' - 'A'] + plaintext_frequency['I' - 'A'] + plaintext_frequency['N' - 'A'];
        score += plaintext_frequency['S' - 'A'] + plaintext_frequency['H' - 'A'] + plaintext_frequency['R' - 'A'];
        score += plaintext_frequency['D' - 'A'] + plaintext_frequency['L' - 'A'] + plaintext_frequency['C' - 'A'];

        printf("Key: %d, Score: %d, Plaintext: %s\n", key, score, plaintext);
    }
}

int main() {
    // Example ciphertext
    char ciphertext[] = "Zpv epa zaylbz alza";
    
    // Number of top results to display
    int top_results = 10;

    // Perform frequency attack
    frequency_attack(ciphertext, top_results);

    return 0;
}
