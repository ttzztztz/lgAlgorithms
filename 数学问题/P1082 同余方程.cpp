#include<iostream>
using namespace std;

void exGcd(int a, int b, int& x, int& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return;
	}

	int x1 = 0, y1 = 0;
	exGcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - a / b * y1;
}

int main() {
	int x1 = 0, y1 = 0, a = 0, b = 0;
	cin >> a >> b;
	exGcd(a, b, x1, y1);

	cout << (x1 + b) % b;
	return 0;
}
