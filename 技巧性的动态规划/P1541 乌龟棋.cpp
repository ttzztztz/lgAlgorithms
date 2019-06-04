#include<iostream>
using namespace std;

const int MAX = 45;
int N, M;
int map[360], dp[MAX][MAX][MAX][MAX];
int cardList[5];

inline int max(int a, int b) {
	return a < b ? b : a;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N;i++) {
		cin >> map[i];
	}
	for (int i = 1; i <= M;i++) {
		int number = 0;
		cin >> number;
		cardList[number]++;
	}
	
	dp[0][0][0][0] = map[1];

	for (int a = 0; a <= cardList[1];a++) {
		for (int b = 0; b <= cardList[2];b++) {
			for (int c = 0; c <= cardList[3];c++) {
				for (int d = 0; d <= cardList[4];d++) {
					int step = a + b * 2 + c * 3 + d * 4 + 1;
					if (a > 0) {
						dp[a][b][c][d] = max(dp[a][b][c][d], dp[a - 1][b][c][d] + map[step]);
					}
					if (b > 0) {
						dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b - 1][c][d] + map[step]);
					}
					if (c > 0) {
						dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c - 1][d] + map[step]);
					}
					if (d > 0) {
						dp[a][b][c][d] = max(dp[a][b][c][d], dp[a][b][c][d - 1] + map[step]);
					}
				}
			}
		}
	}

	cout << dp[cardList[1]][cardList[2]][cardList[3]][cardList[4]];
	
	return 0;
}