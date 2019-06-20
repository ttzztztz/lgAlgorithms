#include<iostream>
#include<map>
#include<cstring>
using namespace std;

map<string, bool> exist;
string charset[] = { "","","ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY" };
string N;
bool outputed = false;

void find(int number, string str) {
	if (number >= N.size()) {
		if (exist[str]) {
			outputed = true;
			cout << str << endl;
		}
		return;
	}

	string s = charset[N[number] - '0'];
	for (int i = 0; i < 3;i++) {
		find(number + 1, str + s[i]);
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < 4617;i++) {
		string s;
		cin >> s;
		exist[s] = true;
	}

	find(0, "");

	if (!outputed) {
		cout << "NONE";
	}

	return 0;
}