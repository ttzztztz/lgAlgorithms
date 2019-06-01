#include<iostream>
using namespace std;

const int MAX = 1005;
int dp[MAX][MAX], map[MAX][MAX];
int R = 0;

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline void DP() {
	for (int i = 1; i <= R;i++) {
		for (int j = 1; j <= i;j++) {
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1]) + map[i][j];
		}
	}
}

int main() {
	cin >> R;
	for (int i = 1; i <= R;i++) {
		for (int j = 1; j <= i;j++) {
			cin >> map[i][j];
		}
	}

	DP();

	int result = 0;
	for (int j = 1; j <= R;j++) {
		result = max(result, dp[R][j]);
	}
	cout << result;

	return 0;
}