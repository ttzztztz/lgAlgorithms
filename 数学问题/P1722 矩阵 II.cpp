#include <iostream>

using namespace std;

int main() {
    int n = 0;
    cin >> n;
    unsigned long long C[2 * n + 1][2 * n + 1];

    for (int i = 1; i <= 2 * n; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j] % 100 + C[i - 1][j - 1] % 100) % 100;
        }
    }

    cout << (C[2 * n][n] - C[2 * n][n - 1] + 100) % 100;

    return 0;
}