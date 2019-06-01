#include<iostream>
using namespace std;

enum Direction {
	Left, Right, Up, Down
};

class Point {
public:
	int x, y;
	Point() :x(0), y(0) {};
	Point(int a, int b) : x(a), y(b) {};
	bool operator== (const Point& p) const {
		return this->x == p.x && this->y == p.y;
	}
};

const int MAX = 105;
int R, C;
int map[MAX][MAX];
int dp[MAX][MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline int min(int x, int y) {
	return x < y ? x : y;
}

Point movePoint(Point p, int relation) {
	switch (relation) {
		case Left: p.x--; break;
		case Right: p.x++; break;
		case Up: p.y--; break;
		case Down: p.y++; break;
	}
	return p;
}

bool validPoint(Point p) {
	return p.x >= 1 && p.y >= 1 && p.x <= R && p.y <= C;
}

int dfs(Point p) {
	if (dp[p.x][p.y] != 1) {
		return dp[p.x][p.y];
	}

	int maxLen = 0;
	for (int i = 0; i < 4;i++) {
		Point next = movePoint(p, i);
		if (validPoint(next) && map[p.x][p.y] > map[next.x][next.y]) {
			maxLen = max(maxLen, dfs(next) + 1);
		}
	}

	// 防止无法移动点，maxLen = 0的情况
	dp[p.x][p.y] = max(dp[p.x][p.y], maxLen);
	return maxLen;
}

// 不一定是 最高处 到 最低处 ！
int main() {
	cin >> R >> C;

	for (int i = 1; i <= R;i++) {
		for (int j = 1; j <= C;j++) {
			cin >> map[i][j];
			dp[i][j] = 1;
		}
	}

	int result = 0;
	for (int i = 1; i <= R;i++) {
		for (int j = 1; j <= C;j++) {
			result = max(result, dfs({i, j}) + 1);
		}
	}
	cout << result;
	return 0;
}