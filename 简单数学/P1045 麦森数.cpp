#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

class BigInt {
public:
	vector<short> number;
	BigInt(): number(vector<short>(500)) {
		*this = 0;
	}
	BigInt(int n) : number(vector<short>(500)) {
		*this = n;
	}
	BigInt& operator=(int n) {
		int digest = 0;
		do {
			this->number[digest] = n % 10;
			digest++;
		} while (n /= 10);
		return *this;
	}
};

BigInt operator*(BigInt& a, BigInt& b) {
	BigInt result;

	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
			if (i + j < 500) {
				result.number[i + j] += a.number[i] * b.number[j];
				if (i + j + 1 < 500) {
					result.number[i + j + 1] += result.number[i + j] / 10;
				}
				result.number[i + j] %= 10;
			}
		}
	}

	return result;
}

int P = 0;

int main() {
	cin >> P;
	int digit = P * log10(2) + 1;
	cout << digit << endl;

	BigInt result = 1, pow = 2;
	while (P) {
		if (P & 1) {
			result = result * pow;
		}
		pow = pow * pow;
		P /= 2;
	}
	result.number[0] -= 1;

	int loop = 0;
	for (int i = 499; i >= 0; i--) {
		if (i >= digit) {
			cout << 0;
		}
		else {
			cout << result.number[i];
		}

		loop++;
		if (loop >= 50) {
			loop -= 50;
			cout << endl;
		}
	}

	return 0;
}