#include<iostream>
#include<deque>
#include<cstring>
using namespace std;

class Edge {
public:
	int start, end, next;
	Edge() : start(0), end(0), next(-1) {};
	Edge(int s, int e, int n) : start(s), end(e), next(n) {};
};

const int MAX = 2000005;
int N, M;
int head[MAX], pathCount[MAX], deep[MAX];
Edge edge[MAX];
bool visited[MAX];

inline void bfs() {
	deque<int> queue;
	queue.push_back(1);
	pathCount[1]++;
	visited[1] = true;

	while (!queue.empty()) {
		int v = queue.front();
		int depth = deep[v];
		queue.pop_front();

		for (int i = head[v]; i != -1;i=edge[i].next) {
			const Edge& nextEdge = edge[i];
			if (!visited[nextEdge.end]) {
				visited[nextEdge.end] = true;
				deep[nextEdge.end] = depth + 1;
				queue.push_back(nextEdge.end);
			}
			if (deep[nextEdge.end] == depth + 1) {
				pathCount[nextEdge.end] = (pathCount[nextEdge.end] + pathCount[nextEdge.start]) % 100003;
			}
		}
	}
}

int main() {
	cin >> N >> M;
	memset(head, 0xff, sizeof(head));
	int edgeCount = 0;
	for (int i = 0; i < M;i++) {
		int s = 0, e = 0;
		cin >> s >> e;

		edge[edgeCount] = { s, e, head[s] };
		head[s] = edgeCount;
		edgeCount++;

		edge[edgeCount] = { e, s, head[e] };
		head[e] = edgeCount;
		edgeCount++;

	}
	bfs();

	for (int i = 1; i <= N;i++) {
		cout << (pathCount[i] % 100003) << endl;
	}

	return 0;
}