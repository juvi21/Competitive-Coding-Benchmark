#include <iostream>
#include <cmath>

int main() {
    int n;
    std::cin >> n;

    // Find the minimum length L such that 2^L - 1 >= n
    int L = 1;
    while ((1 << L) - 1 < n) {
        ++L;
    }

    // Generate the bit string of length L with alternating 1s and 0s
    std::string bitString;
    for (int i = 0; i < L; ++i) {
        if (i % 2 == 0) {
            bitString += '1';
        } else {
            bitString += '0';
        }
    }

    // Print the result
    std::cout << bitString << std::endl;

    return 0;
}
