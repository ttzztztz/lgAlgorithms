#include<iostream>
using namespace std;

const int MAX = 500005;
int arr[MAX];
int input[MAX];

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
		cin >> input[i];
	}

	for (int i = 0; i < M;i++) {
		int opt = 0;
		cin >> opt;
		if (opt == 1) {
			int x = 0, y = 0, k = 0;
			cin >> x >> y >> k;
			increment(x, k);
			increment(y + 1, -k);
		}
		else if (opt == 2) {
			int x = 0;
			cin >> x;
			cout << input[x] + query(x) << endl;
		}
	}

	return 0;
}