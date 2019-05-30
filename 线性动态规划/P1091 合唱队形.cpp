#include<iostream>
using namespace std;

const int MAX = 105;
int N = 0;
int height[MAX], dp_up[MAX], dp_down[MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline void DP(int start, int end) {// [start, end]
	for (int i = 0; i < MAX;i++) {
		dp_up[i] = 1;
	}

	for (int i = start; i <= end;i++) {
		for (int j = start; j < i;j++) {
			if (height[j] < height[i]) {
				dp_up[i] = max(dp_up[i], dp_up[j] + 1);
			}
		}
	}
}

inline void DP_Reversed(int start, int end) {
	for (int i = 0; i < MAX; i++) {
		dp_down[i] = 1;
	}

	for (int i = end; i >= start; i--) {
		for (int j = end; j > i; j--) {
			if (height[j] < height[i]) {
				dp_down[i] = max(dp_down[i], dp_down[j] + 1);
			}
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		cin >> height[i];
	}

	int result = 0;
	
	DP(0, N - 1);
	DP_Reversed(0, N - 1);

	for (int k = 0; k < N;k++) {
		result = max(result, dp_up[k] + dp_down[k] - 1);
	}

	cout << N - result;

	return 0;
}