#include<iostream>
using namespace std;

enum State {
	unvisited, border, outer
};

enum Direction {
	L, R, U, D
};

class Point {
public:
	int x, y;
	Point() :x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
};

const int MAX = 35;
int N;
int map[MAX][MAX];

Point movePoint(Point p, int direction) {
	switch (direction) {
		case L: p.x--; break;
		case R: p.x++; break;
		case U: p.y--; break;
		case D: p.y++; break;
	}
	return p;
}

bool validPoint(Point p) {
	return p.x >= 0 && p.x < N && p.y >= 0 && p.y < N && map[p.x][p.y] == unvisited;
}

void dfs(Point p) {
	if (validPoint(p)) {
		map[p.x][p.y] = outer;

		for (int i = 0; i < 4; i++) {
			Point next = movePoint(p, i);
			if (validPoint(next)) {
				dfs(next);
			}
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < N;j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N;i++) {
		dfs({ 0, i });
		dfs({ i, 0 });
		dfs({ i, N - 1 });
		dfs({ N - 1, i });
	}


	for (int i = 0; i < N;i++) {
		for (int j = 0; j < N;j++) {
			switch (map[i][j]) {
				case unvisited: cout << 2; break;
				case border: cout << 1; break;
				case outer: cout << 0; break;
			}
			if (j != N - 1) {
				cout << " ";
			}
		}
		cout << endl;
	}

	return 0;
}