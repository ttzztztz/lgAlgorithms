#include<iostream>
using namespace std;

const int MAX = 100;
int numbers[MAX];

int main() {
	int N = 0;
	cin >> N;
	for (int i = 0; i < N;i++) {
		cin >> numbers[i];
	}

	int count = 0;
	for (int i = 0; i < N;i++) {
		if (numbers[i] == 0) {
			if (count & 1) {
				cout << "YES";
				return 0;
			}
			break;
		}
		else {
			count++;
		}
	}

	count = 0;

	for (int i = N - 1; i >= 0; i--) {
		if (numbers[i] == 0) {
			if (count & 1) {
				cout << "YES";
				return 0;
			}
			break;
		}
		else {
			count++;
		}
	}
	cout << "NO";
	return 0;
}