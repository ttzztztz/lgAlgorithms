#include<iostream>
#include<cstring>
using namespace std;

class Edge {
public:
	int start, end, weight, next;
	Edge() : start(0), end(0), weight(0), next(-1) {};
	Edge(int s, int e, int w, int n) : start(s), end(e), next(n), weight(w) {};
};

const int MAX = 20005, INF = 10005;
int head[MAX], dist[MAX], N, M;
bool haveNegativeCircle = false;
bool visited[MAX];
Edge edge[MAX];

void addEdge(int s, int e, int w) {
	static int edgeCount;

	edge[edgeCount] = Edge(s, e, w, head[s]);
	head[s] = edgeCount;
	edgeCount++;
}

void dfs(int u) {
	visited[u] = true;
	for (int i = head[u]; i != -1;i=edge[i].next) {
		const Edge& e = edge[i];
		if (dist[e.end] > dist[e.start] + e.weight) {
			if (haveNegativeCircle || visited[e.end]) {
				haveNegativeCircle = true;
				break;
			}

			dist[e.end] = dist[e.start] + e.weight;
			dfs(e.end);
		}
	}
	visited[u] = false;
}

int main() {
	memset(head, 0xff, sizeof(head));
	cin >> N >> M;
	for (int i = 0; i < M;i++) {
		int opt = 0;
		cin >> opt;
		if (opt == 1) {
			int a = 0, b = 0, c = 0;
			cin >> a >> b >> c;
			addEdge(a, b, -c);
		}
		else if (opt == 2) {
			int a = 0, b = 0, c = 0;
			cin >> a >> b >> c;
			addEdge(b, a, c);
		}
		else {
			int a = 0, b = 0;
			cin >> a >> b;

			addEdge(a, b, 0);
			addEdge(b, a, 0);
		}
	}

	for (int i = 1; i <= N;i++) {
		dfs(i);
		if (haveNegativeCircle) {
			break;
		}
	}

	if (haveNegativeCircle) {
		cout << "No";
	}
	else {
		cout << "Yes";
	}
	return 0;
}