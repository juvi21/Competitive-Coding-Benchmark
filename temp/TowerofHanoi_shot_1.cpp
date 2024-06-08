#include <iostream>
using namespace std;

void hanoi(int n, int src, int dst, int aux) {
    if (n == 1) {
        cout << src << " " << dst << endl;
        return;
    }
    hanoi(n - 1, src, aux, dst);
    cout << src << " " << dst << endl;
    hanoi(n - 1, aux, dst, src);
}

int main() {
    int n;
    cin >> n;
    cout << (1 << n) - 1 << endl;
    hanoi(n, 1, 3, 2);
    return 0;
}