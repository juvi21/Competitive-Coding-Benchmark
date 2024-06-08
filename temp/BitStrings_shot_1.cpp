#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;

// Function to perform modular exponentiation
long long modular_exponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd, multiply base with the result
            result = (result * base) % mod;
        }
        base = (base * base) % mod; // Square the base
        exp /= 2; // Divide the exponent by 2
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    
    // Calculate 2^n % (10^9 + 7)
    long long result = modular_exponentiation(2, n, MOD);
    
    // Print the result
    cout << result << endl;
    
    return 0;
}
