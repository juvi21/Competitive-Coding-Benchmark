#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::vector<int> tail;
    for (int i = 0; i < n; i++) {
        auto it = std::lower_bound(tail.begin(), tail.end(), arr[i]);
        if (it == tail.end()) {
            tail.push_back(arr[i]);
        } else {
            *it = arr[i];
        }
    }

    std::cout << tail.size() << std::endl;

    return 0;
}