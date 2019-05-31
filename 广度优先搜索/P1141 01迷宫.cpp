#include<iostream>
#include<deque>
#include<cstring>
using namespace std;

const int MAX = 1005;
int map[MAX][MAX];
int N;
int parent[2000005], number[2000005];

enum Direction {
	L, R, U, D
};

class Point {
public:
	int x, y;
	Point() :x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
};

inline bool validPoint(Point& src, Point& p) {
	bool first = p.x >= 0 && p.y >= 0 && p.x < N && p.y < N;
	bool second = map[p.x][p.y] ^ map[src.x][src.y];

	return first && second;
}

inline Point movePoint(Point p, int direction) {
	switch (direction) {
		case L: p.x--; break;
		case R: p.x++; break;
		case U: p.y--; break;
		case D: p.y++; break;
	}
	return p;
}

int find(int x) {
	if (parent[x] == x) {
		return parent[x];
	}
	else {
		return parent[x] = find(parent[x]);
	}
}

void merge(int x, int y) {
	int parentX = find(x), parentY = find(y);
	if (parentX != parentY) {
		parent[parentX] = parentY;
		number[parentY] += number[parentX];
	}
}

int dfs(Point p) {
	auto [x, y] = p;

	if (parent[x * N + y] != -1) {
		return find(x * N + y);
	}

	parent[x * N + y] = x * N + y;
	number[x * N + y] = 1;
	for (int i = 0; i < 4;i++) {
		Point next = movePoint({ x, y }, i);
		if (validPoint(p, next)) {
			merge(x * N + y, dfs(next));
		}
	}

	return find(x * N + y);
}

int main() {
	int m = 0;

	memset(parent, 0xff, sizeof(number));

	cin >> N >> m;
	char cache[MAX];

	for (int i = 0; i < N;i++) {
		cin >> cache;
		for (int j = 0; j < N;j++) {
			map[i][j] = cache[j] - '0';
		}
	}


	for (int i = 0; i < m;i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		x--; y--;

		cout << number[dfs({ x, y })] << endl;
	}
	return 0;
}