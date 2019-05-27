#include<iostream>
#include<algorithm>
using namespace std;

pair<long long,long long> arr[100];

int main() {
	int N = 0;
	cin >> N;

	int number = 0;
	string min = "";

	for (int i = 0; i < N;i++) {
		string s = "";
		cin >> s;

		if (s.length() > min.length() || (s.length() >= min.length() && s >= min)) {
			number = i + 1;
			min = s;
		}
	}

	cout << number << endl << min;

	
	return 0;
}