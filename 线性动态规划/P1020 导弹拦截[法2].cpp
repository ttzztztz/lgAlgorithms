#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int MAX = 100005;
int N = 0, number[MAX];

int main() {
	int n = 0;
	while (cin >> n) {
		number[N++] = n;
	}

	vector<int> stack;
	stack.push_back(number[0]);
	for (int i = 1; i < N;i++) {
		if (number[i] <= stack.back()) {
			stack.push_back(number[i]);
		}
		else {
			auto it = upper_bound(stack.begin(), stack.end(), number[i], greater<int>());
			*it = number[i];
		}
	}
	cout << stack.size() << endl;
	stack.clear();
	stack.push_back(number[0]);
	for (int i = 1; i < N; i++) {
		if (number[i] > stack.back()) {
			stack.push_back(number[i]);
		}
		else {
			auto it = lower_bound(stack.begin(), stack.end(), number[i]);
			*it = number[i];
		}
	}
	cout << stack.size();
	return 0;
}