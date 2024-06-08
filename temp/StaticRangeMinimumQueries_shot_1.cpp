#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct SegmentTreeNode {
    int minVal;
    int left, right;
};

vector<SegmentTreeNode> segTree;

void buildSegmentTree(int node, int start, int end, vector<int>& arr) {
    if (start == end) {
        segTree[node].minVal = arr[start];
        segTree[node].left = segTree[node].right = start;
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(2 * node, start, mid, arr);
        buildSegmentTree(2 * node + 1, mid + 1, end, arr);
        segTree[node].minVal = min(segTree[2 * node].minVal, segTree[2 * node + 1].minVal);
        segTree[node].left = segTree[2 * node].left;
        segTree[node].right = segTree[2 * node + 1].right;
    }
}

int querySegmentTree(int node, int start, int end) {
    if (segTree[node].left == start && segTree[node].right == end) {
        return segTree[node].minVal;
    }
    int mid = (segTree[node].left + segTree[node].right) / 2;
    if (end <= mid) {
        return querySegmentTree(2 * node, start, end);
    } else if (start > mid) {
        return querySegmentTree(2 * node + 1, start, end);
    } else {
        return min(querySegmentTree(2 * node, start, mid), querySegmentTree(2 * node + 1, mid + 1, end));
    }
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    segTree.resize(4 * n);
    buildSegmentTree(1, 0, n - 1, arr);
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << querySegmentTree(1, a - 1, b - 1) << endl;
    }
    return 0;
}