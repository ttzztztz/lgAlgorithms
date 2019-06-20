#include<iostream>
#include<cstring>
using namespace std;

const int MOD = 1000000007;
long long N, k;
class Matrix {
public:
	long long number[105][105];
	Matrix(){
		memset(this->number, 0, sizeof(this->number));
	}
};

Matrix operator*(Matrix& $1, Matrix& $2){
	Matrix result;
	for (int i = 1; i <= N;i++) {
		for (int j = 1; j <= N;j++) {
			for (int k = 1; k <= N;k++) {
				result.number[i][j] = (result.number[i][j] + 
					$1.number[i][k] * $2.number[k][j]
				) % MOD;
			}
		}
	}
	return result;
}

Matrix fastPow(Matrix& a, long long b) {
	Matrix base = a, result;
	for (int i = 1; i <= N;i++) {
		result.number[i][i] = 1;
	}
	while (b) {
		if (b & 1) {
			result = result * base;
		}

		base = base * base;
		b >>= 1;
	}
	return result;
}

int main() {
	cin >> N >> k;
	Matrix start;
	for (int i = 1; i <= N;i++) {
		for (int j = 1; j <= N;j++) {
			cin >> start.number[i][j];
		}
	}
	Matrix result = fastPow(start, k);
	for (int i = 1; i <= N;i++) {
		for (int j = 1; j <= N;j++) {
			cout << result.number[i][j] % MOD << " ";
		}
		cout << endl;
	}
	return 0;
}