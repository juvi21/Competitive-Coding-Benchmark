#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int numberOfTestCases;
    cin >> numberOfTestCases;

    // Loop through each test case
    while (numberOfTestCases--) {
        int sizeOfArray;
        cin >> sizeOfArray;

        int array[sizeOfArray];
        int xorResult = 0;

        // Read the number of sticks in each heap and calculate the XOR of the remainders
        for (int i = 0; i < sizeOfArray; i++) {
            cin >> array[i];
            xorResult ^= (array[i] % 4);
        }

        // Determine the winner based on the XOR result
        if (xorResult != 0)
            cout << "first\n";
        else
            cout << "second\n";
    }

    return 0;
}