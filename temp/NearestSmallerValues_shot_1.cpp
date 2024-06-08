#include <iostream>
#include <stack>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::stack<int> s;
    std::vector<int> result(n);

    for (int i = 0; i < n; i++) {
        while (!s.empty() && arr[s.top()] >= arr[i]) {
            s.pop();
        }

        if (!s.empty()) {
            result[i] = s.top() + 1;
        } else {
            result[i] = 0;
        }

        s.push(i);
    }

    for (int i = 0; i < n; i++) {
        std::cout << result[i] << " ";
    }

    return 0;
}