#include<iostream>
#include<cstring>
using namespace std;

void solve(string middle, string after) {
	if (middle.size() && after.size()) {
		char root = after.back();
		cout << root;

		int position = middle.find(root);
		solve(middle.substr(0, position), after.substr(0, position));
		solve(middle.substr(position + 1), after.substr(position, after.size() - 1 - position));
	}
}

int main() {
	string middle, after;
	cin >> middle >> after;
	solve(middle, after);

	return 0;
}