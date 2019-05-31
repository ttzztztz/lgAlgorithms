#include<iostream>
#include<deque>
#include<cstring>
using namespace std;

enum State {
	unvisited, visited
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

const int MAX = 1005;
int map[MAX][MAX], visit[MAX][MAX], record[MAX][MAX];
int connectedBlockCount[100005];
int N;

inline void init(Point& startPoint) {
	memset(visit, 0, sizeof(visit));
	visit[startPoint.x][startPoint.y] = visited;
}

inline bool validPoint(Point& src, Point& p) {
	bool first = p.x >= 0 && p.y >= 0 && p.x < N && p.y < N && visit[p.x][p.y] == unvisited;
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

inline int bfs(Point p, int block) {
	init(p);

	deque<Point> queue;
	int result = 0;

	queue.push_back(p);
	while (!queue.empty()) {
		Point src = queue.front();
		record[src.x][src.y] = block;
		result++;
		queue.pop_front();

		for (int i = 0; i < 4;i++) {
			Point next = movePoint(src, i);
			if (validPoint(src, next)) {
				visit[next.x][next.y] = visited;
				queue.push_back(next);
			}
		}
	}

	connectedBlockCount[block] = result;
	return result;
}

int main() {
	int m = 0;
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

		if (record[x][y]) {
			cout << connectedBlockCount[record[x][y]] << endl;
		}
		else {
			int result = bfs({ x, y }, i + 1);
			cout << result << endl;
		}
	}
	return 0;
}