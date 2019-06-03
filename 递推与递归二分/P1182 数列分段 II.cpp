#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 100005;
int N, M;
int arr[MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline bool judge(int x) {
	int blocks = 0, currentSum = 0;
	for (int i = 1; i <= N;i++) {
		if (currentSum + arr[i] > x) {
			currentSum = arr[i];
			blocks++;
		}
		else {
			currentSum += arr[i];
		}
	}
	return blocks >= M;
}

inline int search(int l, int r) {
	while (l <= r) {
		int middle = (l + r) / 2;
		if (judge(middle)) {
			l = middle + 1;
		}
		else {
			r = middle - 1;
		}
	}
	return l;
}

int main() {
	int l = 0, r = 0;

	cin >> N >> M;
	for (int i = 1; i <= N;i++) {
		cin >> arr[i];

		r += arr[i];
		l = max(arr[i], l);
	}
	
	cout << search(l, r);
	return 0;
}