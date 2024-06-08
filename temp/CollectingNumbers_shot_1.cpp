#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> pos(n + 1); // pos[i] will store the position of number i

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }

    int rounds = 1; // At least one round is needed
    for (int i = 2; i <= n; ++i) {
        if (pos[i] < pos[i - 1]) {
            ++rounds;
        }
    }

    cout << rounds << endl;
    return 0;
}
