#include<iostream>
using namespace std;

const int MAX = 205;
int dp[MAX][MAX];
int map[MAX][MAX];
int m, n;

inline int max(int x, int y) {
	return x < y ? y : x;
}

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
	int center = (n + 1) / 2;

	for (int j = 1; j <= m;j++) {
		for (int i = 1; i <= n;i++) {
			if (i >= center - j && i <= center + j) {
				dp[i][j] = 
					max4(dp[i][j], dp[i][j - 1], dp[i + 1][j - 1], dp[i - 1][j - 1])
					+ map[i][j];
			}
		}
	}
}

int main() {
	cin >> m >> n;
	for (int j = m; j >= 1;j--) {
		for (int i = 1; i <= n;i++) {
			cin >> map[i][j];
		}
	}
	DP();

	int result = 0;
	for (int i = 1; i <= n;i++) {
		result = max(result, dp[i][m]);
	}
	cout << result;
	return 0;
}