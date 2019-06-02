#include<iostream>
using namespace std;

const int MAX = 60;
int m, n;
int map[MAX][MAX];
int dp[MAX][MAX][MAX][MAX];

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
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n;j++) {
			for (int k = i + 1; k <= m;k++) {
				for (int l = 1; l <= n;l++) {
					dp[i][j][k][l] = 
						max4(dp[i - 1][j][k - 1][l], dp[i][j - 1][k - 1][l], dp[i - 1][j][k][l - 1], dp[i][j - 1][k][l - 1])
						+ map[i][j] + map[k][l];
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

	cout << dp[m - 1][n][m][n - 1];

	return 0;
}