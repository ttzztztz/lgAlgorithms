#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

class BigInt {
public:
	vector<int> number;
	BigInt() {
		*this = 0;
	}
	BigInt(int x) {
		*this = x;
	}
	BigInt& operator= (int x) {
		number.clear();
		do {
			number.push_back(x % 10);
		} while (x /= 10);
		return *this;
	}
	friend ostream& operator<<(ostream& stream, BigInt& $1) {
		if ($1.number.size() == 0) {
			stream << 0;
		}
		else {
			for (int i = $1.number.size() - 1; i >= 0; i--) {
				stream << $1.number[i];
			}
		}
		return stream;
	}
	BigInt& operator=(const BigInt& x) {
		number.resize(x.number.size());
		memcpy(const_cast<int*>(number.data()), x.number.data(), x.number.size() * sizeof(int));
		return *this;
	}
};

inline BigInt max(BigInt $1, BigInt $2) {
	int size_1 = $1.number.size(), size_2 = $2.number.size();
	if (size_1 != size_2) {
		return size_1 < size_2 ? $2 : $1;
	}
	else {
		bool $1_greater_$2 = false;
		for (int offset = size_1 - 1; offset >= 0; offset--) {
			if ($1.number[offset] > $2.number[offset]) {
				$1_greater_$2 = true;
				break;
			}
			else if ($1.number[offset] < $2.number[offset]) {
				break;
			}
		}

		if ($1_greater_$2) {
			return $1;
		}
		else {
			return $2;
		}
	}
}

inline int max(int x, int y) {
	return x < y ? y : x;
}

BigInt operator+(const BigInt& $1, const BigInt& $2) {
	BigInt result;
	int len = max($1.number.size(), $2.number.size());
	result.number.resize(len + 1);

	bool haveExtra = false;
	for (int i = 0; i < len; i++) {
		int number = 0;
		if ($1.number.size() > i) {
			number += $1.number[i];
		}
		if ($2.number.size() > i) {
			number += $2.number[i];
		}

		if (haveExtra) {
			number++;
			haveExtra = false;
		}

		if (number >= 10) {
			number -= 10;
			haveExtra = true;
		}
		result.number[i] = number;
	}

	if (haveExtra) {
		result.number[len] = 1;
	}
	int size = result.number.size();
	while (size > 1 && result.number[size - 1] == 0) {
		size--;
	}
	result.number.resize(size);
	return result;
}

BigInt operator*(const BigInt& $1, const BigInt& $2) {
	BigInt result;
	int len = $1.number.size() + $2.number.size();
	result.number.resize(len);

	for (int i = 0; i < $1.number.size(); i++) {
		for (int j = 0; j < $2.number.size(); j++) {
			result.number[i + j] += $1.number[i] * $2.number[j];
			result.number[i + j + 1] += result.number[i + j] / 10;
			result.number[i + j] %= 10;
		}
	}

	int size = result.number.size();
	while (size > 1 && result.number[size - 1] == 0) {
		size--;
	}
	result.number.resize(size);
	return result;
}

const int MAX = 85;
int N, M;
BigInt matrix[MAX][MAX], pow2[MAX];
BigInt dp[MAX][MAX][MAX];

void fastPow2() {
	BigInt curr = 1;

	pow2[0] = 1;
	for (int i = 1; i < MAX;i++) {
		curr = curr * 2;
		pow2[i] = curr;
	}
}

int main() {
	fastPow2();
	cin >> N >> M;
	for (int i = 1; i <= N;i++) {
		for (int j = 1; j <= M;j++) {
			int number = 0;
			cin >> number;
			matrix[i][j] = number;
		}
	}

	for (int k = 1; k <= N; k++) {
		for (int L = M; L >= 1; L--) {
			for (int i = 1; L + i - 1 <= M; i++) {
				int j = L + i - 1;

				dp[k][i][j] = max(
					dp[k][i][j + 1] + (pow2[M - L] * matrix[k][j + 1]),
					dp[k][i][j]
				);

				dp[k][i][j] = max(
					dp[k][i][j],
					dp[k][i - 1][j] + (pow2[M - L] * matrix[k][i - 1])
				);
			}
		}
	}

	BigInt answer = 0;
	for (int k = 1; k <= N;k++) {
		BigInt temp = 0;
		for (int i = 1; i <= M;i++) {
			temp = max(temp, dp[k][i][i] + (pow2[M] * matrix[k][i]));
		}
		answer = answer + temp;
	}
	cout << answer;
	return 0;
}
