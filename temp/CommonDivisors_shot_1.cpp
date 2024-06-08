#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    int maxElement = 0;
    
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        maxElement = max(maxElement, arr[i]);
    }

    vector<int> freq(maxElement + 1, 0);

    for (int i = 0; i < n; ++i) {
        freq[arr[i]]++;
    }

    for (int g = maxElement; g >= 1; --g) {
        int count = 0;
        for (int multiple = g; multiple <= maxElement; multiple += g) {
            count += freq[multiple];
            if (count >= 2) {
                cout << g << endl;
                return 0;
            }
        }
    }

    return 0;
}
