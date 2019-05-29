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
};

inline int min(int a, int b) {
	return a < b ? a : b;
}

const int MAX = 500001;
const int INF = 0x7fffffff;
int dist[MAX], head[MAX], visited[MAX], updateTimes[MAX];
Edge edge[MAX];
int N = 0, M = 0, S = 0;

void spfa(int S) {
	deque<MinEdge> queue;

	queue.push_back(MinEdge(S,0));
	while (!queue.empty()) {
		MinEdge e = queue.front();
		queue.pop_front();
		visited[e.end] = 0;

		for (int i = head[e.end]; i != -1;i=edge[i].next) {
			Edge& target = edge[i];
			
			if (dist[target.end] > dist[target.start] + target.weight && dist[target.start] != INF) {
				dist[target.end] = dist[target.start] + target.weight;

				if (!visited[target.end]) {
					queue.push_back(MinEdge(target.end, target.weight));
					visited[target.end] = 1;
				}

				if (++updateTimes[e.end] >= N) {
					return;
				}
			}
		}
	}
}

int main() {
	memset(head, 0xff, sizeof(head));
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

	spfa(S);

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