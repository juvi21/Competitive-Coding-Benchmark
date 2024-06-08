#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, x;
    std::cin >> n >> x;

    std::vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> weights[i];
    }

    std::sort(weights.begin(), weights.end());

    int left = 0, right = n - 1;
    int gondolas = 0;

    while (left <= right) {
        if (weights[left] + weights[right] <= x) {
            left++;
        }
        right--;
        gondolas++;
    }

    std::cout << gondolas << std::endl;

    return 0;
}