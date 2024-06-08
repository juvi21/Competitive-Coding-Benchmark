#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int xor1 = 0;
    for (int i = 1; i <= n; i++) {
        xor1 ^= i;
    }

    int xor2 = 0;
    for (int i = 0; i < n - 1; i++) {
        int num;
        cin >> num;
        xor2 ^= num;
    }

    cout << (xor1 ^ xor2) << endl;
    return 0;
}