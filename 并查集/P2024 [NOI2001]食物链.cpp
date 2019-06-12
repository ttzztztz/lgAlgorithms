#include<iostream>
using namespace std;

const int MAX = 150005;
int parent[MAX];
int N, K;

void init() {
	for (int i = 0; i < MAX;i++) {
		parent[i] = i;
	}
}

int findParent(int x) {
	if (parent[x] == x) {
		return x;
	}
	else {
		return parent[x] = findParent(parent[x]);
	}
}

void merge(int x, int y) {
	int parentX = findParent(x), parentY = findParent(y);
	parent[parentX] = parentY;
}

int main() {
	init();
	cin >> N >> K;
	int result = 0;

	for (int i = 0; i < K;i++) {
		int opt = 0, x = 0, y = 0;
		cin >> opt >> x >> y;

		if (x > N || y > N) {
			result++;
		}
		else if (x == y && opt == 2) {
			result++;
		}
		else {
			int parentX = findParent(x), parentY = findParent(y);

			if (opt == 1) {
				if (parentX == findParent(y + N) || findParent(x + N) == parentY) {
					result++;
				}
				else {
					merge(x, y);
					merge(x + N, y + N);
					merge(x + 2 * N, y + 2 * N);
				}
			}
			else if (opt == 2) {
				if (parentX == parentY || findParent(x + N) == parentY) {
					result++;
				}
				else {
					merge(x, y + N);
					merge(x + N, y + 2 * N);
					merge(x + 2 * N, y);
				}
			}
		}
	}

	cout << result;
	return 0;
}