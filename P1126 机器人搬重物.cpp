#include<iostream>
using namespace std;

class Point {
public:
	int x, y;
	Point() : x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
};

class State {
public:
	Point point;
	char direction;
	State() : point({ 0, 0 }), direction('L') {};
};

int map[55][55];
int N, M;
Point src, target;
State currentState;

bool validPoint(Point& point) {
	bool b1 = point.x >= 0 && point.y >= 0 && point.x <= N && point.y <= M;
	bool b2 = !map[point.x][point.y] && !map[point.x][point.y - 1] && !map[point.x + 1][point.y] && !map[point.x + 1][point.y - 1];

	return b1 && b2;
}

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N;i++) {
		for (int j = 1; j <= M;j++) {
			cin >> map[i][j];
		}
	}

	cin >> src.x >> src.y;
	cin >> target.x >> target.y;
	currentState.point = src;
	cin >> currentState.direction;



	return 0;
}