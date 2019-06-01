#include<iostream>
using namespace std;

const int MAX = 95;
int n, m, dp[MAX][MAX];

void DP() {
	dp[1][0] = 1;

	for (int j = 1; j <= m;j++) {
		dp[1][j] = dp[n][j - 1] + dp[2][j - 1];
		dp[n][j] = dp[n - 1][j - 1] + dp[1][j - 1];

		for (int i = 2; i < n;i++) {
			dp[i][j] = dp[i - 1][j - 1] + dp[i + 1][j - 1];
		}
	}
}

int main() {
	cin >> n >> m;

	DP();
	// dp[i][j] 表示第j步时，球在i上，所以根据含义 这里应该是dp[1][m]
	cout << dp[1][m];
	return 0;
}