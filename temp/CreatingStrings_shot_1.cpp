#include <iostream>
#include <string>
#include <set>
#include <algorithm>

int main() {
    std::string input;
    std::cin >> input;

    // Sort the string to ensure that permutations are generated in lexicographical order
    std::sort(input.begin(), input.end());

    // Use a set to store unique permutations
    std::set<std::string> permutations;

    // Generate permutations using std::next_permutation
    do {
        permutations.insert(input);
    } while (std::next_permutation(input.begin(), input.end()));

    // Output the number of unique permutations
    std::cout << permutations.size() << std::endl;

    // Output each permutation
    for (const auto& perm : permutations) {
        std::cout << perm << std::endl;
    }

    return 0;
}
