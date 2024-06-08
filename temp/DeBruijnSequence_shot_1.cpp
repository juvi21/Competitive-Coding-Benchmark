#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

void dfs(int node, int n, std::vector<int>& sequence, std::vector<bool>& visited, int& num_edges) {
    for (int i = 0; i < 2; ++i) {
        int next_node = (node << 1 | i) & ((1 << (n - 1)) - 1);
        if (!visited[node * 2 + i]) {
            visited[node * 2 + i] = true;
            dfs(next_node, n, sequence, visited, num_edges);
        }
    }
    sequence.push_back(node % 2);
}

std::string deBruijnSequence(int n) {
    if (n == 1) return "01";
    
    int num_nodes = 1 << (n - 1);
    int num_edges = 1 << n;
    std::vector<int> sequence;
    std::vector<bool> visited(num_edges, false);
    
    dfs(0, n, sequence, visited, num_edges);
    
    std::reverse(sequence.begin(), sequence.end());

    std::string result;
    for (int i = 0; i < sequence.size(); ++i) {
        result += std::to_string(sequence[i]);
    }
    for (int i = 0; i < n - 1; ++i) {
        result += result[i];
    }

    return result;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << deBruijnSequence(n) << std::endl;
    return 0;
}
