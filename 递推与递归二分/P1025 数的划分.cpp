#include<iostream>
using namespace std;

int dp[205][205];
int N = 0, K = 0;

void DP() {
	// 总情况 = 至少有1个箱子里只有一个球 + 所有的箱子都至少有两个球
	// 所有箱子都至少有两个球，等价于每个箱子都拿出一个球，dp[i-j][j]的情况

	for (int i = 1; i <= N; i++) {
		dp[i][1] = 1;
	}

	for (int i = 2; i <= N;i++) {
		for (int j = 2; j <= K;j++) {
			if (i >= j) {
				dp[i][j] = dp[i - 1][j - 1] + dp[i - j][j];
			}
			else {
				dp[i][j] = dp[i - 1][j - 1];
			}
		}
	}
}

int main() {
	cin >> N >> K;
	DP();

	cout << dp[N][K];
	return 0;
}