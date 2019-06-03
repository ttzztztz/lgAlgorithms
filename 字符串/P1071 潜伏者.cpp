#include<iostream>
#include<cstring>
#include<map>
using namespace std;

map<char, char> reflection;

map<char, char> usedChar;

int main() {
	string $1, $2;
	cin >> $1 >> $2;
	for (int i = 0; i < $1.length();i++) {
		char ch1 = $1[i], ch2 = $2[i];
		if ((reflection.count(ch1) && reflection[ch1] != ch2) || (usedChar.count(ch2) && usedChar[ch2] != ch1)) {
			cout << "Failed";
			return 0;
		}
		else {
			reflection[ch1] = ch2;
			usedChar[ch2] = ch1;
		}
	}

	if (reflection.size() != 26) {
		cout << "Failed";
		return 0;
	}

	string $3;
	cin >> $3;
	for (int i = 0; i < $3.length();i++) {
		char ch = $3[i];
		if (reflection.count(ch)) {
			cout << reflection[ch];
		}
		else {
			cout << "Failed";
			return 0;
		}
	}
	
	return 0;
}