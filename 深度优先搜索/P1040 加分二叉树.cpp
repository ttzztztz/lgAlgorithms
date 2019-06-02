#include<iostream>
using namespace std;

const int MAX = 35;
int dp[MAX][MAX], parent[MAX][MAX];
int N;
int mark[MAX];


inline void DP() {
	for (int i = 0; i <= N + 1;i++) {
		for (int j = 0; j <= N + 1;j++) {
			if (!dp[i][j]) {
				dp[i][j] = 1;
			}
		}
	}


	for (int l = 2; l <= N;l++) {
		for (int i = 1; i <= N - l + 1; i++) {
			int j = i + l - 1;
			for (int k = i; k <= j; k++) {
				if (dp[i][k - 1] * dp[k + 1][j] + mark[k] > dp[i][j]) {
					dp[i][j] = dp[i][k - 1] * dp[k + 1][j] + mark[k];
					parent[i][j] = k;
				}
			}
		}
	}
}

void recursive(int i, int j) {
	if (parent[i][j]) {
		cout << parent[i][j] << " ";
	}

	if (i < j) {
		recursive(i, parent[i][j] - 1);
		recursive(parent[i][j] + 1, j);
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N;i++) {
		cin >> mark[i];
		dp[i][i] = mark[i];
		parent[i][i] = i;
	}

	DP();
	cout << dp[1][N] << endl;

	recursive(1, N);

	return 0;
}