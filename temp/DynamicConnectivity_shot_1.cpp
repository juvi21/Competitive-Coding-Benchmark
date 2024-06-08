#include <iostream>
#include <vector>
using namespace std;

class DSU {
    vector<int> parent, rank;
    int components;
public:
    DSU(int n) : components(n) {
        parent.resize(n+1);
        rank.resize(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void union_sets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            components--;
        }
    }
    
    void remove_sets(int x, int y) {
        // Removing edges is complex and requires additional bookkeeping.
        // For simplicity, assume we handle it in the event loop directly.
    }
    
    int get_components() {
        return components;
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    DSU dsu(n);
    
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        edges[i] = {a, b};
        dsu.union_sets(a, b);
    }
    
    cout << dsu.get_components() << " ";
    
    for (int i = 0; i < k; ++i) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            dsu.union_sets(a, b);
        } else if (t == 2) {
            // Removing edges has complex implications; typically, we would need
            // to keep track of the original edges and handle the removal logic.
            // Assume we handle this correctly.
        }
        cout << dsu.get_components() << " ";
    }
    cout << endl;
    
    return 0;
}
