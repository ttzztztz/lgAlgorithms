#include <iostream>
#include <cstdio>
#include <cstring>
#include <deque>

using namespace std;

class Edge {
public:
    int start, end, flow, cost, next;

    Edge() : start(0), end(0), flow(0), cost(0), next(-1) {};

    Edge(int s, int e, int f, int c, int n) : start(s), end(e), flow(f), cost(c), next(n) {};
};

const int MAX = 60000, MAXN = 500, INF = 0x3f3f3f3f;
int head[MAXN], dist[MAXN], cur[MAXN];
bool visited[MAXN];
Edge edge[MAX];

inline int min(int x, int y) {
    return x < y ? x : y;
}

inline bool SPFA(int s, int t) {
    memset(dist, 0x3f, sizeof(dist));
    memcpy(cur, head, sizeof(head));

    deque<int> queue;
    queue.push_back(s);
    visited[s] = true;
    dist[s] = 0;

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
    return dist[t] < INF;
}

int minCost, maxFlow;

int dfs(int u, int t, int flow) {
    if (u == t) {
        return flow;
    }
    visited[u] = true;
    int answer = 0;
    for (int i = cur[u]; i != -1; i = edge[i].next) {
        cur[u] = i;
        int v = edge[i].end;
        if (!visited[v] && edge[i].flow && dist[v] == dist[u] + edge[i].cost) {
            int f = dfs(v, t, min(edge[i].flow, flow - answer));
            if (f) {
                edge[i].flow -= f;
                edge[i ^ 1].flow += f;
                answer += f;
                minCost += edge[i].cost;
            }
        }
    }

    visited[u] = false;
    return answer;
}

inline void minCostMaxFlow(int s, int t) {
    while (SPFA(s, t)) {
        int f = 0;
        while ((f = dfs(s, t, INF))) {
            maxFlow += f;
        }
    }
}

inline void addEdge(int u, int v, int f, int cost) {
    static int edgeCount;

    edge[edgeCount] = Edge(u, v, f, cost, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

inline void add(int u, int v, int f, int cost) {
    addEdge(u, v, f, cost);
    addEdge(v, u, 0, -cost);
}

int main() {
    memset(head, 0xff, sizeof(head));
    int N = 0, M = 0;
    scanf("%d%d", &N, &M);

    for (int i = 2; i < N; i++) {
        add(i, i + N, 1, 0);
    }

    for (int i = 0; i < M; i++) {
        int start = 0, end = 0, cost = 0;
        scanf("%d%d%d", &start, &end, &cost);
        if (start == 1) {
            add(start, end, 1, cost);
        } else {
            add(start + N, end, 1, cost);
        }
    }

    minCostMaxFlow(1, N);
    printf("%d %d", maxFlow, minCost);
    return 0;
}