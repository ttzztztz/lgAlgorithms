#include<iostream>
#include<algorithm>
using namespace std;

class Junk {
public:
	int T, F, H;
	Junk() :T(0), F(0), H(0) {};
	Junk(int t, int f, int h) :T(t), F(f), H(h) {};
};

inline int max(int x, int y) {
	return x < y ? y : x;
}

int D, G;
Junk junk[105];
int dp[105][105];
// 第i件垃圾，在高度为j时候的，牛的血量

int main() {
	cin >> D >> G;
	for (int i = 1; i <= G;i++) {
		int t = 0, f = 0, h = 0;
		cin >> t >> f >> h;
		junk[i] = { t,f,h };
	}

	sort(junk + 1, junk + 1 + G, [](const Junk& $1, const Junk& $2)->bool {
		return $1.T < $2.T;
	});

	for (int i = 0; i <= G;i++) {
		for (int j = 0; j <= D;j++) {
			dp[i][j] = -999999;
		}
	}
	dp[0][0] = 10;

	for (int i = 1; i <= G;i++) {
		const Junk& nowJunk = junk[i], & lastJunk = junk[i - 1];
		int delta = nowJunk.T - lastJunk.T;

		for (int j = 0; j <= D;j++) {
			// 转移状态之前是合法的
			if (dp[i - 1][j] >= delta) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j] - delta + nowJunk.F);
			}

			if (j >= nowJunk.H && dp[i - 1][j - nowJunk.H] >= delta) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - nowJunk.H] - delta);

				if (j == D) {
					cout << nowJunk.T;
					return 0;
				}
			}
		}
	}

	int maxLiveTime = 0;
	for (int i = 0; i <= G;i++) {
		const Junk& nowJunk = junk[i];
		for (int j = 0; j <= D;j++) {
			if (dp[i][j] > 0) {
				maxLiveTime = max(maxLiveTime, dp[i][j] + nowJunk.T);
			}
		}
	}
	cout << maxLiveTime;

	return 0;
}