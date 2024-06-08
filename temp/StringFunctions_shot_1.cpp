#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Calculate the z-function using the Z-algorithm
vector<int> z_function(const string& s) {
    int n = s.length();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i > r) {
            l = r = i;
            while (r < n && s[r - l] == s[r]) r++;
            z[i] = r - l;
            r--;
        } else {
            int k = i - l;
            if (z[k] < r - i + 1) {
                z[i] = z[k];
            } else {
                l = i;
                while (r < n && s[r - l] == s[r]) r++;
                z[i] = r - l;
                r--;
            }
        }
    }
    return z;
}

// Calculate the π-function using the KMP algorithm
vector<int> pi_function(const string& s) {
    int n = s.length();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s;
    cin >> s;
    vector<int> z = z_function(s);
    vector<int> pi = pi_function(s);
    for (int i = 0; i < s.length(); i++) {
        cout << z[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < s.length(); i++) {
        cout << pi[i] << " ";
    }
    cout << endl;
    return 0;
}