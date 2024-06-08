#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Read the number of test cases
    long long numberOfTestCases;
    cin >> numberOfTestCases;

    // Loop through each test case
    while (numberOfTestCases--) {
        long long row, column;
        cin >> row >> column;

        // Determine the maximum value between the row and column numbers
        long long maxValue = max(row, column);

        // Calculate the starting number of the layer
        long long layerStart = (maxValue - 1) * (maxValue - 1);

        // Calculate the number in the given row and column based on the layer and the starting number
        long long result;
        if (maxValue % 2 == 0) {
            result = layerStart + row;
            result = result + (maxValue - column);
        } else {
            result = layerStart + column;
            result = result + (maxValue - row);
        }

        // Print the number in the given row and column
        cout << result << "\n";
    }

    return 0;
}