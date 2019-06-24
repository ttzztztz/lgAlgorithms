#include<iostream>
#include<cstring>
using namespace std;

const int MAX = 55, INF = 9999999;
int dp[MAX][MAX][2];
int prefixSum[MAX], offset[MAX];
int N = 0, C = 0;

inline int calcSum(int r1, int l2) {
	return prefixSum[r1] + (prefixSum[N] - prefixSum[l2 - 1]);
}

inline int min(int x, int y) {
	return x < y ? x : y;
}

int main() {
	memset(dp, 0x7f, sizeof(dp));
	cin >> N >> C;
	for (int i = 1; i <= N;i++) {
		cin >> offset[i] >> prefixSum[i];
	}
	for (int i = 2; i <= N; i++) {
		prefixSum[i] += prefixSum[i - 1];
	}
	dp[C][C][0] = dp[C][C][1] = 0;

	for (int l = 2; l <= N;l++) {
		for (int i = 1; i + l - 1 <= N;i++) {
			int j = i + l - 1;
			dp[i][j][0] = min(
				dp[i + 1][j][1] + calcSum(i, j + 1) * (offset[j] - offset[i]),
				dp[i + 1][j][0] + calcSum(i, j + 1) * (offset[i + 1] - offset[i])
			);

			dp[i][j][1] = min(
				dp[i][j - 1][1] + calcSum(i - 1, j) * (offset[j] - offset[j - 1]),
				dp[i][j - 1][0] + calcSum(i - 1, j) * (offset[j] - offset[i])
			);
		}
	}

	cout << min(dp[1][N][0], dp[1][N][1]);
	return 0;
}