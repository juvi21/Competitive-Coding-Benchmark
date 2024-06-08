#include <iostream>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int prefixXOR[n + 1];
    prefixXOR[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefixXOR[i] = prefixXOR[i - 1] ^ arr[i - 1];
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << (prefixXOR[b] ^ prefixXOR[a - 1]) << endl;
    }

    return 0;
}