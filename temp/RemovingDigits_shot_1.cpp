#include <iostream>
using namespace std;

int main() {
    int n, steps = 0;
    cin >> n;

    while (n > 0) {
        int max_digit = 0;
        int temp = n;

        // Find the largest digit in the number
        while (temp > 0) {
            max_digit = max(max_digit, temp % 10);
            temp /= 10;
        }

        // Subtract the largest digit from the number
        n -= max_digit;

        // Increment the number of steps
        steps++;
    }

    cout << steps << endl;
    return 0;
}