#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> heaps(n);
        int nim_sum = 0;
        
        for (int i = 0; i < n; ++i) {
            cin >> heaps[i];
            nim_sum ^= heaps[i];
        }
        
        if (nim_sum) {
            cout << "first\n";
        } else {
            cout << "second\n";
        }
    }
    
    return 0;
}
