#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

int M;
long long D, t;
const int MAX = 200005, MAXLOGN = 25;
long long dp[MAX][MAXLOGN];
int dataCount = 0;

inline long long max(long long x, long long y) {
	return x < y ? y : x;
}

void insert(long long num) {
	dataCount++;
	dp[dataCount][0] = num;

	for (int i = 1; dataCount - (1 << (i - 1)) >= 0; i++) {
		dp[dataCount][i] = max(
			dp[dataCount][i - 1],
			dp[dataCount - (1 << (i - 1))][i - 1]
		);
	}
}

int find(int start, int end) {
	int k = log2(end - start + 1);
	return max(dp[end][k], dp[start + (1 << k) - 1][k]);
}

int main() {
	cin >> M >> D;

	for (int i = 0; i < M;i++) {
		char opt = '\0';
		int par = 0;
		cin >> opt >> par;
		if (opt == 'A') {
			insert((par + t) % D);
		}
		else if (opt == 'Q') {
			t = find(dataCount - par + 1, dataCount);
			cout << t << endl;
		}
	}

	return 0;
}