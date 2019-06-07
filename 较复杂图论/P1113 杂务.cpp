#include<iostream>
#include<cstring>
#include<deque>
using namespace std;

class Edge {
public:
	int start, end, weight, next;
	Edge() : start(0), end(0), weight(0), next(0) {};
	Edge(int s, int e, int w, int n) : start(s), end(e), weight(w), next(n) {};
};

const int MAX = 1000000;
int N, result;
int head[MAX], finishTime[MAX], inDegree[MAX];
Edge edge[MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline void addEdge(int s, int e, int w) {
	static int edgeCount;

	edge[edgeCount] = {s, e, w, head[s]};
	head[s] = edgeCount;
	edgeCount++;
	inDegree[e]++;
}

inline void bfs() {
	deque<int> queue;
	queue.push_back(0);

	while (!queue.empty()) {
		int u = queue.front();
		queue.pop_front();

		for (int i = head[u]; i != -1;i=edge[i].next) {
			const Edge& e = edge[i];
			finishTime[e.end] = max(finishTime[e.end], finishTime[e.start] + e.weight);
			inDegree[e.end]--;

			if (!inDegree[e.end]) {
				queue.push_back(e.end);
			}
		}
	}
}

int main() {
	memset(head, 0xff, sizeof(head));
	cin >> N;
	for (int i = 0; i < N;i++) {
		int id = 0, len = 0;
		cin >> id >> len;
		int dependency = -1;
		cin >> dependency;
		addEdge(dependency, id, len);

		while (dependency != 0) {
			cin >> dependency;
			addEdge(dependency, id, len);
		}
	}
	bfs();

	int maxTime = 0;
	for (int i = 0; i <= N;i++) {
		maxTime = max(maxTime, finishTime[i]);
	}
	cout << maxTime;
	return 0;
}