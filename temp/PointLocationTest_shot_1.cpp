#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;

    while (t--) {
        long long x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

        long long cross_product = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);

        if (cross_product > 0)
            cout << "LEFT\n";
        else if (cross_product < 0)
            cout << "RIGHT\n";
        else
            cout << "TOUCH\n";
    }

    return 0;
}