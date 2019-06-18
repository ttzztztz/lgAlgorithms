#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int MAX = 505;
int map[MAX][MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

int main() {
	int N = 0, result = 0;
	cin >> N;

	for (int i = 0; i < N;i++) {
		for (int j = i + 1; j < N;j++) {
			int number = 0;
			cin >> number;
			map[i][j] = number;
			map[j][i] = number;
		}
	}

	for (int i = 0; i < N;i++) {
		sort(map[i], map[i] + N, greater<int>());
		result = max(result, map[i][1]);
	}

	cout << 1 << endl << result;
	return 0;
}