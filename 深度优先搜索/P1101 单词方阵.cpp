#include<iostream>
using namespace std;

const char* target = "yizhong";
const int length = 7;
const int directions = 8;
char map[105][105], resultMap[105][105];
int dimension;

class Point {
public:
	int x, y;
	Point() :x(0), y(0) {};
	Point(int a, int b) :x(a), y(b) {};
};

enum Direction {
	L, R, U, D, LU, RU, LD, RD
};

Point movePoint(Point p, int direction) {
	switch (direction) {
		case L: p.x--; break;
		case R: p.x++; break;
		case U: p.y--; break;
		case D: p.y++; break;
		case LU: p.x--; p.y--; break;
		case RU: p.x++; p.y--; break;
		case LD: p.x--; p.y++; break;
		case RD: p.x++; p.y++; break;
	}
	return p;
}

void search(Point start, int direction) {
	Point p = movePoint(start, direction);
	bool OK = true;

	for (int i = 1; i < length;i++) {
		if (   p.x < 0 || p.y < 0 || p.x >= dimension || p.y>= dimension
			|| map[p.x][p.y] != target[i]
			) {
			OK = false;
			break;
		}
		p = movePoint(p, direction);
	}

	if (OK) {
		for (int i = 0; i < length;i++) {
			resultMap[start.x][start.y] = target[i];
			start = movePoint(start, direction);
		}
	}
}

int main() {
	cin >> dimension;
	for (int i = 0; i < dimension;i++) {
		for (int j = 0; j < dimension;j++) {
			cin >> map[i][j];
			resultMap[i][j] = '*';
		}
	}

	for (int i = 0; i < dimension;i++) {
		for (int j = 0; j < dimension;j++) {
			if (map[i][j] == target[0]) {
				for (int m = 0; m < directions;m++) {
					Point p = movePoint({ i, j }, m);
					if (map[p.x][p.y] == target[1]) {
						search({ i,j }, m);
					}
				}
			}
		}
	}

	for (int i = 0; i < dimension;i++) {
		for (int j = 0; j < dimension;j++) {
			cout << resultMap[i][j];
		}
		cout << endl;
	}

	return 0;
}