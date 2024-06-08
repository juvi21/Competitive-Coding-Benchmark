#include <iostream>
#include <vector>

const int MAX_X = 1000000;

int main() {
    // Step 1: Precompute number of divisors for each number from 1 to MAX_X
    std::vector<int> divisors(MAX_X + 1, 0);
    for (int i = 1; i <= MAX_X; ++i) {
        for (int j = i; j <= MAX_X; j += i) {
            divisors[j]++;
        }
    }

    // Step 2: Read input and output results
    int n;
    std::cin >> n;
    std::vector<int> results(n);
    
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        results[i] = divisors[x];
    }

    for (int result : results) {
        std::cout << result << std::endl;
    }

    return 0;
}
