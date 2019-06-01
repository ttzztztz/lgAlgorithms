#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 10005;
pair<int, int> timeTable[MAX];
int startTaskCountAt[MAX];
int N, K;
int dp[MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline void DP() {
	int offset = 0;

	for (int i = N; i >= 1;i--) {
		if (startTaskCountAt[i] == 0) {
			dp[i] = dp[i + 1] + 1;
		}
		else {
			for (int j = 0; j < startTaskCountAt[i];j++) {
				dp[i] = max(dp[i], dp[timeTable[offset].second]);
				offset++;
			}
		}
	}
}

int main() {
	cin >> N >> K;

	for (int i = 0; i < K;i++) {
		int start = 0, duration = 0;
		cin >> start >> duration;
		timeTable[i] = { start, start + duration };
		startTaskCountAt[start]++;
	}

	sort(timeTable, timeTable + K, [](pair<int, int>& $1, pair<int, int>& $2)->bool {
		return $1.first > $2.first;
	});

	DP();
	cout << dp[1];
	return 0;
}