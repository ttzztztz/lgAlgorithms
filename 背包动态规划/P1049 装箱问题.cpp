#include<iostream>
using namespace std;

int N, volumeAll;
int volume[35];
int dp[35][200005];

int max(int x, int y) {
	return x > y ? x : y;
}

void DP() {
	for (int i = 1; i <= N;i++) {
		int v = volume[i];
		for (int j = 1; j <= volumeAll;j++) {
			if (j >= v) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v] + v);
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
}

int main() {
	cin >> volumeAll >> N;
	for (int i = 1; i <= N;i++) {
		int s = 0;
		cin >> s;
		volume[i] = s;
	}

	DP();

	cout << (volumeAll - dp[N][volumeAll]);
	return 0;
}