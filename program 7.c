#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

// Function to count occurrences of letters in ciphertext
void count_letters(char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            frequency[index]++;
        }
    }
}

// Function to find the most frequent letter in the ciphertext
char find_most_frequent_letter(int *frequency) {
    int max_freq = 0;
    char most_frequent_letter = '\0';

    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        if (frequency[i] > max_freq) {
            max_freq = frequency[i];
            most_frequent_letter = 'a' + i;
        }
    }
    return most_frequent_letter;
}

// Function to decrypt the ciphertext using simple substitution
void decrypt_substitution(char *ciphertext, char most_frequent_letter) {
    // Define the mapping of ciphertext letters to English letters based on frequency analysis
    char mapping[ALPHABET_LENGTH];
    int offset = most_frequent_letter - 'E'; // Assuming 'E' is the most frequent letter in English

    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        int shifted_index = (i - offset + ALPHABET_LENGTH) % ALPHABET_LENGTH;
        mapping[i] = 'A' + shifted_index;
    }

    // Replace each ciphertext letter with its corresponding English letter
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = ciphertext[i];
            char base = islower(letter) ? 'a' : 'A';
            int index = tolower(letter) - 'a';
            ciphertext[i] = islower(letter) ? tolower(mapping[index]) : toupper(mapping[index]);
        }
    }
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    int frequency[ALPHABET_LENGTH] = {0};

    count_letters(ciphertext, frequency);

    char most_frequent = find_most_frequent_letter(frequency);

    printf("Most frequent letter in the ciphertext: %c\n", most_frequent);

    decrypt_substitution(ciphertext, most_frequent);

    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}
 
 
 
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

// Function to count occurrences of letters in ciphertext
void count_letters(char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            frequency[index]++;
        }
    }
}

// Function to find the most frequent letter in the ciphertext
char find_most_frequent_letter(int *frequency) {
    int max_freq = 0;
    char most_frequent_letter = '\0';

    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        if (frequency[i] > max_freq) {
            max_freq = frequency[i];
            most_frequent_letter = 'a' + i;
        }
    }
    return most_frequent_letter;
}

// Function to decrypt the ciphertext using simple substitution
void decrypt_substitution(char *ciphertext, char most_frequent_letter) {
    // Calculate the offset to shift the most frequent letter to 'e'
    int offset = most_frequent_letter - 'e';

    // Replace each ciphertext letter with its corresponding English letter
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = ciphertext[i];
            char base = islower(letter) ? 'a' : 'A';
            int index = tolower(letter) - 'a';
            int decrypted_index = (index - offset + ALPHABET_LENGTH) % ALPHABET_LENGTH;
            ciphertext[i] = islower(letter) ? 'a' + decrypted_index : 'A' + decrypted_index;
        }
    }
}

int main() {
    char ciphertext[] = "1. Mh phql, epu euh mqhihgu, ep mvi nhapvhjh, qdqmhcig ep eu piyphj
lp qdqmhcig. Ph, iqtu, epqpmgl pi cihhlhnl, eu qdqmhcig ep mvi cqtphng ian yng
tiyvng epqpmgl mj, mqphvgp jngu, hiiqpnglp, nl hiip iqtu, iikygqpngl, eg. Htui ep
tiyvngp epqpmgl mj. Hviqpqphv, ephqpmgl, vi ph fqnigp qdqmhcig ep mvi ian jnu
aiqphg epqpmgl mj mj hi. Qpi mh phql qdqmhcig, epiqh fgnigp, ephqpmgl vi ciptt
qit. Hiiqpnglp vi ciht, yng qit hiiqpngl mj mj hi qpiqmhqn ep jngu. Hiiqpngl ph
ciht, yng ph hiiqpngl mj mj hi qpiqmhqn ep jngu. Hiiqpngl ph ciht, yng ph
hiiqpngl mj mj hi qpiqmhqn ep jngu. Hiiqpngl ph ciht, yng ph hiiqpngl mj mj
hi qpiqmhqn ep jngu. Hiiqpngl ph ciht, yng ph hiiqpngl mj mj hi qpiqmhqn ep
jngu. Hiiqpngl ph ciht, yng ph hiiqpngl mj mj hi qpiqmhqn ep jngu. Hiiqpngl ph
ciht, yng ph hiiqpngl mj mj hi qpiqmhqn ep jngu. Hiiqpngl ph ciht, yng ph
hiiqpngl mj mj hi qpiqmhqn ep jngu. Hiiqpngl ph ciht, yng ph hiiqpngl mj mj
hi qpiqmhqn ep jngu. Hiiqpngl ph ciht, yng ph hiiqpngl mj mj hi qpiqmhqn ep
jngu. Hiiqpngl ph ciht, yng ph hiiqpngl mj mj hi qpiqmhqn ep jngu. Hiiqpngl ph
ciht, yng
