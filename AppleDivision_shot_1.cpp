#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    int n;
    cin >> n;
    vector<ll> p(n);
    ll sum = 0;
    for(int i = 0; i < n; i++){
        cin >> p[i];
        sum += p[i];
    }
    ll min_diff = LLONG_MAX;
    // Generate all possible combinations
    for(int i = 0; i < (1 << n); i++){
        ll curr_sum = 0;
        // Check if the jth apple is in the current combination
        for(int j = 0; j < n; j++){
            if(i & (1 << j)){
                curr_sum += p[j];
            }
        }
        // Calculate the difference for the current combination
        ll other_sum = sum - curr_sum;
        min_diff = min(min_diff, abs(curr_sum - other_sum));
    }
    cout << min_diff;
    return 0;
}