#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
bool check[25];

int main() {
	int T = 0;
	cin >> T;
	for (int _ = 0; _ < T;_++) {
		int n = 0, result = 0;
		cin >> n;
		for (int i = 0; i < n;i++) {
			memset(check, 0, sizeof(check));
			vector<int> piles = { 0 };
			int m = 0, sg = 0;
			cin >> m;
			for (int j = 0; j < m;j++) {
				int number = 0;
				cin >> number;
				check[number] = true;
			}

			int nowIndex = 0;
			for (int j = 20; j >= 1;j--) {
				if (check[j]) {
					piles[nowIndex]++;
				}
				else {
					nowIndex++;
					piles.push_back(0);
				}
			}

			for (int i = 1; i < piles.size();i+=2) {
				sg ^= piles[i];
			}

			result ^= sg;
		}

		if (result) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}

	return 0;
}