#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<int> desired_sizes(n);
    std::vector<int> apartment_sizes(m);
    
    for(int i = 0; i < n; i++) {
        std::cin >> desired_sizes[i];
    }
    
    for(int i = 0; i < m; i++) {
        std::cin >> apartment_sizes[i];
    }
    
    std::sort(desired_sizes.begin(), desired_sizes.end());
    std::sort(apartment_sizes.begin(), apartment_sizes.end());
    
    int i = 0, j = 0, matches = 0;
    
    while(i < n && j < m) {
        if(apartment_sizes[j] >= desired_sizes[i] - k && apartment_sizes[j] <= desired_sizes[i] + k) {
            matches++;
            i++;
            j++;
        } else if(apartment_sizes[j] < desired_sizes[i] - k) {
            j++;
        } else {
            i++;
        }
    }
    
    std::cout << matches << std::endl;
    
    return 0;
}