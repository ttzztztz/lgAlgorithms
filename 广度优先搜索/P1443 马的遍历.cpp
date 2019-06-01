#include<iostream>
#include<deque>
#include<cstring>
using namespace std;

enum Position{
	A, B, C, D, E, F, G, H
};

class Point {
public:
	int x, y;
	Point() : x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
};

class Item {
public:
	Point point;
	int dist;
	Item(Point p, int d) : point(p), dist(d) {};
};

const int MAX = 405;
int n, m;
int dist[MAX][MAX];

inline Point nextPoint(Point p, int position) {
	switch (position) {
		case A: p.x -= 1; p.y -= 2; break;
		case B: p.x += 1; p.y -= 2; break;
		case C: p.x -= 2; p.y -= 1; break;
		case D: p.x += 2; p.y -= 1; break;
		case E: p.x -= 2; p.y += 1; break;
		case F: p.x -= 1; p.y += 2; break;
		case G: p.x += 1; p.y += 2; break;
		case H: p.x += 2; p.y += 1; break;
	}
	return p;
}

inline bool checkPoint(Point& p) {
	bool check1 = p.x >= 1 && p.x <= n && p.y >= 1 && p.y <= m;
	bool check2 = dist[p.x][p.y] == -1;

	return check1 && check2;
}

void bfs(Point start) {
	deque<Item> queue;
	queue.push_back({ start, 0 });

	while (!queue.empty()) {
		auto [p ,d] = queue.front();
		queue.pop_front();

		for (int i = 0; i < 8;i++) {
			Point next = nextPoint(p, i);
			if (checkPoint(next)) {
				dist[next.x][next.y] = d + 1;
				queue.push_back({ next, d + 1 });
			}
		}
	}
}

int main() {
	cin >> n >> m;
	Point start;
	cin >> start.x >> start.y;
	memset(dist, 0xff, sizeof(dist));

	dist[start.x][start.y] = 0;
	bfs(start);

	for (int i = 1; i <= n;i++) {
		for (int j = 1; j <= m;j++) {
			printf("%-5d", dist[i][j]);
		}
		printf("\n");
	}

	return 0;
}