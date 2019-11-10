#include <iostream>

using namespace std;

const int MAXN = 100005, MAXLOGN = 20;
int dp[MAXN][MAXLOGN + 5], Log2N[MAXN];

void init() {
    for (int j = 1; j <= MAXLOGN; j++) {
        for (int i = 1; i + (1 << j) - 1 <= MAXN; i++) {
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }

    Log2N[1] = 0;
    Log2N[2] = 1;
    for (int i = 3; i < MAXN; i++) {
        Log2N[i] = Log2N[i / 2] + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> dp[i][0];
    }

    init();
    for (int i = 0; i < M; i++) {
        int start, end;
        cin >> start >> end;

        const int K = Log2N[end - start + 1];

        printf("%d\n", max(dp[start][K], dp[end - (1 << K) + 1][K]));
    }

    return 0;
}