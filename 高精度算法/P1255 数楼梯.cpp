#include<iostream>
#include<cstring>
using namespace std;

string add(string& s1, string& s2) {
	string resultStr = "";
	int s1_len = s1.length(), s2_len = s2.length();
	int maxLen = s1_len < s2_len ? s2_len : s1_len;

	int extra = 0;
	for (int i = 0; i < maxLen; i++) {
		int number1 = i >= s1.length() ? 0 : s1[s1_len - i - 1] - '0';
		int number2 = i >= s2.length() ? 0 : s2[s2_len - i - 1] - '0';

		int result = number1 + number2;
		if (extra) {
			result++;
			extra = 0;
		}
		if (result >= 10) {
			result -= 10;
			extra = 1;
		}

		resultStr = (char)(result + '0') + resultStr;
	}

	if (extra) {
		resultStr = "1" + resultStr;
	}

	return std::move(resultStr);
}

int main() {
	int number = 0;
	cin >> number;
	if (number == 1) {
		cout << 1;
	}
	else if (number == 0) {
		cout << 0;
	}
	else {
		string last1 = "1";
		string last2 = "1";
		string result = "0";
		for (int i = 2; i <= number; i++) {
			result = add(last1, last2);
			last1 = last2;
			last2 = result;
		}

		cout << result;
	}

	return 0;
}