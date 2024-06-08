#include <iostream>
#include <set>

int main() {
    int n;
    std::cin >> n;

    std::set<int> distinct_numbers;
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        distinct_numbers.insert(num);
    }

    std::cout << distinct_numbers.size() << std::endl;

    return 0;
}