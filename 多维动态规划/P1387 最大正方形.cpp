#include<iostream>
using namespace std;

// dp[i][j] 表示以 (i, j)为右下角可以构成的三角形数量
const int MAX = 105;
int map[MAX][MAX], dp[MAX][MAX];
int n, m, result;

inline int min3(int a, int b, int c) {
	if (b < a) {
		a = b;
	}
	if (c < a) {
		a = c;
	}
	return a;
}

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline void DP() {
	for (int i = 1; i <= n;i++) {
		for (int j = 1; j <= m;j++) {
			if (map[i][j]) {
				dp[i][j] = min3(dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]) + 1;
				result = max(dp[i][j], result);
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n;i++) {
		for (int j = 1; j <= m;j++) {
			cin >> map[i][j];
		}
	}

	DP();
	cout << result;
	return 0;
}