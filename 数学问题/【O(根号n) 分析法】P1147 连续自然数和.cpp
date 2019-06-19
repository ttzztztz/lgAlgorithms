#include<iostream>
#include<cmath>
using namespace std;
int N = 0;

int main() {
	cin >> N;

	for (int k1 = sqrt(N * 2); k1 > 1;k1--) {
		int k2 = 2 * N / k1;
		if (2 * N % k1 == 0 && (k1 + k2) % 2) {
			int L = (k2 - k1 + 1) / 2, R = (k1 + k2 - 1) / 2;
			cout << L << " " << R << endl;
		}
	}

	return 0;
}