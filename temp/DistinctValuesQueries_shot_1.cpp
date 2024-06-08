#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
int freq[MAXN];
int arr[MAXN];
int block_size;
int distinct_count = 0;

struct Query {
    int l, r, idx;
    bool operator<(const Query& other) const {
        if (l / block_size != other.l / block_size) {
            return l / block_size < other.l / block_size;
        }
        return r < other.r;
    }
};

void add(int pos) {
    freq[arr[pos]]++;
    if (freq[arr[pos]] == 1) distinct_count++;
}

void remove(int pos) {
    freq[arr[pos]]--;
    if (freq[arr[pos]] == 0) distinct_count--;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    block_size = sqrt(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<Query> queries(q);
    vector<int> answers(q);

    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].l--; queries[i].r--; // Convert to 0-based index
        queries[i].idx = i;
    }

    sort(queries.begin(), queries.end());

    int curr_l = 0, curr_r = -1;

    for (const auto& query : queries) {
        while (curr_r < query.r) add(++curr_r);
        while (curr_r > query.r) remove(curr_r--);
        while (curr_l < query.l) remove(curr_l++);
        while (curr_l > query.l) add(--curr_l);

        answers[query.idx] = distinct_count;
    }

    for (int i = 0; i < q; i++) {
        cout << answers[i] << '\n';
    }

    return 0;
}
