#include<iostream>
using namespace std;

const int MAX = 1005;
long long dp[MAX][MAX];
int a, b, k, n, m;

int main() {
	cin >> a >> b >> k >> n >> m;

	dp[0][0] = 1;

	for (int i = 0; i <= n;i++) {
		for (int j = 0; j <= m;j++) {
			if (i == 0 && j == 0) {
				continue;
			}

			if (i - 1 >= 0) {
				dp[i][j] = (dp[i][j] + dp[i - 1][j] * a) % 10007;
			}

			if (j - 1 >= 0) {
				dp[i][j] = (dp[i][j] + dp[i][j - 1] * b) % 10007;
			}

		}
	}

	cout << dp[n][m];
	return 0;
}