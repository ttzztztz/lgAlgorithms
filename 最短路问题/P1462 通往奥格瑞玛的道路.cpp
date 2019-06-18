#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

class Edge {
public:
	int start, end, next;
	long long blood;
	Edge() : start(0), end(0), blood(0), next(-1) {};
	Edge(int s, int e, long long w, int n) : start(s), end(e), blood(w), next(n) {};
};

class MinEdge {
public:
	int to;
	long long weight;
	MinEdge() : to(0), weight(0) {};
	MinEdge(int t, long long w) : to(t), weight(w) {};
	bool operator< (const MinEdge& $1) const {
		return this->weight > $1.weight;
	}
};

const int MAX = 100005, INF = 1 << 30;
int head[MAX], vertexCount, N, M, B, vertexCost[MAX];
long long dist[MAX];
bool visited[MAX];
Edge edge[MAX];

inline int min(int x, int y) {
	return x < y ? x : y;
}

inline int max(int x, int y) {
	return x < y ? y : x;
}

bool dijkstra(long long cost) {
	const int start = 1, vertexCount = N;

	for (int i = 0; i <= vertexCount; i++) {
		visited[i] = false;
		dist[i] = INF;
	}

	priority_queue<MinEdge>queue;
	queue.push({ start, 0 });
	dist[start] = 0;

	while (!queue.empty()) {
		MinEdge curr;
		do {
			curr = queue.top();
			queue.pop();
		} while (!queue.empty() && visited[curr.to]);

		if (!visited[curr.to]) {
			visited[curr.to] = true;

			for (int i = head[curr.to]; i != -1; i = edge[i].next) {
				const Edge& e = edge[i];

				if (!visited[e.end] && dist[e.end] > dist[e.start] + e.blood
					&& vertexCost[e.end] <= cost) {
					dist[e.end] = dist[e.start] + e.blood;
					queue.push({ e.end, dist[e.end] });
				}

			}
		}
	}

	return dist[N] < INF && dist[N] > 0 && dist[N] < B;
}

void addEdge(int start, int end, int weight) {
	static int edgeCount;

	edge[edgeCount] = Edge(start, end, weight, head[start]);
	head[start] = edgeCount;
	edgeCount++;
}

long long search(long long l, long long r){
	while (l <= r) {
		long long middle = (l + r) / 2;
		if (dijkstra(middle)) {
			r = middle - 1;
		}
		else {
			l = middle + 1;
		}
	}

	return r + 1;
}

int main() {
	memset(head, 0xff, sizeof(head));

	int maxCost = -1, minCost = 0x7fffffff;

	cin >> N >> M >> B;
	for (int i = 1; i <= N;i++) {
		cin >> vertexCost[i];
		maxCost = max(maxCost, vertexCost[i]);
		minCost = min(minCost, vertexCost[i]);
	}
	for (int i = 1; i <= M;i++) {
		int s = 0, e = 0, b = 0;
		cin >> s >> e >> b;

		addEdge(s, e, b);
		addEdge(e, s, b);
	}


	if (!dijkstra(maxCost)) {
		cout << "AFK";
	}
	else {
		cout << search(minCost, maxCost);
	}

	return 0;
}