#include<iostream>
using namespace std;

const int MAX = 200005;
int parent[MAX], dist[MAX], arr[MAX];
int N, answer = 0x7fffffff;

inline int min(int x, int y) {
	return x < y ? x : y;
}

inline void init() {
	for (int i = 0; i < MAX;i++) {
		parent[i] = i;
	}
}

inline int check(int x) {
	if (parent[x] != x) {
		int parentX = parent[x];
		parent[x] = check(parentX);
		dist[x] += dist[parentX];
	}
	return parent[x];
}

inline void merge(int x, int y){
	int parentX = check(x), parentY = check(y);
	if (parentX == parentY) {
		answer = min(answer, dist[x] + dist[y] + 1);
	}
	else {
		parent[parentX] = parentY;
		dist[x] = dist[y] + 1;
	}
}

int main() {
	cin >> N;
	for (int i = 1; i <= N;i++) {
		cin >> arr[i];
	}

	init();
	for (int i = 1; i <= N;i++) {
		int start = i, end = arr[i];
		merge(start, end);
	}
	cout << answer;
	return 0;
}
