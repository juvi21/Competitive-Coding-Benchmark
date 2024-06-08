#include <iostream>
using namespace std;

int main() {
    int numberOfTestCases;
    cin >> numberOfTestCases;

    // Loop through each test case
    while (numberOfTestCases--) {
        int numberOfElements;
        cin >> numberOfElements;

        int xorResult = 0;
        // Loop through each heap of sticks
        for (int i = 0; i < numberOfElements; i++) {
            int currentElement;
            cin >> currentElement;

            // XOR the number of sticks in each heap
            xorResult ^= currentElement;
        }

        // If the XOR result is 0, the second player wins
        // Otherwise, the first player wins
        if (xorResult == 0)
            cout << "second" << endl;
        else
            cout << "first" << endl;
    }

    return 0;
}