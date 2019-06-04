#include<iostream>
using namespace std;

const int MAX = 215;
int map[MAX], dp[MAX][MAX];
int N;

inline int max(int x, int y) {
	return x < y ? y : x;
}

int main() {
	cin >> N;
	for (int i = 1; i <= N;i++) {
		cin >> map[i];
	}
	for (int i = N + 1; i <= 2 * N;i++) {
		map[i] = map[i - N];
	}
	
	for (int l = 2; l <= N;l++) {
		for (int i = 1; i <= 2 * N - l + 1;i++) {
			int j = l + i - 1;
			for (int k = i; k < j;k++) {
				dp[i][j] = max(dp[i][j],
					dp[i][k] + dp[k + 1][j] + map[i - 1] * map[j] * map[k]);
			}
		}
	}

	int result = 0;
	for (int i = 1; i <= N + 1;i++) {
		int j = i + N - 1;
		result = max(result, dp[i][j]);
	}
	cout << result;

	return 0;
}