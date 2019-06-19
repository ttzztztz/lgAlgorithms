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
	BigInt(string s) {
		for (int i = s.length() - 1; i >= 0;i--) {
			this->number.push_back(s[i] - '0');
		}
	}
	BigInt& operator=(int n) {
		while (n) {
			this->number.push_back(n % 10);
			n /= 10;
		}
		return *this;
	}
};

int min(int x, int y) {
	return x < y ? x : y;
}

int max(int x, int y) {
	return x < y ? y : x;
}

BigInt operator+ (const BigInt& $1, const BigInt& $2) {
	BigInt result;

	bool flag = false;
	for (int i = 0; i < max($1.number.size(), $2.number.size());i++) {
		int tmp = 0;

		if (i < $1.number.size()) {
			tmp += $1.number[i];
		}
		if (i < $2.number.size()) {
			tmp += $2.number[i];
		}

		if (flag) {
			tmp += 1;
			flag = false;
		}
		if (tmp >= 10) {
			tmp -= 10;
			flag = true;
		}
		result.number.push_back(tmp);
	}
	if (flag) {
		result.number.push_back(1);
	}
	return result;
}

BigInt operator- (const BigInt& $1, const BigInt& $2) {
	BigInt result;
	bool flag = false;

	for (int i = 0; i < $1.number.size();i++) {
		int tmp = $1.number[i];

		if (i < $2.number.size()) {
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
		result.number.push_back(tmp);
	}

	int size = result.number.size();
	while (size && result.number[size - 1] == 0) {
		size--;
	}
	result.number.resize(size);

	return result;
}

bool operator<= (const BigInt& $1, const BigInt& $2) {
	if ($1.number.size() != $2.number.size()) {
		return $1.number.size() < $2.number.size();
	} else {
		for (int i = $1.number.size() - 1; i >= 0;i--) {
			if ($1.number[i] != $2.number[i]) {
				return $1.number[i] < $2.number[i];
			}
		}
	}

	return true;
}

ostream& operator<<(ostream& out, const BigInt& data) {
	for (int i = data.number.size() - 1; i >= 0;i--) {
		out << data.number[i];
	}
	return out;
}

int main() {
	string s1, s2;
	cin >> s1 >> s2;

	if (s1 == s2) {
		cout << 0;
		return 0;
	}

	if (s1[0] == '-' && s2[0] == '-') {
		BigInt $1(s1.substr(1, s1.length())), $2(s2.substr(1, s2.length()));
		if ($1 <= $2) {
			cout << ($2 - $1);
		}
		else {
			cout << '-' << ($1 - $2);
		}
	}
	else if (s1[0] == '-' && s2[0] != '-') {
		BigInt $1(s1), $2(s2);
		cout << '-' << ($1 + $2);
	}
	else if (s1[0] != '-' && s2[0] == '-') {
		BigInt $1(s1.substr(1, s1.length())), $2(s2.substr(1, s2.length()));
		BigInt result = $1 + $2;
		cout << result;
	}
	else if (s1[0] != '-' && s2[0] != '-') {
		BigInt $1(s1), $2(s2);

		if ($2 <= $1) {
			cout << ($1 - $2);
		}
		else {
			cout << '-' << ($2 - $1);
		}
	}

	return 0;
}