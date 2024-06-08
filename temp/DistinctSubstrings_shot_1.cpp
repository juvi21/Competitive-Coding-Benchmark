#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to build suffix array
vector<int> buildSuffixArray(const string &s) {
    int n = s.size();
    vector<int> suffixArray(n), classes(n);
    vector<pair<char, int>> a(n);
    
    for (int i = 0; i < n; ++i) a[i] = {s[i], i};
    sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) suffixArray[i] = a[i].second;
    classes[suffixArray[0]] = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i].first == a[i-1].first) classes[suffixArray[i]] = classes[suffixArray[i-1]];
        else classes[suffixArray[i]] = classes[suffixArray[i-1]] + 1;
    }

    vector<int> c(n), cnt(n), sNew(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; ++i) {
            sNew[i] = suffixArray[i] - (1 << h);
            if (sNew[i] < 0) sNew[i] += n;
        }
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; ++i) cnt[classes[sNew[i]]]++;
        for (int i = 1; i < n; ++i) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; --i) suffixArray[--cnt[classes[sNew[i]]]] = sNew[i];
        c[suffixArray[0]] = 0;
        for (int i = 1; i < n; ++i) {
            pair<int, int> curr = {classes[suffixArray[i]], classes[(suffixArray[i] + (1 << h)) % n]};
            pair<int, int> prev = {classes[suffixArray[i-1]], classes[(suffixArray[i-1] + (1 << h)) % n]};
            if (curr == prev) c[suffixArray[i]] = c[suffixArray[i-1]];
            else c[suffixArray[i]] = c[suffixArray[i-1]] + 1;
        }
        classes.swap(c);
    }
    return suffixArray;
}

// Function to build LCP array
vector<int> buildLCPArray(const string &s, const vector<int> &suffixArray) {
    int n = s.size();
    vector<int> rank(n, 0), lcp(n, 0);
    for (int i = 0; i < n; ++i) rank[suffixArray[i]] = i;
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] > 0) {
            int j = suffixArray[rank[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            lcp[rank[i]] = h;
            if (h > 0) h--;
        }
    }
    return lcp;
}

// Function to count distinct substrings
int countDistinctSubstrings(const string &s) {
    int n = s.size();
    vector<int> suffixArray = buildSuffixArray(s);
    vector<int> lcpArray = buildLCPArray(s, suffixArray);
    
    int totalSubstrings = n * (n + 1) / 2;
    int lcpSum = 0;
    for (int i = 1; i < n; ++i) {
        lcpSum += lcpArray[i];
    }

    return totalSubstrings - lcpSum;
}

int main() {
    string s;
    cin >> s;
    cout << countDistinctSubstrings(s) << endl;
    return 0;
}
