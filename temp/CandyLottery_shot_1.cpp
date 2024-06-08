#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    double expected_max = 0.0;

    for (int c = 1; c <= k; ++c) {
        double prob_c_max = pow(double(c) / k, n) - pow(double(c - 1) / k, n);
        expected_max += c * prob_c_max;
    }

    cout << fixed << setprecision(6) << expected_max << endl;

    return 0;
}
