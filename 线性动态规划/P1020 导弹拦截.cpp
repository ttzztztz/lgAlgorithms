#include<iostream>
#include<cstring>
using namespace std;

const int MAX = 100005;
int N = 0, number[MAX];
int arr[MAX];

inline int max(int x, int y) {
	return x > y ? x : y;
}

int lowbit(int x) {
	return x & (-x);
}

int query(int x) {
	int result = 0;
	while (x) {
		result = max(result, arr[x]);
		x -= lowbit(x);
	}
	return result;
}

void increment(int x, int y) {
	while (x && x <= MAX) {
		arr[x] = max(arr[x], y);
		x += lowbit(x);
	}
}

int main() {
	int n = 0;
	while (cin >> n) {
		number[N++] = n;
	}

	int arrCount = 0;
	for (int i = N - 1; i >= 0;i--) {
		int count = query(number[i]) + 1;
		arrCount = max(arrCount, count);
		increment(number[i], count);
	}
	cout << arrCount << endl;

	arrCount = 0;
	memset(arr, 0, sizeof(arr));
	for (int i = 0; i < N; i++) {
		int count = query(number[i] - 1) + 1;
		arrCount = max(arrCount, count);
		increment(number[i], count);
	}
	cout << arrCount << endl;
	return 0;
}