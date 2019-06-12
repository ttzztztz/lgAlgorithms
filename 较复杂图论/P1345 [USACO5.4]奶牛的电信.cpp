#include<iostream>
#include<cstring>
#include<deque>
using namespace std;

class Edge {
public:
	int start, end, flow, next;
	Edge() :start(0), end(0), flow(0), next(-1) {};
	Edge(int s, int e, int f, int n) : start(s), end(e), flow(f), next(n) {};
};

const int MAX = 5000, INF = 999999;
int head[MAX], layer[MAX], curr[MAX], cur[MAX];
Edge edge[MAX];
int N, M, SRC, TARGET;

void init() {
	memset(head, 0xff, sizeof(head));
}

void addEdge(int s, int e, int f) {
	static int edgeCount;

	edge[edgeCount] = Edge(s, e, f, head[s]);
	head[s] = edgeCount;
	edgeCount++;
}

inline int min(int x, int y) {
	return x < y ? x : y;
}

int bfs() {
	memset(layer, 0xff, sizeof(layer));
	deque<int> queue;
	queue.push_back(SRC);
	layer[SRC] = 0;

	while (!queue.empty()) {
		int u = queue.front();
		queue.pop_front();

		for (int i = head[u]; i != -1;i=edge[i].next) {
			const Edge& e = edge[i];
			if (layer[e.end] == -1 && e.flow) {
				layer[e.end] = layer[e.start] + 1;
				if (e.end == TARGET) {
					return 1;
				}
				else {
					queue.push_back(e.end);
				}
			}
		}
	}
	return 0;
}

int dfs(int u, int f) {
	if (u == TARGET) {
		return f;
	}

	int flow = 0;
	for (int i = cur[u]; f && i != -1;i=edge[i].next) {
		cur[u] = i;
		Edge& e = edge[i], & e_reversed = edge[i ^ 1];
		if (e.flow && layer[e.end] == layer[e.start] + 1) {
			int maxFlow = dfs(e.end, min(f, e.flow));

			e.flow -= maxFlow;
			e_reversed.flow += maxFlow;

			f -= maxFlow;
			flow += maxFlow;
		}
	}

	if (!flow) {
		layer[u] = -1;
	}
	return flow;
}

int dinic() {
	int flow = 0;
	while (bfs()) {
		memcpy(cur, head, sizeof(head));
		flow += dfs(SRC, INF);
	}
	return flow;
}

int main() {
	memset(head, 0xff, sizeof(head));
	cin >> N >> M >> SRC >> TARGET;

	SRC += N;
	for (int i = 1; i <= N;i++) {
		addEdge(i, i + N, 1);
		addEdge(i + N, i, 0);
	}

	for (int i = 0; i < M; i++) {
		int s = 0, e = 0;
		cin >> s >> e;

		addEdge(s + N, e, INF);
		addEdge(e, s + N, 0);
		addEdge(e + N, s, INF);
		addEdge(s, e + N, 0);
	}

	cout << dinic();

	return 0;
}