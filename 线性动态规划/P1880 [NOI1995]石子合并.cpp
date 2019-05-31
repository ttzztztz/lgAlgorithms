#include<iostream>
using namespace std;

const int MAX = 210;
int arr[MAX], dp_max[MAX][MAX], dp_min[MAX][MAX];

inline int merge(int x, int y) {
	int result = 0;
	for (int i = x; i <= y;i++) {
		result += arr[i];
	}
	return result;
}

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline int min(int x, int y) {
	return x < y ? x : y;
}

int main() {
	int N = 0;
	cin >> N;
	for (int i = 1; i <= N;i++) {
		cin >> arr[i];
	}

	for (int i = N + 1; i <= 2 * N;i++) {
		arr[i] = arr[i - N];
	}

	for (int l = 2;l <= N;l++) {
		for (int i = 1; i <= 2 * N - l + 1;i++) {
			int j = i + l - 1;
			dp_min[i][j] = 1000000;
			for (int k = i; k < j;k++) {
				dp_max[i][j] = max(dp_max[i][j], dp_max[i][k] + dp_max[k + 1][j] + merge(i, j));
				dp_min[i][j] = min(dp_min[i][j], dp_min[i][k] + dp_min[k + 1][j] + merge(i, j));
			}

		}
	}

	int maxResult = 0, minResult = 0x7fffffff;
	for (int i = 1; i <= N;i++) {
		maxResult = max(maxResult, dp_max[i][i + N - 1]);
		minResult = min(minResult, dp_min[i][i + N - 1]);
	}

	cout << minResult << endl << maxResult;
	return 0;
}