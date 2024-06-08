#include <iostream>
#include <vector>

int main() {
    int k, n, m;
    std::cin >> k >> n >> m;

    std::vector<int> apples(n);
    std::vector<int> bananas(m);

    for (int i = 0; i < n; ++i) {
        std::cin >> apples[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> bananas[i];
    }

    std::vector<int> apple_count(k + 1, 0);
    std::vector<int> banana_count(k + 1, 0);

    for (int i = 0; i < n; ++i) {
        apple_count[apples[i]]++;
    }
    for (int i = 0; i < m; ++i) {
        banana_count[bananas[i]]++;
    }

    std::vector<int> result(2 * k + 1, 0);

    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j) {
            result[i + j] += apple_count[i] * banana_count[j];
        }
    }

    for (int w = 2; w <= 2 * k; ++w) {
        std::cout << result[w] << " ";
    }
    std::cout << std::endl;

    return 0;
}
