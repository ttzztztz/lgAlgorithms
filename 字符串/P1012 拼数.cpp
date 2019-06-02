#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

string str[25];

int main() {
	int N = 0;
	cin >> N;
	for (int i = 0; i < N;i++) {
		cin >> str[i];
	}

	sort(str, str + N, [](string& $1, string& $2)->bool {
		return $1 + $2 > $2 + $1;
	});

	for (int i = 0; i < N;i++) {
		cout << str[i];
	}

	return 0;
}