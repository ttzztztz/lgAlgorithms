#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 205;
int M, T;
int dp[MAX][MAX];

int moneyArr[MAX], timeArr[MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

int main() {
	int n = 0;
	cin >> n >> M >> T;
	for (int i = 1; i <= n;i++) {
		int m = 0, t = 0;
		cin >> m >> t;
		moneyArr[i] = m;
		timeArr[i] = t;
	}
	
	for (int i = 1; i <= n;i++) {
		int m = moneyArr[i], t = timeArr[i];
		for (int j = M; j >= m;j--) {
			for (int k = T; k >= t;k--) {
				dp[j][k] = max(dp[j][k], dp[j - m][k - t] + 1);
			}
		}
	}

	cout << dp[M][T];
	return 0;
}