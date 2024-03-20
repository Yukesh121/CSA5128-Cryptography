#include <stdio.h>
#include <stdint.h>

// Permuted Choice 1
const int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1,  58, 50, 42, 34, 26, 18,
    10, 2,  59, 51, 43, 35, 27,
    19, 11, 3,  60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7,  62, 54, 46, 38, 30, 22,
    14, 6,  61, 53, 45, 37, 29,
    21, 13, 5,  28, 20, 12, 4
};

// Permuted Choice 2
const int PC2[] = {
    14, 17, 11, 24, 1,  5,
    3,  28, 15, 6,  21, 10,
    23, 19, 12, 4,  26, 8,
    16, 7,  27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Key rotation schedule
const int SHIFT_SCHEDULE[] = {
    1,  1,  2,  2,  2,  2,  2,  2,
    1,  2,  2,  2,  2,  2,  2,  1
};

// Perform permutation according to the given table
void permute(const uint64_t *input, uint64_t *output, const int *table, int size) {
    for (int i = 0; i < size; i++) {
        int bit_index = table[i] - 1;
        int byte_index = bit_index / 8;
        int bit_offset = 7 - (bit_index % 8);
        output[i / 8] |= ((input[byte_index] >> bit_offset) & 1) << (7 - (i % 8));
    }
}

// Left circular shift operation
void left_shift(uint64_t *key, int shift) {
    uint64_t temp = (*key << shift) | (*key >> (28 - shift));
    *key = temp & 0xFFFFFFF; // Mask out the upper 4 bits
}

// Generate the subkeys for decryption
void generate_keys(uint64_t master_key, uint64_t *subkeys) {
    // Perform PC1 permutation
    uint64_t permuted_key = 0;
    permute(&master_key, &permuted_key, PC1, 56);

    // Split into left and right halves
    uint32_t left_half = permuted_key >> 28;
    uint32_t right_half = permuted_key & 0xFFFFFFF;

    // Generate subkeys in reverse order
    for (int i = 15; i >= 0; i--) {
        // Apply reverse shift schedule
        left_shift(&left_half, SHIFT_SCHEDULE[i]);
        left_shift(&right_half, SHIFT_SCHEDULE[i]);

        // Combine left and right halves
        uint64_t combined = ((uint64_t)left_half << 28) | right_half;

        // Perform PC2 permutation
        permute(&combined, &subkeys[i], PC2, 48);
    }
}

int main() {
    // Example master key
    uint64_t master_key = 0x133457799BBCDFF1;

    // Array to store subkeys
    uint64_t subkeys[16];

    // Generate subkeys for decryption
    generate_keys(master_key, subkeys);

    // Print the generated subkeys
    printf("Subkeys for decryption:\n");
    for (int i = 0; i < 16; i++) {
        printf("%2d: 0x%012lx\n", i + 1, subkeys[i]);
    }

    return 0;
}
