#include <iostream>
#include <vector>

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::vector<long long> prefix_sum(n);
    prefix_sum[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + arr[i];
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        std::cin >> a >> b;
        a--; b--;
        if (a == 0) {
            std::cout << prefix_sum[b] << std::endl;
        } else {
            std::cout << prefix_sum[b] - prefix_sum[a - 1] << std::endl;
        }
    }

    return 0;
}