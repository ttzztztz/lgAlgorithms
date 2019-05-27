#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

class Edge {
public:
	int start, end, weight, next;
	Edge() : start(0), end(0), weight(0), next(-1) {};
	Edge(int s, int e, int w, int n) :start(s), end(e), weight(w), next(n) {};
};

class MinEdge {
public:
	int end, weight;
	MinEdge(int e, int w) : end(e), weight(w) {};
	MinEdge() : end(0), weight(0) {};
	bool operator< (const MinEdge& e) const {
		return this->weight > e.weight;
	}
};

inline int min(int a, int b) {
	return a < b ? a : b;
}

const int MAX = 200001;
const int INF = 1 << 30;
int dist[MAX], head[MAX], visited[MAX];
Edge edge[MAX];

void dijkstra(int S) {
	priority_queue<MinEdge> queue;
	queue.push(MinEdge(S, 0));

	while (!queue.empty()) {
		MinEdge e;
		do {
			e = queue.top();
			queue.pop();
		} while (visited[e.end] && !queue.empty());

		if (!visited[e.end]) {
			visited[e.end] = 1;

			for (int i = head[e.end]; i != -1; i = edge[i].next) {
				Edge& target = edge[i];
				if (!visited[target.end] && dist[target.end] > dist[target.start] + target.weight) {
					dist[target.end] = dist[target.start] + target.weight;
					queue.push(MinEdge(target.end, dist[target.end]));
				}
			}
		}
	}
}

int main() {
	memset(head, 0xff, sizeof(head));
	int N = 0, M = 0, S = 0;
	cin >> N >> M >> S;
	for (int i = 0; i < MAX; i++) {
		dist[i] = INF;
	}
	dist[S] = 0;

	for (int i = 0; i < M; i++) {
		int s = 0, e = 0, w = 0;
		cin >> s >> e >> w;
		edge[i] = Edge(s, e, w, head[s]);
		head[s] = i;
	}

	dijkstra(S);

	for (int i = 1; i <= N; i++) {
		if (i == N) {
			cout << dist[i];
		}
		else {
			cout << dist[i] << " ";
		}
	}

	return 0;
}