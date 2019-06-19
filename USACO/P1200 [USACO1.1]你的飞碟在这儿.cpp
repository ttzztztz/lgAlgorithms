#include<iostream>
#include<cstring>
using namespace std;

int main() {
	string s1, s2;
	cin >> s1 >> s2;

	int s1Sum = 1, s2Sum = 1;
	for (int i = 0; i < s1.length();i++) {
		s1Sum *= s1[i] - '@';
	}
	for (int i = 0; i < s2.length();i++) {
		s2Sum *= s2[i] - '@';
	}

	if (s1Sum % 47 == s2Sum % 47) {
		cout << "GO";
	}
	else {
		cout << "STAY";
	}

	return 0;
}