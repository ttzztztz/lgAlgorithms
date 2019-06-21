#include<iostream>
using namespace std;

const int MAX = 1005;
int arr[MAX], N;

int min(int x, int y) {
	return x < y ? x : y;
}

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		cin >> arr[i];
	}

	int answer = 0x7fffffff;
	for (int i = 0; i <= 100 - 17;i++) {
		int tempAnswer = 0;

		for (int j = 0; j < N;j++) {
			if (arr[j] < i) {
				tempAnswer += (arr[j] - i) * (arr[j] - i);
			}

			if (arr[j] >= i + 17) {
				tempAnswer += (arr[j] - (i + 17)) * (arr[j] - (i + 17));
			}
		}
		answer = min(tempAnswer, answer);
	}
	cout << answer;
	return 0;
}