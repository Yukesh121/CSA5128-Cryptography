#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

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

// Function to decrypt the ciphertext using a given mapping
void decrypt(char *ciphertext, char *plaintext, char *mapping) {
    int i = 0;
    while (ciphertext[i]) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = mapping[ciphertext[i] - base];
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0';
}

// Function to perform a letter frequency attack on the monoalphabetic substitution cipher
void frequency_attack(char *ciphertext, int top_results) {
    int frequency[ALPHABET_SIZE] = {0}; // Array to store frequency of letters in ciphertext
    calculate_frequency(ciphertext, frequency);

    printf("Possible plaintexts in rough order of likelihood:\n");

    char mapping[ALPHABET_SIZE];
    int used[ALPHABET_SIZE] = {0};

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        // Find the most frequent letter in ciphertext
        int max_index = 0;
        for (int j = 1; j < ALPHABET_SIZE; j++) {
            if (frequency[j] > frequency[max_index] && !used[j]) {
                max_index = j;
            }
        }
        
        // Assign the most frequent letter to the most frequent letter in English
        char c = max_index + 'A';
        int freq_index = (c - 'E' + ALPHABET_SIZE) % ALPHABET_SIZE;
        char plaintext_freq = freq_index + 'A';
        mapping[max_index] = plaintext_freq;
        used[max_index] = 1;
    }

    // Decrypt the ciphertext using the mapping and print the results
    char plaintext[strlen(ciphertext) + 1];
    decrypt(ciphertext, plaintext, mapping);
    printf("%s\n", plaintext);
}

int main() {
    // Example ciphertext
    char ciphertext[] = "Zpv epa zaylbz alza";

    // Perform frequency attack
    frequency_attack(ciphertext, 10);

    return 0;
}
