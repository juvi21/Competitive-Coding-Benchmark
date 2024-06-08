#include <iostream>
using namespace std;

long long countBits(long long n) {
    long long count = 0;
    for (int i = 0; (1LL << i) <= n; ++i) {
        long long fullCycles = (n + 1) / (1LL << (i + 1));
        count += fullCycles * (1LL << i);

        long long remainder = (n + 1) % (1LL << (i + 1));
        if (remainder > (1LL << i)) {
            count += remainder - (1LL << i);
        }
    }
    return count;
}

int main() {
    long long n;
    cin >> n;
    cout << countBits(n) << endl;
    return 0;
}
