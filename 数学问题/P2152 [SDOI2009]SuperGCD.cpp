#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;

inline int min(int x, int y) {
	return x < y ? x : y;
}

inline int max(int x, int y) {
	return x < y ? y : x;
}

class BigInt {
public:
	int number[10005];
	int size;
	BigInt() {
		this->size = 0;
		memset(this->number, 0, sizeof(this->number));
	}
	BigInt(int x) {
		memset(this->number, 0, sizeof(this->number));
		int offset = 0;
		while (x) {
			this->number[offset] = x % 10;
			x /= 10;
			offset++;
		}
		this->size = offset;
	}
};

BigInt operator- (const BigInt& $1, const BigInt& $2) {
	BigInt result;
	bool flag = false;

	for (int i = 0; i < $1.size; i++) {
		int tmp = $1.number[i];

		if (i < $2.size) {
			tmp -= $2.number[i];
		}
		if (flag) {
			tmp--;
			flag = false;
		}
		if (tmp < 0) {
			tmp += 10;
			flag = true;
		}
		result.number[i] = tmp;
	}

	int size = max($1.size, $2.size);
	while (size && result.number[size - 1] == 0) {
		size--;
	}
	result.size = size;

	return std::move(result);
}

void div2(BigInt& $1) {
	bool haveOne = false;
	for (int i = $1.size - 1; i >= 0;i--) {
		bool newHaveOne = $1.number[i] & 1;
		if (haveOne) {
			$1.number[i] += 10;
			haveOne = false;
		}
		$1.number[i] >>= 1;
		if (newHaveOne) {
			haveOne = newHaveOne;
		}
	}

	int size = $1.size;
	while ($1.number[size - 1] == 0) {
		size--;
	}
	$1.size = size;
}

bool operator< (const BigInt& $1, const BigInt& $2) {
	if ($1.size != $2.size) {
		return $1.size < $2.size;
	}
	else {
		for (int i = $1.size - 1; i >= 0; i--) {
			if ($1.number[i] != $2.number[i]) {
				return $1.number[i] < $2.number[i];
			}
		}
	}
	return false;
}

bool operator==(const BigInt& $1, const BigInt& $2) {
	if ($1.size != $2.size) {
		return false;
	}
	else {
		for (int i = $1.size - 1; i >= 0; i--) {
			if ($1.number[i] != $2.number[i]) {
				return false;
			}
		}
	}
	return true;
}

inline void outputData(const BigInt& data) {
	for (int i = data.size - 1; i >= 0; i--) {
		printf("%d", data.number[i]);
	}
}

inline bool canDiv2(BigInt& $1) {
	int number = $1.number[0];
	return !(number % 2);
}

inline void mul2(BigInt& number) {
	int more = 0;
	for (int i = 0; i < number.size;i++) {
		number.number[i] = number.number[i] * 2 + more;
		if (number.number[i] >= 10) {
			more = number.number[i] / 10;
			number.number[i] %= 10;
			if (i == number.size - 1) {
				number.size++;
			}
		}
		else {
			more = 0;
		}
	}
}

BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt result;

	for (int i = 0; i < a.size; i++) {
		for (int j = 0; j < b.size; j++) {
			result.number[i + j] += a.number[i] * b.number[j];
			result.number[i + j + 1] += result.number[i + j] / 10;
			result.number[i + j] %= 10;
		}
	}

	int size = a.size + b.size;
	while (size && result.number[size - 1] == 0) {
		size--;
	}
	result.size = size;

	return std::move(result);
}

char str1[10005], str2[10005];
BigInt b1, b2;

int main() {
	scanf("%s%s",str1, str2);

	int len1 = strlen(str1), len2 = strlen(str2);
	for (int i = len1 - 1; i >= 0;i--) {
		b1.number[len1 - i - 1] = str1[i] - '0';
	}
	for (int i = len2 - 1; i >= 0; i--) {
		b2.number[len2 - i - 1] = str2[i] - '0';
	}
	b1.size = len1;
	b2.size = len2;

	int count = 0;
	while (!(b1 == b2)) {
		bool check1 = canDiv2(b1), check2 = canDiv2(b2);

		if (check1 && check2) {
			div2(b1);
			div2(b2);
			count++;
		}
		else if (check1 && !check2) {
			div2(b1);
		}
		else if (!check1 && check2) {
			div2(b2);
		}
		else {
			if (b1 < b2) {
				b2 = b2 - b1;
			}
			else {
				b1 = b1 - b2;
			}
		}
	}

	for (int i = 0; i < count;i++) {
		mul2(b1);
	}
	outputData(b1);
	return 0;
}