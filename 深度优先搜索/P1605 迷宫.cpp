#include<iostream>
#include<cstring>
using namespace std;

class Point {
public:
	int x, y;
	Point() :x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
	bool operator== (const Point& p) const {
		return p.x == this->x && p.y == this->y;
	}
};

enum Direction {
	L, R, U, D
};

enum Road {
	unvisited, visited, block
};

const int MAX = 10;
const int directionCount = 4;
int map[MAX][MAX];
int M, N, T;
Point src, target;
int result = 0;

Point movePoint(Point p, int relation) {
	switch (relation) {
		case L: p.x--; break;
		case R: p.x++; break;
		case U: p.y--; break;
		case D: p.y++; break;
	}
	return p;
}

bool validPoint(Point p) {
	return p.x >= 1 && p.y >= 1 && p.x <= N && p.y <= M && map[p.x][p.y] == unvisited;
}

void init() {
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < M;j++) {
			if (map[i][j] == visited) {
				map[i][j] = unvisited;
			}
		}
	}

	map[src.x][src.y] = visited;
}

void dfs(Point p) {
	if (p == target) {
		result++;
		return;
	}

	for (int i = 0; i < directionCount;i++) {
		Point next = movePoint(p, i);

		if (validPoint(next)) {
			map[next.x][next.y] = visited;
			dfs(next);
			map[next.x][next.y] = unvisited;
		}
		
	}
}

int main() {
	cin >> N >> M >> T;
	
	cin >> src.x >> src.y >> target.x >> target.y;

	for (int i = 0; i < T;i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		map[x][y] = block;
	}

	init();
	dfs(src);

	cout << result;

	return 0;
}