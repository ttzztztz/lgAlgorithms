#include<iostream>
#include<vector>
using namespace std;

class Item {
public:
	int id, weight, value;
	Item() : id(-1), weight(0), value(0) {};
	Item(int i, int w, int v) : id(i), weight(w), value(v) {};
};

Item itemArray[65][5];
int N, m;
int dp[3205];

inline int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	cin >> N >> m;
	N /= 10;
	for (int i = 1; i <= m;i++) {
		int v = 0, p = 0, q = 0;
		cin >> v >> p >> q;
		v /= 10;

		if (!q) {
			itemArray[i][0] = Item(i, p, v);
		}
		else {
			if (itemArray[q][1].id == -1) {
				itemArray[q][1] = Item(i, p, v);
			}
			else {
				itemArray[q][2] = Item(i, p, v);
			}
		}
	}

	for (int i = 1; i <= m;i++) {
		for (int j = N; j >= 0;j--) {
			if (j >= itemArray[i][0].value) {

				dp[j] = max(dp[j], 
					dp[j - itemArray[i][0].value]
					+ itemArray[i][0].value * itemArray[i][0].weight);

			}
			if (j >= itemArray[i][0].value + itemArray[i][1].value) {

				dp[j] = max(dp[j], 
					dp[j - itemArray[i][0].value - itemArray[i][1].value]
					+ itemArray[i][0].value * itemArray[i][0].weight 
					+ itemArray[i][1].value * itemArray[i][1].weight);

			}
			if (j >= itemArray[i][0].value + itemArray[i][2].value) {

				dp[j] = max(dp[j], 
					dp[j - itemArray[i][0].value - itemArray[i][2].value]
					+ itemArray[i][0].value * itemArray[i][0].weight 
					+ itemArray[i][2].value * itemArray[i][2].weight);

			}
			if (j >= itemArray[i][0].value + itemArray[i][1].value + itemArray[i][2].value) {

				dp[j] = max(dp[j], 
					dp[j - itemArray[i][0].value - itemArray[i][1].value - itemArray[i][2].value]
					+ itemArray[i][0].value * itemArray[i][0].weight 
					+ itemArray[i][1].value * itemArray[i][1].weight 
					+ itemArray[i][2].value * itemArray[i][2].weight);

			}
		}
	}

	cout << dp[N] * 10;
	return 0;
}