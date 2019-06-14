#include<iostream>
using namespace std;

const int MAX = 5005;
int dp[MAX], dp_2[MAX];

int max(int x, int y) {
	return x < y ? y : x;
}

int N, stock[MAX];

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		cin >> stock[i];
		dp[i] = 1;
	}

	int arrCount = 1, repeatNumber = 0;

	for (int i = 0; i < N;i++) {
		for (int j = 0; j < i;j++) {
			if (stock[i] < stock[j]) {
				dp[i] = max(dp[i], dp[j] + 1);
				arrCount = max(arrCount, dp[i]);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (dp[i] == 1) {
			dp_2[i] = 1;
		}

		for (int j = 0; j < i;j++) {
			if (stock[i] < stock[j] && dp[j] + 1 == dp[i]) {
				dp_2[i] += dp_2[j];
			}
			if (stock[i] == stock[j] && dp[i] == dp[j]) {
				dp_2[i] = 0;
			}
		}
	}

	for (int i = 0; i < N;i++) {
		if (dp[i] == arrCount) {
			repeatNumber += dp_2[i];
		}
	}

	cout << arrCount << " " << repeatNumber;
	return 0;
}