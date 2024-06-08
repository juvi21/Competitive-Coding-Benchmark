#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calcRounds(const vector<int>& pos, int n) {
    int rounds = 1;
    for (int i = 2; i <= n; i++) {
        if (pos[i] < pos[i - 1]) {
            rounds++;
        }
    }
    return rounds;
}

void updateRounds(vector<int>& pos, int x, int y, int& rounds, int n) {
    for (int i = -1; i <= 1; i++) {
        if (x + i > 0 && x + i < n) {
            if (pos[x + i] < pos[x + i - 1]) rounds--;
            if (pos[x + i] > pos[x + i - 1]) rounds++;
        }
        if (y + i > 0 && y + i < n) {
            if (pos[y + i] < pos[y + i - 1]) rounds--;
            if (pos[y + i] > pos[y + i - 1]) rounds++;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> arr(n + 1);
    vector<int> pos(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }

    int rounds = calcRounds(pos, n);

    while (m--) {
        int a, b;
        cin >> a >> b;
        if (arr[a] == arr[b]) {
            cout << rounds << endl;
            continue;
        }
        
        int x = arr[a], y = arr[b];
        
        // Remove the effects of the current positions
        updateRounds(pos, x, y, rounds, n);
        
        // Swap the elements in arr and their positions
        swap(arr[a], arr[b]);
        swap(pos[x], pos[y]);
        
        // Add the effects of the new positions
        updateRounds(pos, x, y, rounds, n);
        
        cout << rounds << endl;
    }

    return 0;
}
