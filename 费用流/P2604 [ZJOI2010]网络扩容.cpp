#include <iostream>
#include <cstring>
#include <deque>
#include <vector>
#include <tuple>

using namespace std;

class Edge {
public:
    int start, end, flow, cost, next;

    Edge() : start(0), end(0), flow(0), cost(0), next(-1) {};

    Edge(int s, int e, int f, int c, int n) : start(s), end(e), flow(f), cost(c), next(n) {};
};

const int MAX = 50005, INF = 0x6f6f6f6f;
Edge edge[MAX];
int head[MAX], src, target, dist[MAX], layer[MAX], cur[MAX];
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

bool BFS() {
    memset(layer, 0xff, sizeof(layer));
    deque<int> queue;
    queue.push_back(src);
    layer[src] = 0;

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();

        for (int i = head[u]; i != -1; i = edge[i].next) {
            const Edge &e = edge[i];
            if (layer[e.end] == -1 && e.flow) {
                layer[e.end] = layer[e.start] + 1;
                if (e.end == target) {
                    return true;
                } else {
                    queue.push_back(e.end);
                }
            }
        }
    }
    return false;
}

int DFS_Dinic(int u, int flow) {
    if (u == target) {
        return flow;
    }
    int answer = 0;
    for (int i = cur[u]; i != -1; i = edge[i].next) {
        cur[u] = i;
        Edge &e = edge[i];
        Edge &e_reversed = edge[i ^ 1];
        if (e.flow && layer[e.end] == layer[e.start] + 1) {
            int f = DFS_Dinic(e.end, min(e.flow, flow - answer));

            e.flow -= f;
            e_reversed.flow += f;
            answer += f;
        }
    }

    if (!answer) {
        layer[u] = -1;
    }
    return answer;
}

int dinic() {
    int answer = 0, f = 0;
    while (BFS()) {
        memcpy(cur, head, sizeof(head));
        while ((f = DFS_Dinic(src, INF))) {
            answer += f;
        }
    }
    return answer;
}

int N, M, K;

int main() {
    vector<tuple<int, int, int>> costStorage;
    memset(head, 0xff, sizeof(head));
    cin >> N >> M >> K;

    src = 1;
    target = N;
    for (int i = 0; i < M; i++) {
        int u = 0, v = 0, c = 0, w = 0;
        cin >> u >> v >> c >> w;
        addEdgeDouble(u, v, c, 0);
        costStorage.push_back({u, v, w});
    }
    cout << dinic() << " ";

    src = 0;
    addEdgeDouble(0, 1, K, 0);
    for (auto[u, v, w]: costStorage) {
        addEdgeDouble(u, v, INF, w);
    }

    minCost = 0;
    minCostMaxFlow();
    cout << minCost;
    return 0;
}