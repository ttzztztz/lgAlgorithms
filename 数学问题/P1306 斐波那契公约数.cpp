#include<iostream>
#include<cstring>
using namespace std;

const int MOD = 100000000;

class Matrix {
public:
	long long number[3][3];
	Matrix(){
		memset(this->number, 0, sizeof(this->number));
	}
};

Matrix operator*(Matrix& $1, Matrix& $2){
	Matrix result;
	for (int i = 1; i <= 2;i++) {
		for (int j = 1; j <= 2;j++) {
			for (int k = 1; k <= 2;k++) {
				result.number[i][j] = (result.number[i][j] + 
					$1.number[i][k] * $2.number[k][j]
				) % MOD;
			}
		}
	}
	return result;
}

Matrix fastPow(Matrix& a, int b) {
	Matrix base = a, result;
	result.number[1][1] = result.number[2][2] = 1;

	while (b) {
		if (b & 1) {
			result = result * base;
		}

		base = base * base;
		b >>= 1;
	}
	return result;
}

int gcd(int x, int y) {
	if (y == 0) {
		return x;
	}
	return gcd(y, x % y);
}

int main() {
	Matrix matrix;
	matrix.number[1][1] = matrix.number[1][2] = matrix.number[2][1] = 1;
	matrix.number[2][2] = 0;

	int m = 0, n = 0;
	cin >> m >> n;
	int _gcd = gcd(m, n);
	
	if (_gcd <= 2) {
		cout << 1;
	}
	else {
		matrix = fastPow(matrix, _gcd - 1);
		cout << matrix.number[1][1];
	}

	return 0;
}