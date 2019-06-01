#include<iostream>
#include<queue>
using namespace std;

class Edge {
public:
	int toVertex, times;
	Edge() : toVertex(0), times(0) {};
	Edge(int to, int t) : toVertex(to), times(t) {};
};

int N, A, B;
int edgeInfo[205];
bool visited[205];
// 使用visited 判断是否成环

inline int bfs() {
	queue<Edge> queue;
	queue.push({ A, 1 });

	while (!queue.empty()) {
		auto [toVertex, nowTimes] = queue.front();
		queue.pop();
		visited[toVertex] = true;

		int downFloor = toVertex - edgeInfo[toVertex];
		int upFloor = toVertex + edgeInfo[toVertex];

		if (downFloor >= 1) {
			if (downFloor == B) {
				return nowTimes;
			}
			else if(!visited[downFloor]) {
				queue.push({ downFloor, nowTimes + 1 });
			}
		}
		if (upFloor <= N) {
			if (upFloor == B) {
				return nowTimes;
			}
			else if (!visited[upFloor]) {
				queue.push({ upFloor, nowTimes + 1 });
			}
		}

	}

	return -1;
}

int main() {
	cin >> N >> A >> B;

	for (int i = 1; i <= N; i++) {
		cin >> edgeInfo[i];
	}

	if (A == B) {
		cout << 0;
	}
	else {
		cout << bfs();
	}
	return 0;
}