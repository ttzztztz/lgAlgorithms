#include<iostream>
using namespace std;

int T, M;
int timeArr[10005], valueArr[10005];
int dp[100005];

int max(int x, int y) {
	return x > y ? x : y;
}

void DP() {
	for (int i = 1; i <= M;i++) {
		int v = valueArr[i], t = timeArr[i];
		for (int j = 1; j <= T;j++) {
			if (j >= t) {
				dp[j] = max(dp[j], dp[j - t] + v);
			}
		}
	}
}

int main() {
	cin >> T >> M;
	for (int i = 1; i <= M;i++) {
		int time = 0, value = 0;
		cin >> time >> value;
		timeArr[i] = time;
		valueArr[i] = value;
	}

	DP();

	cout << dp[T];
	return 0;
}