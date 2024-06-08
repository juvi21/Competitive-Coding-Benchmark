#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::multiset<int> tickets;
    std::vector<int> customers(m);
    
    for (int i = 0; i < n; ++i) {
        int price;
        std::cin >> price;
        tickets.insert(price);
    }
    
    for (int i = 0; i < m; ++i) {
        std::cin >> customers[i];
    }
    
    for (int i = 0; i < m; ++i) {
        auto it = tickets.upper_bound(customers[i]);
        if (it == tickets.begin()) {
            std::cout << -1 << std::endl;
        } else {
            --it;
            std::cout << *it << std::endl;
            tickets.erase(it);
        }
    }
    
    return 0;
}
