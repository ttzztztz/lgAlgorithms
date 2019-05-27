#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 5e5 + 10;
const int ARR_MAX = 6e6;
long long arr[ARR_MAX];
pair<int, int> list[MAX];

int lowbit(int x) {
	return x & (-x);
}

long long query(int x) {
	long long result = 0;
	while (x) {
		result += arr[x];
		x -= lowbit(x);
	}
	return result;
}

void add(int x, long long number) {
	while (x && x< ARR_MAX) {
		arr[x] += number;
		x += lowbit(x);
	}
}

int main() {
	ios::sync_with_stdio(false);

	int N = 0;
	cin >> N;

	for (int i = 1; i <= N;i++) {
		int number = 0;
		cin >> number;
		list[i - 1] = { i , number };
	}

	sort(list, list + N, [](pair<int, int>& $1, pair<int, int>& $2)->bool {
		if ($1.second != $2.second) {
			return $1.second < $2.second;
		}
		else {
			return $1.first < $2.first;
		}
	});

	long long result = 0;
	for (int i = N - 1; i >= 0;i--) {
		int rank = list[i].first;
		add(rank, 1);
		result += query(rank - 1);
	}
	cout << result;
	return 0;
}