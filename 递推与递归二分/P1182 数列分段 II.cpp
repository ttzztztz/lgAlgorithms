#include<iostream>
using namespace std;

const int MAX = 100005;
int N, M, arr[MAX];
int minNumber = 2<<31 - 1, maxNumber = 0;

inline int min(int x, int y) {
	return x < y ? x : y;
}

inline int max(int x, int y) {
	return x < y ? y : x;
}

bool judge(int x) {
	int blocks = 0, sum = 0;
	for (int i = 1; i <= N;i++) {
		if (sum + arr[i] > x) {
			blocks++;
			sum = arr[i];
		}
		else {
			sum += arr[i];
		}
	}
	if (sum > 0) {
		blocks++;
	}
	return blocks > M;
}

int search() {
	int l = minNumber, r = maxNumber;
	while (l <= r) {
		int middle = (l + r) / 2;
		if (judge(middle)) {
			l = middle + 1;
		}
		else {
			r = middle - 1;
		}
	}
	return r + 1;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N;i++) {
		cin >> arr[i];
		minNumber = max(arr[i], minNumber);
		maxNumber += arr[i];
	}

	cout << search();
	return 0;
}