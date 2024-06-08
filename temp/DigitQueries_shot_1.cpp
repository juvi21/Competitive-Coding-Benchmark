#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

char findKthDigit(long long k) {
    long long digitLength = 1;
    long long count = 9;
    long long start = 1;
    
    while (k > digitLength * count) {
        k -= digitLength * count;
        digitLength++;
        count *= 10;
        start *= 10;
    }
    
    start += (k - 1) / digitLength;
    string number = to_string(start);
    return number[(k - 1) % digitLength];
}

int main() {
    int q;
    cin >> q;
    vector<long long> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i];
    }
    
    for (const auto& k : queries) {
        cout << findKthDigit(k) << endl;
    }
    
    return 0;
}
