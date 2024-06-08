#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    string s;
    cin >> s;

    int n = s.length();
    vector<int> count(n + 1, 0);
    vector<int> prefix(n + 1, 0);
    
    // Calculate prefix sums of number of 1s
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + (s[i] == '1');
    }

    // Frequency map to count occurrences of prefix sums
    unordered_map<int, int> freq;
    freq[0] = 1;

    for (int i = 1; i <= n; ++i) {
        // Each frequency[prefix[i] - k] means there is a substring ending at i with k ones
        for (int k = 0; k <= n; ++k) {
            if (freq.find(prefix[i] - k) != freq.end()) {
                count[k] += freq[prefix[i] - k];
            }
        }
        // Update frequency map
        freq[prefix[i]]++;
    }
    
    // Output the results
    for (int k = 0; k <= n; ++k) {
        cout << count[k] << " ";
    }
    cout << endl;

    return 0;
}
