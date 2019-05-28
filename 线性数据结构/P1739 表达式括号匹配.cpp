#include<iostream>
#include<vector>
using namespace std;

int main() {
	char c = '\0';
	vector<int> v;
	bool failed = false;
	while ((cin >> c) && c != '@') {
		if (c == '(') {
			v.push_back(1);
		}
		else if (c == ')') {
			if (v.empty()) {
				failed = true;
				break;
			}
			else {
				v.pop_back();
			}
		}
	}

	if (failed || v.size()) {
		cout << "NO";
	}
	else {
		cout << "YES";
	}
	return 0;
}