#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    unordered_map<int, int> freq;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        freq[arr[i]]++;
    }

    // Precompute bitwise information
    const int MAX_VAL = 1e6;
    vector<int> subset_count(MAX_VAL + 1, 0);
    vector<int> superset_count(MAX_VAL + 1, 0);
    vector<int> nonzero_and_count(MAX_VAL + 1, 0);

    for (auto &[val, count] : freq) {
        for (int i = val; i <= MAX_VAL; i += val) {
            subset_count[i] += count;
        }
    }

    for (auto &[val, count] : freq) {
        int mask = ~val;
        for (int i = mask; i > 0; i = (i - 1) & mask) {
            superset_count[i | val] += count;
        }
        superset_count[val] += count;
    }

    for (int i = 1; i <= MAX_VAL; ++i) {
        for (int j = i; j <= MAX_VAL; j += i) {
            nonzero_and_count[j] += freq[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        int x = arr[i];
        cout << subset_count[x] << " " << superset_count[x] << " " << nonzero_and_count[x] << "\n";
    }

    return 0;
}
