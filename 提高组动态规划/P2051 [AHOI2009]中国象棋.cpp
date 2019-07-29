#include<iostream>

using namespace std;
const int MAX = 102, MOD = 9999973;
long long dp[MAX][MAX][MAX];
int N, M;

long long C2(int x) {
    return ((x * (x - 1)) / 2) % MOD;
}

int main() {
    cin >> N >> M;
    dp[0][0][0] = 1;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            for (int k = 0; j + k <= M; k++) {
                int m = M - j - k;
                // put 0
                dp[i][j][k] = dp[i - 1][j][k] % MOD;

                // put 1
                if (j + 1 <= M && k >= 1) {
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j + 1][k - 1] * (j + 1)) % MOD;
                }
                if (m + 1 <= M && j >= 1) {
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - 1][k] * (m + 1)) % MOD;
                }

                // put 2
                if (m + 1 <= M && k >= 1) {
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k - 1] * j * (m + 1)) % MOD;
                }
                if (k - 2 >= 0 && j + 2 <= M) {
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j + 2][k - 2] * C2(j + 2)) % MOD;
                }
                if (j - 2 >= 0 && m + 2 <= M) {
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - 2][k] * C2(m + 2)) % MOD;
                }
            }
        }
    }

    long long answer = 0;
    for (int j = 0; j <= M; j++) {
        for (int k = 0; j + k <= M; k++) {
            answer = (answer + dp[N][j][k]) % MOD;
        }
    }
    cout << answer;
    return 0;
}