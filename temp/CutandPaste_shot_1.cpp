#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    while (m--) {
        int a, b;
        cin >> a >> b;
        // Append the substring from position a to b to the end of the string
        s += s.substr(a - 1, b - a + 1);
    }

    cout << s << endl;
    return 0;
}
