#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure for the segment tree node
struct SegmentTreeNode {
    long long sum;
    long long min_val;
    long long max_val;
};

// Build the segment tree from the input array
void build_segment_tree(vector<long long>& arr, vector<SegmentTreeNode>& tree, int node, int start, int end) {
    if (start == end) {
        tree[node].sum = arr[start];
        tree[node].min_val = arr[start];
        tree[node].max_val = arr[start];
    } else {
        int mid = (start + end) / 2;
        build_segment_tree(arr, tree, 2 * node, start, mid);
        build_segment_tree(arr, tree, 2 * node + 1, mid + 1, end);
        tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
        tree[node].min_val = min(tree[2 * node].min_val, tree[2 * node + 1].min_val);
        tree[node].max_val = max(tree[2 * node].max_val, tree[2 * node + 1].max_val);
    }
}

// Update the value at a specific position in the array and update the corresponding segment tree nodes
void update_segment_tree(vector<long long>& arr, vector<SegmentTreeNode>& tree, int node, int start, int end, int idx, long long val) {
    if (start == end) {
        arr[idx] = val;
        tree[node].sum = val;
        tree[node].min_val = val;
        tree[node].max_val = val;
    } else {
        int mid = (start + end) / 2;
        if (idx <= mid)
            update_segment_tree(arr, tree, 2 * node, start, mid, idx, val);
        else
            update_segment_tree(arr, tree, 2 * node + 1, mid + 1, end, idx, val);
        tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
        tree[node].min_val = min(tree[2 * node].min_val, tree[2 * node + 1].min_val);
        tree[node].max_val = max(tree[2 * node].max_val, tree[2 * node + 1].max_val);
    }
}

// Query the sum of values in a given range using the segment tree
long long query_segment_tree(vector<SegmentTreeNode>& tree, int node, int start, int end, int l, int r) {
    if (r < start || end < l)
        return 0;
    if (l <= start && end <= r)
        return tree[node].sum;
    int mid = (start + end) / 2;
    return query_segment_tree(tree, 2 * node, start, mid, l, r) + query_segment_tree(tree, 2 * node + 1, mid + 1, end, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<SegmentTreeNode> tree(4 * n);
    build_segment_tree(arr, tree, 1, 0, n - 1);

    for (int i = 0; i < q; i++) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 1) {
            update_segment_tree(arr, tree, 1, 0, n - 1, a - 1, b);
        } else {
            cout << query_segment_tree(tree, 1, 0, n - 1, a - 1, b - 1) << endl;
        }
    }

    return 0;
}