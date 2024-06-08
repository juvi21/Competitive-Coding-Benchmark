#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    stack<int> s;
    int maxArea = 0;
    int i = 0;

    while (i < n) {
        if (s.empty() || heights[s.top()] <= heights[i]) {
            s.push(i++);
        } else {
            int tp = s.top();
            s.pop();
            int height = heights[tp];
            int width = s.empty() ? i : i - s.top() - 1;
            maxArea = max(maxArea, height * width);
        }
    }

    while (!s.empty()) {
        int tp = s.top();
        s.pop();
        int height = heights[tp];
        int width = s.empty() ? i : i - s.top() - 1;
        maxArea = max(maxArea, height * width);
    }

    cout << maxArea << endl;
    return 0;
}
