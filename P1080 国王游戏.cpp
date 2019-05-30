#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class BigInt {
public:
	vector<short> v;
	BigInt() {
		*this = 0;
	}
	BigInt(int x) {
		*this = x;
	}

	BigInt& operator= (int x) {
		v.clear();
		do {
			v.push_back(x % 10);
		} while (x /= 10);
		return *this;
	}
	BigInt& operator=(const BigInt& x) {
		v.resize(x.v.size());
		memcpy(const_cast<short*>(v.data()), x.v.data(), x.v.size() * sizeof(short));
		return *this;
	}
};

ostream& operator<<(ostream& out, const BigInt& x) {
	for (int i = x.v.size() - 1; i >= 0; i--) {
		out << x.v[i];
	}
	return out;
}

BigInt operator+(const BigInt& a, const BigInt& b) {
	BigInt result;
	bool flag = false;
	for (int i = 0; i < max(a.v.size(), b.v.size()); i++) {
		int tmp = 0;
		if (i < a.v.size()) {
			tmp += a.v[i];
		}
		if (i < b.v.size()) {
			tmp += b.v[i];
		}
		if (flag) {
			tmp++;
			flag = false;
		}
		if (tmp >= 10) {
			tmp -= 10;
			flag = true;
		}
		result.v.push_back(tmp);
	}
	if (flag) {
		result.v.push_back(1);
	}

	return result;
}

BigInt& operator-(const BigInt& a, const BigInt& b) {
	BigInt result;
	bool flag = false;

	for (int i = 0; i < a.v.size(); i++) {
		int tmp = a.v[i];
		if (i < b.v.size()) {
			tmp -= b.v[i];
		}
		if (flag) {
			tmp--;
			flag = false;
		}
		if (tmp < 0) {
			tmp += 10;
			flag = true;
		}
		result.v.push_back(tmp);
	}

	int size = result.v.size();
	while (size && result.v[size - 1] == 0) {
		size--;
	}
	result.v.resize(size);

	return result;
}

BigInt& operator-(BigInt& a, const BigInt& b) {
	return a = a - b;
}

BigInt& operator+=(BigInt& a, const BigInt& b) {
	return a = a + b;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
	BigInt result;
	result.v.resize(a.v.size() + b.v.size());
	for (int i = 0; i < a.v.size(); i++) {
		for (int j = 0; j < b.v.size(); j++) {
			result.v[i + j] += a.v[i] * b.v[j];
			result.v[i + j + 1] += result.v[i + j] / 10;
			result.v[i + j] %= 10;
		}
	}

	int size = result.v.size();
	while (size && result.v[size - 1] == 0) {
		size--;
	}
	result.v.resize(size);

	return result;
}

BigInt operator*=(BigInt& a, const BigInt& b) {
	return a = a * b;
}

bool operator<(const BigInt& a, const BigInt& b) {
	int maxlen_a = a.v.size(), maxlen_b = b.v.size();
	if (maxlen_b != maxlen_a) {
		return maxlen_a < maxlen_b;
	}
	else {
		maxlen_a--; maxlen_b--;
		while (maxlen_a && maxlen_b) {
			short number_a = a.v[maxlen_a];
			short number_b = b.v[maxlen_b];

			maxlen_a--;
			maxlen_b--;

			if (number_a != number_b) {
				return number_a < number_b;
			}
		}
	}
}

bool operator>(const BigInt& a, const BigInt& b) {
	bool result = a < b;
	return !result;
}

class Person {
public:
	BigInt left, right;
	Person() :left(0), right(0) {};
	Person(BigInt l, BigInt r) : left(l), right(r) {};
};

const int MAX = 1005;
Person person[MAX];

int main() {
	int N;
	cin >> N;

	int kingLeft = 0, kingRight = 0;
	cin >> kingLeft >> kingRight;
	
	for (int i = 0; i < N;i++) {
		int left = 0, right = 0;
		cin >> left >> right;
		person[i] = { left, right };
	}

	sort(person, person + N, [](const Person& $1, const Person $2)->bool {
		return $1.left * $1.right < $2.left * $2.right;
	});

	BigInt left = kingLeft, right = kingRight;
	BigInt result = 0;
	for (int i = 0; i < N;i++) {
		Person& p = person[i];
		BigInt reward = left / p.right;
		left *= p.left;
		if (reward > result) {
			result = reward;
		}
	}
	cout << result;

	return 0;
}