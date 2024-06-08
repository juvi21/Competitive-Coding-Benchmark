#include <iostream>
#include <string>

int main() {
    std::string dnaSequence;
    std::cin >> dnaSequence;

    char currentChar = dnaSequence[0];
    int currentCount = 1;
    int maxCount = 1;

    for (int i = 1; i < dnaSequence.length(); i++) {
        if (dnaSequence[i] == currentChar) {
            currentCount++;
        } else {
            maxCount = std::max(maxCount, currentCount);
            currentChar = dnaSequence[i];
            currentCount = 1;
        }
    }

    maxCount = std::max(maxCount, currentCount);

    std::cout << maxCount << std::endl;

    return 0;
}