#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

class Point {
public:
	double x, y;
	Point() :x(0), y(0) {};
	Point(double a, double b) : x(a), y(b) {};
};

class Edge {
public:
	int start, end, next;
	double weight;
	Edge() : start(0), end(0), weight(0.0), next(-1) {};
	Edge(int s, int e, double w, int n) : start(s), end(e), weight(w), next(n) {};
};

inline double calcDistance(Point& p1, Point& p2) {
	auto [x1, y1] = p1;
	auto [x2, y2] = p2;

	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline double min(double x, double y) {
	return x < y ? x : y;
}

const int MAX = 20;
Point pointList[MAX];
bool visited[MAX];
Edge edge[MAX * MAX];
int edgeCount = 0, N = 0;
int head[MAX];
double answer = 9999999999;

void dfs(int vertex, double result, int finishedCount) {
	if (result >= answer) {
		// 最优性剪枝
		return;
	}

	if (finishedCount == N) {
		answer = min(answer, result);
		return;
	}

	for (int i = head[vertex]; i != -1;i=edge[i].next) {
		Edge& e = edge[i];
		if (!visited[e.end]) {
			visited[e.end] = true;
			dfs(e.end, result + e.weight, finishedCount + 1);
			visited[e.end] = false;
		}
	}
}

int main() {
	memset(head, 0xff, sizeof(head));
	cin >> N;
	for (int i = 1; i <= N;i++) {
		cin >> pointList[i].x >> pointList[i].y;
	}
	
	for (int i = 0; i <= N;i++) {
		for (int j = 0; j < i;j++) {
			double dist = calcDistance(pointList[i], pointList[j]);
			
			edge[edgeCount] = { i, j, dist, head[i] };
			head[i] = edgeCount;
			edgeCount++;

			edge[edgeCount] = { j ,i , dist, head[j] };
			head[j] = edgeCount;
			edgeCount++;
		}
	}

	visited[0] = true;
	dfs(0, 0.0, 0);

	printf("%.2f", answer);

	return 0;
}