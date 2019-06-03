#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 100005;
int arr[MAX];
int A, B;

inline bool judge(int x) {
	int total = 1, number = 1;
	for (int i = 2; i <= A;i++) {
		if (arr[i] - arr[number] >= x) {
			total++;
			// 使最近的两个瓶盖距离最大
			number = i;
		}
		if (total >= B) {
			break;
		}
	}

	return total >= B;
}

inline int search() {
	int l = 1, r = arr[A] - arr[1];

	while (l <= r) {
		int middle = (l + r) / 2;
		if (judge(middle)) {
			l = middle + 1;
		}
		else {
			r = middle - 1;
		}
	}

	return l - 1;
}

int main() {
	cin >> A >> B;
	for (int i = 1; i <= A;i++) {
		cin >> arr[i];
	}
	sort(arr + 1, arr + A + 1);

	cout << search();
	return 0;
}