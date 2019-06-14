#include<iostream>
using namespace std;

const int MAX = 300005;
int M, S, T, dp[MAX];

int max(int x, int y) {
	return x < y ? y : x;
}

int main() {
	cin >> M >> S >> T;

	for (int t = 1; t <= T;t++) {
		if (M >= 10) {
			M -= 10;
			dp[t] = dp[t - 1] + 60;
		}
		else {
			M += 4;
			dp[t] = dp[t - 1];
		}
	}
	
	int answerS = 0, answerT = 0;

	for (int t = 1; t <= T; t++) {
		dp[t] = max(dp[t - 1] + 17, dp[t]);
		if (dp[t] > answerS) {
			answerS = dp[t];
		}
		if (dp[t] >= S && !answerT) {
			answerT = t;
		}
	}

	if (answerT) {
		cout << "Yes" << endl << answerT;
	}
	else {
		cout << "No" << endl << answerS;
	}

	return 0;
}