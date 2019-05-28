#include<iostream>
using namespace std;

class Item{
public:
	int value, weight;
	Item() :weight(0), value(0) {};
	Item(int v, int w) : weight(w), value(v) {};
};

Item arr[25];
int dp[30000];

inline int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int N = 0, m = 0;
	cin >> N >> m;
	for (int i = 0; i < m;i++) {
		int w = 0, v = 0;
		cin >> w >> v;
		arr[i] = { w,v };
	}
	for (int j = 0; j <= m; j++) {
		for (int i = N; i >= 0;i--) {
			int value = arr[j].value;
			int weight = arr[j].weight;

			if (i - value >= 0) {
				dp[i] = max(dp[i], dp[i - value] + weight * value);
			}

		}
	}

	cout << dp[N];

	return 0;
}