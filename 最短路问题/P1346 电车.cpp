#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

class Edge {
public:
	int start, end, next, weight;
	Edge() : start(0), end(0), next(-1), weight(0) {};
	Edge(int s, int e, int n, int on) : start(s), end(e), next(n), weight(on) {};
};

class MinEdge {
public:
	int to, weight;
	MinEdge() : to(0), weight(0) {};
	MinEdge(int t, int w) : to(t), weight(w) {};
	bool operator< (const MinEdge& e) const {
		return this->weight > e.weight;
	}
};

int A, B, N;
const int MAX = 1000000;
int head[MAX];
bool visited[MAX];
Edge edge[MAX];

int dijkstra() {
	priority_queue<MinEdge> queue;
	queue.push({ A, 0 });
	while (!queue.empty()) {
		MinEdge e;
		do {
			e = queue.top();
			queue.pop();
		} while (visited[e.to] && !queue.empty());

		if (!visited[e.to]) {
			visited[e.to] = true;
			if (e.to == B) {
				return e.weight;
			}

			for (int i = head[e.to]; i != -1;i = edge[i].next) {
				const Edge& to = edge[i];
				queue.push({ to.end, e.weight + to.weight });
			}
		}
	}

	return -1;
}

int main() {
	memset(head, 0xff, sizeof(head));

	cin >> N >> A >> B;
	int edgeCount = 0;
	for (int i = 1; i <= N;i++) {
		int K = 0;
		cin >> K;
		for (int j = 1; j <= K;j++) {
			int to = 0;
			cin >> to;
			edge[edgeCount] = { i, to, head[i], j == 1 ? 0: 1 };
			head[i] = edgeCount;
			edgeCount++;
		}
	}
	cout << dijkstra();
	return 0;
}