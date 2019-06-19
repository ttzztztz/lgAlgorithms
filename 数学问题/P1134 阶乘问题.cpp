#include<iostream>
using namespace std;

int N = 0;

int main() {
	cin >> N;

	long long number = 1;
	for (int i = 1; i <= N;i++) {
		number *= i;
		while (number && !(number % 10) && number >= 10) {
			number /= 10;
		}
		number %= 10000000000;
	}
	cout << number % 10;
	return 0;
}