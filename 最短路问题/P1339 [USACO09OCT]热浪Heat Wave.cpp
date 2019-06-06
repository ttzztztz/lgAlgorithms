#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

class Edge {
public:
	int start, end, next, weight;
	Edge() : start(0), end(0), next(-1), weight(0) {};
	Edge(int s, int e, int n, int w) : start(s), end(e), next(n), weight(w) {};
};

class MinEdge {
public:
	int end, weight;
	MinEdge() : end(0), weight(0) {};
	MinEdge(int e, int w) : end(e), weight(w) {};
	bool operator< (const MinEdge& e) const {
		return this->weight > e.weight;
	}
};

const int MAX = 13000;
int vertexCount, edgeCount, src, target;
int head[MAX];
bool visited[MAX];
Edge edge[MAX];

inline int dijkstra() {
	priority_queue<MinEdge> queue;
	queue.push({ src, 0 });

	while (!queue.empty()) {
		MinEdge e;
		do {
			e = queue.top();
			queue.pop();
		} while (!queue.empty() && visited[e.end]);

		if (!visited[e.end]) {
			visited[e.end] = true;
			if (e.end == target) {
				return e.weight;
			}

			for (int i = head[e.end]; i != -1;i=edge[i].next) {
				const Edge& nextEdge = edge[i];
				if (!visited[nextEdge.end]) {
					queue.push({ nextEdge.end, nextEdge.weight + e.weight });
				}
			}
		}
	}

	return 0;
}

int main() {
	memset(head, 0xff, sizeof(head));
	cin >> vertexCount >> edgeCount >> src >> target;

	int count = 0;
	for (int i = 0; i < edgeCount;i++) {
		int start = 0, end = 0, weight = 0;
		cin >> start >> end >> weight;

		edge[count] = Edge(start, end, head[start], weight);
		head[start] = count;
		count++;

		edge[count] = Edge(end, start, head[end], weight);
		head[end] = count;
		count++;
	}

	cout << dijkstra();

	return 0;
}