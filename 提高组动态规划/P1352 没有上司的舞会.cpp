#include<iostream>
#include<cstring>
using namespace std;

class Edge {
public:
	int start, end, next;
	Edge() : start(0), end(0), next(-1) {};
	Edge(int s, int e, int n) :start(s), end(e), next(n) {};
};

const int MAX = 12005;
int boss[MAX], dp[MAX][2], N, head[MAX];
bool visited[MAX];
Edge edge[MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

void addEdge(int s, int e) {
	static int edgeCount;

	edge[edgeCount] = Edge(s, e, head[s]);
	head[s] = edgeCount;
	edgeCount++;
}

void dfs(int u) {
	visited[u] = true;
	for (int i = head[u]; i != -1;i = edge[i].next) {
		const int v = edge[i].end;
		if (!visited[v]) {
			dfs(v);

			dp[u][0] += max(dp[v][0], dp[v][1]);
			dp[u][1] += dp[v][0];
		}
	}
}

int main() {
	memset(head, 0xff, sizeof(head));
	cin >> N;
	for (int i = 1; i <= N;i++) {
		cin >> dp[i][1];
	}
	for (int i = 1; i < N;i++) {
		int L = 0, K = 0;
		cin >> L >> K;
		addEdge(K, L);
		addEdge(L, K);
	}

	int answer = 0;
	for (int i = 1; i <= N;i++) {
		if (!visited[i]) {
			dfs(i);

			answer = max(answer,
				max(dp[i][0], dp[i][1])
			);
		}
	}
	cout << answer;
	return 0;
}