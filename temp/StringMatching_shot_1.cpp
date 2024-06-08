#include <iostream>
#include <vector>
#include <string>

std::vector<int> computePrefixFunction(const std::string& pattern) {
    int m = pattern.size();
    std::vector<int> pi(m, 0);
    int k = 0;
    for (int q = 1; q < m; q++) {
        while (k > 0 && pattern[k] != pattern[q]) {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[q]) {
            k++;
        }
        pi[q] = k;
    }
    return pi;
}

int stringMatching(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    std::vector<int> pi = computePrefixFunction(pattern);
    int q = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 && pattern[q] != text[i]) {
            q = pi[q - 1];
        }
        if (pattern[q] == text[i]) {
            q++;
        }
        if (q == m) {
            count++;
            q = pi[q - 1];
        }
    }
    return count;
}

int main() {
    std::string text, pattern;
    std::cin >> text >> pattern;
    int count = stringMatching(text, pattern);
    std::cout << count << std::endl;
    return 0;
}