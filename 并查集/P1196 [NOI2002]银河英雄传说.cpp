#include<iostream>
using namespace std;

const int MAX = 30005;
int parent[MAX], numbers[MAX], weight[MAX], N;

void init() {
	for (int i = 0; i < MAX;i++) {
		parent[i] = i;
		numbers[i] = 1;
		weight[i] = 0;
	}
}

int findParent(int x) {
	if (parent[x] == x) {
		return x;
	}
	int rawParent = parent[x];
	int newParent = findParent(parent[x]);

	parent[x] = newParent;
	weight[x] += weight[rawParent];
	return newParent;
}

void merge(int x, int y) {
	int parentX = findParent(x), parentY = findParent(y);

	parent[parentX] = parentY;
	weight[parentX] = numbers[parentY];
	numbers[parentY] += numbers[parentX];
	numbers[parentX] = 0;
}

inline int _abs(int x) {
	if (x >= 0) {
		return x;
	}
	else {
		return -x;
	}
}

int main() {
	init();
	cin >> N;
	for (int i = 0; i < N;i++) {
		char command = '\0';
		int a = 0, b = 0;
		cin >> command >> a >> b;

		if (command == 'M') {
			merge(a, b);
		}
		else if (command == 'C') {
			int parentX = findParent(a), parentY = findParent(b);

			if (parentX != parentY) {
				cout << -1 << endl;
			}
			else {
				int answer = _abs(weight[a] - weight[b]) - 1;
				cout << answer << endl;
			}
		}
	}

	return 0;
}