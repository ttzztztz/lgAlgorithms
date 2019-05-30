#include<iostream>
#include<queue>
#include<vector>
using namespace std;

const int MAX = 10005;
int N;

int main() {
	cin >> N;
	priority_queue<int, vector<int>, greater<int>> queue;

	for (int i = 0; i < N;i++) {
		int number = 0;
		cin >> number;
		queue.push(number);
	}

	int result = 0;
	while (queue.size() > 1) {
		int heap1 = queue.top(); queue.pop();
		int heap2 = queue.top(); queue.pop();
		result += heap1 + heap2;
		queue.push(heap1 + heap2);
	}
	
	cout << result;
	return 0;
}