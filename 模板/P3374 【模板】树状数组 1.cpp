#include<iostream>
using namespace std;

const int MAX = 500005;
int arr[MAX];

inline int lowbit(int x) {
	return x & (-x);
}

inline void increment(int x, int number) {
	while (x && x <= MAX) {
		arr[x] += number;
		x += lowbit(x);
	}
}

inline int query(int x) {
	int result = 0;
	while (x) {
		result += arr[x];
		x -= lowbit(x);
	}
	return result;
}

int main() {
	int N = 0, M = 0;
	cin >> N >> M;

	for (int i = 1; i <= N;i++) {
		int number = 0;
		cin >> number;
		increment(i, number);
	}

	for (int i = 0; i < M;i++) {
		int opt = 0, x = 0, y = 0;
		cin >> opt >> x >> y;;
		if (opt == 1) {
			increment(x, y);
		}
		else if (opt == 2) {
			int result = query(y) - query(x - 1);
			cout << result << endl;
		}
	}

	return 0;
}