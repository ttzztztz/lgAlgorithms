#include<iostream>
using namespace std;

const int MAX = 300000;
int parent[MAX], ranks[MAX];

void init() {
	for (int i = 0; i < MAX;i++) {
		parent[i] = i;
		ranks[i] = 0;
	}
}

int findParent(int x) {
	if (parent[x] == x) {
		return x;
	}

	return parent[x] = findParent(parent[x]);
}

void merge(int x, int y) {
	int parentX = findParent(x), parentY = findParent(y);
	if (ranks[parentX] < ranks[parentY]) {
		parent[parentX] = parentY;
	}
	else {
		if (ranks[parentX] == ranks[parentY]) {
			ranks[parentX] ++;
		}
		parent[parentY] = parentX;
	}
}

int main() {
	int N = 0, M = 0;
	cin >> N >> M;

	init();

	for (int i = 0; i < M;i++) {
		int op, x, y;
		cin >> op >> x >> y;
		if (op == 1) {
			merge(x, y);
		}
		else if(op == 2) {
			cout << (findParent(x) == findParent(y) ? "Y" : "N") << endl;
		}
	}

	return 0;
}