#include<iostream>
#include<cstring>
using namespace std;

enum Direction {
	L, R, U, D
};

class Point {
public:
	int x, y;
	Point() : x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
	bool operator==(const Point& p) const{
		return this->x == p.x && this->y == p.y;
	}
};

const int MAX = 1505;
int N, M;
char matrix[MAX][MAX];
bool visited[MAX][MAX];
Point src;

inline int _MOD(int x, int y) {
	if (x < 0) {
		x = -x;
	}
	return x % y;
}

Point nextPoint(Point curr, int dir) {
	switch (dir) {
		case L: curr.x--; break;
		case R: curr.x++; break;
		case U: curr.y--; break;
		case D: curr.y++; break;
	}
	return curr;
}

bool pointValid(Point ptr) {
	return matrix[_MOD(ptr.x, N)][_MOD(ptr.y, M)] != '#'
		&& !visited[_MOD(ptr.x, N)][_MOD(ptr.y, M)];
}

bool pointEdge(Point ptr) {
	return ptr.x == 0 || ptr.x == N + 1 || ptr.y == 0 || ptr.y == M + 1;
}

pair<bool,Point> pointEdgeCanGo(Point ptr) {
	if (ptr.x == 0) {
		ptr.x += N;
	}
	else if (ptr.x == N + 1) {
		ptr.x -= N;
	}
	else if (ptr.y == 0) {
		ptr.y += M;
	}
	else if (ptr.y == M + 1) {
		ptr.y -= M;
	}

	return { matrix[ptr.x][ptr.y] != '#', ptr };
}

bool dfs(Point now) {
	for (int i = 0; i < 4;i++) {
		Point next = nextPoint(now, i);
		bool valid = pointValid(next);

		if (!valid && pointEdge(next)) {
			auto [canGo, nextPtr] = pointEdgeCanGo(next);
			if (Point(_MOD(nextPtr.x, N), _MOD(nextPtr.y, M)) == src) {
				return true;
			}

			if (canGo) {
				return dfs(nextPtr);
			}
		}

		if (valid) {
			visited[_MOD(next.x, N)][_MOD(next.y, M)] = true;
			if (dfs(next)) {
				return true;
			}
			visited[_MOD(next.x, N)][_MOD(next.y, M)] = false;
		}
	}
	return false;
}

int main() {
	while (cin >> N >> M) {
		memset(matrix, 0, sizeof(matrix));
		memset(visited, 0, sizeof(matrix));
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M;j++) {
				cin >> matrix[i][j];

				if (matrix[i][j] == 'S') {
					src = { i,j };
					visited[i][j] = true;
				}
			}
		}

		if (dfs(src)) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
	return 0;
}