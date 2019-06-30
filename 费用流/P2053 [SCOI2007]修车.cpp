#include <iostream>
#include <cstring>
#include <deque>
#include <cstdio>

using namespace std;

class Edge {
public:
    int start, end, flow, cost, next;

    Edge() : start(0), end(0), flow(0), cost(0), next(-1) {};

    Edge(int s, int e, int f, int c, int n) : start(s), end(e), flow(f), cost(c), next(n) {};
};

const int MAX = 100005, INF = 0x6f6f6f6f;
Edge edge[MAX];
int head[MAX], cur[MAX], src, target, dist[MAX];
int matrix[100][100];
bool visited[MAX];

int min(int x, int y) {
    return x < y ? x : y;
}

void addEdge(int u, int v, int f, int c) {
    static int edgeCount;

    edge[edgeCount] = Edge(u, v, f, c, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

void addEdgeDouble(int u, int v, int f, int c) {
    addEdge(u, v, f, c);
    addEdge(v, u, 0, -c);
}

bool SPFA() {
    memset(dist, 0x6f, sizeof(dist));
    memcpy(cur, head, sizeof(head));
    deque<int> queue;

    queue.push_back(src);
    visited[src] = true;
    dist[src] = 0;

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        visited[u] = false;

        for (int i = head[u]; i != -1; i = edge[i].next) {
            const Edge &e = edge[i];
            if (e.flow && dist[e.end] > dist[e.start] + e.cost) {
                dist[e.end] = dist[e.start] + e.cost;

                if (!visited[e.end]) {
                    queue.push_back(e.end);
                    visited[e.end] = true;
                }
            }
        }
    }

    return dist[target] < INF;
}

int minCost = 0;

int DFS(int u, int flow) {
    if (u == target) {
        return flow;
    }
    int answer = 0;
    visited[u] = true;
    for (int i = cur[u]; i != -1; i = edge[i].next) {
        cur[u] = i;
        Edge &e = edge[i];
        if (!visited[e.end] && e.flow && dist[e.end] == dist[e.start] + e.cost) {
            int f = DFS(e.end, min(flow - answer, edge[i].flow));
            if (f) {
                minCost += e.cost * f;
                edge[i].flow -= f;
                edge[i ^ 1].flow += f;
                answer += f;
            }
        }
    }

    visited[u] = false;
    return answer;
}

int minCostMaxFlow() {
    int answer = 0;
    while (SPFA()) {
        int f = 0;
        while ((f = DFS(src, 0x7fffffff))) {
            answer += f;
        }
    }
    return answer;
}

int main() {
    memset(head, 0xff, sizeof(head));
    src = 0;
    target = 99999;
    int M = 0, N = 0;
    cin >> M >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> matrix[i][j];
        }
    }

    for (int i = 1; i <= M * N; i++) {
        addEdgeDouble(src, i, 1, 0);
    }
    for (int i = 1; i <= M; i++) {
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) {
                addEdgeDouble((i - 1) * N + j, M * N + k, 1, matrix[k][i] * j);
            }
        }
    }
    for(int i=1;i<=N;i++){
        addEdgeDouble(N * M + i, target, 1, 0);
    }

    minCostMaxFlow();
    printf("%.2f", (double) minCost / (double) N);

    return 0;
}