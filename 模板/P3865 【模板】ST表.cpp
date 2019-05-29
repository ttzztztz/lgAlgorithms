#include<iostream>
#include<cmath>
using namespace std;

int N, M;
const int MAX = 100005, MAXLOGN = 30;
int dp[MAX][MAXLOGN];

inline int max(int a, int b) {
	return a < b ? b : a;
}

inline void prepare() {
	int maxJ = log2(N);

	for (int j = 1; j <= maxJ; j++) {
		for (int i = 1; i + (1 << j) - 1 <= N;i++) {
			dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
		}
	}
}


int main() {
	ios::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 1; i <= N;i++) {
		cin >> dp[i][0];
	}

	prepare();
	int start = 0, end = 0;
	for (int i = 0; i < M;i++) {
		cin >> start >> end;
		int k = log2(end - start + 1);

		cout << max(dp[start][k], dp[end - (1 << k) + 1][k]) << endl;
	}

	return 0;
}