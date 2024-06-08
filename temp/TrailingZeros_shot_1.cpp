#include <iostream>
using namespace std;

int main() {
    int n, count = 0;
    cin >> n;
    for (int i = 5; i <= n; i *= 5) {
        count += n / i;
    }
    cout << count << endl;
    return 0;
}