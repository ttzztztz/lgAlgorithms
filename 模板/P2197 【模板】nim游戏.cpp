#include<iostream>
using namespace std;

int main() {
	int T = 0;
	cin >> T;
	for (int i = 0; i < T;i++) {
		int N = 0, result = 0;
		cin >> N;
		for (int j = 0; j < N;j++) {
			int number = 0;
			cin >> number;
			result ^= number;
		}
		if (result) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}

	return 0;
}