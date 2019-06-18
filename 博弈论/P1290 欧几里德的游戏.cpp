#include<iostream>
using namespace std;

int max(int x, int y) {
	return x < y ? y : x;
}

int min(int x, int y) {
	return x < y ? x : y;
}

bool sg(int x, int y) {
	if (!y) {
		return false;
	}

	if (x / y == 1) {
		return !sg(y, x % y);
	}
	else {
		return true;
	}
}

int main() {
	int N = 0;
	cin >> N;

	for (int i = 0; i < N;i++) {
		int a = 0, b = 0;
		cin >> a >> b;

		if (sg(max(a, b), min(a, b))) {
			cout << "Stan wins" << endl;
		}
		else {
			cout << "Ollie wins" << endl;
		}
	}
	return 0;
}