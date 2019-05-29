#include<iostream>
using namespace std;

int N, M;
int value[105];
int dp[105][1005];

int max(int x, int y) {
	return x > y ? x : y;
}

void DP() {
	for (int i = 1; i <= N;i++) {
		int v = value[i];
		for (int j = 1; j <= M;j++) {
			if (j == v) {
				dp[i][j] = dp[i - 1][j] + 1;
			}
			else if(j > v) {
				dp[i][j] = dp[i - 1][j] + dp[i - 1][j - v];
			}
			else if (j < v) {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N;i++) {
		int v = 0;
		cin >> v;
		value[i] = v;
	}

	DP();

	cout << dp[N][M];
	return 0;
}