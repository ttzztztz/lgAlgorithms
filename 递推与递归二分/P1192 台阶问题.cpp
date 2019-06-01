#include<iostream>
using namespace std;

int dp[100005];

int main() {
	int N = 0, K = 0;
	cin >> N >> K;

	dp[0] = 1;
	for (int i = 1; i <= N;i++) {
		for (int j = 1; j <= K;j++) {
			if (i >= j && dp[i - j]) {
				dp[i] += dp[i - j];
				dp[i] %= 100003;
			}
		}
	}

	cout << dp[N];

	return 0;
}