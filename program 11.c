#include <stdio.h>
#include <math.h>

// Function to calculate the factorial of a number
unsigned long long factorial(int n) {
    unsigned long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

// Function to estimate the number of effectively unique keys for the Playfair cipher
double estimate_effective_keys() {
    // Total number of possible keys without considering identical encryption results
    unsigned long long total_keys = factorial(25) * factorial(25);

    // Estimate the number of effectively unique keys
    // We divide by 2 to account for symmetrical keys (e.g., ABCDEF and FEDCBA)
    double effective_keys = total_keys / 2.0;

    return effective_keys;
}

int main() {
    // Estimate the number of effectively unique keys for the Playfair cipher
    double num_effective_keys = estimate_effective_keys();

    // Print the estimated number of effectively unique keys
    printf("Estimated number of effectively unique keys for the Playfair cipher: %.0f\n", num_effective_keys);

    return 0;
}
