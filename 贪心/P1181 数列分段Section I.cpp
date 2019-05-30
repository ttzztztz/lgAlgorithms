#include<iostream>
using namespace std;

int N, M;
int main() {
	cin >> N >> M;

	int total = 0, result = 0;

	for (int i = 0; i < N;i++) {
		int number = 0;
		cin >> number;

		total += number;
		if (total == M) {
			total = 0;
			result++;
		}
		else if (total > M) {
			total = number;
			result++;
		}

	}

	if (total != 0) {
		result++;
	}
	cout << result;

	return 0;
}