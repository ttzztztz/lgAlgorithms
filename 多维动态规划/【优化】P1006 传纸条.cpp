#include<iostream>
using namespace std;

const int MAX = 60;
int m, n;
int map[MAX][MAX];
int dp[2 * MAX + 10][MAX][MAX];

inline int max4(int a, int b, int c, int d) {
	if (b > a) {
		a = b;
	}
	if (c > a) {
		a = c;
	}
	if (d > a) {
		a = d;
	}
	return a;
}

inline void DP() {
	for (int k = 1; k <= m + n - 1; k++) {
		for (int i = 1; i <= m;i++) {
			for (int j = 1; j <= m;j++) {
				if (k - i + 1 < 1 || k - j + 1 < 1) {
					continue;
				}
				dp[k][i][j] = max4(dp[k - 1][i][j], dp[k - 1][i - 1][j], dp[k - 1][i][j - 1], dp[k - 1][i - 1][j - 1])
					+ map[i][k - i + 1] + map[j][k - j + 1];

				if (i == j) {
					dp[k][i][j] -= map[i][k - i + 1];
				}
			}
		}
	}
}

int main() {
	cin >> m >> n;
	for (int i = 1; i <= m;i++) {
		for (int j = 1; j <= n;j++) {
			cin >> map[i][j];
		}
	}

	DP();

	cout << dp[n + m - 1][m][m];

	return 0;
}