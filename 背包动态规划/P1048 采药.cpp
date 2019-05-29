#include<iostream>
using namespace std;

int T, M;
int value[105], time_arr[105];
int dp[105][1005];

int max(int x, int y) {
	return x > y ? x : y;
}

void DP() {
	for (int i = 1; i <= M;i++) {
		int v = value[i], t = time_arr[i];
		for (int j = 1; j <= T;j++) {
			if (j >= t) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - t] + v);
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
}

int main() {
	cin >> T >> M;
	for (int i = 1; i <= M;i++) {
		int t = 0, v = 0;
		cin >> t >> v;
		value[i] = v;
		time_arr[i] = t;
	}

	DP();

	cout << dp[M][T];
	return 0;
}