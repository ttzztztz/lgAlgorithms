#include<iostream>
#include<algorithm>
using namespace std;

int arr[20];
int N = 0, solutions = 0;

int fabs(int a) {
	return a < 0 ? -a : a;
}

int check(int curr) {
	for (int i = 1; i < curr;i++) {
		if (arr[i] == arr[curr] || fabs( i - curr ) == fabs(arr[i] - arr[curr]) ) {
			return 1;
		}
	}
	return 0;
}

void calculate(int curr) {
	if (curr == N + 1) {
		solutions++;
		if (solutions <= 3) {
			for (int i = 1; i <= N; i++) {
				if (i == N) {
					cout << arr[i] << endl;
				}
				else {
					cout << arr[i] << " ";
				}
			}
		}
	}
	else {
		for (int i = 1; i <= N; i++) {
			arr[curr] = i;
			if (check(curr)) {
				continue;
			}
			calculate(curr + 1);
		}
	}
}

int main() {
	cin >> N;
	calculate(1);
	cout << solutions;
	return 0;
}