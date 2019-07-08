#include <iostream>
#include <cstring>
#include <deque>
#include <vector>

using namespace std;

class Edge {
public:
    int start, end, flow, cost, next;

    Edge() : start(0), end(0), flow(0), cost(0), next(-1) {};

    Edge(int s, int e, int f, int c, int n) : start(s), end(e), flow(f), cost(c), next(n) {};
};

const int MAX = 20005, INF = 0x6f6f6f6f;
Edge edge[MAX * 2];
int head[MAX], src, target, dist[MAX];
bool visited[MAX];

inline int min(int x, int y) {
    return x < y ? x : y;
}

void addEdge(int s, int e, int f, int c) {
    static int edgeCount;

    edge[edgeCount] = {s, e, f, c, head[s]};
    head[s] = edgeCount;
    edgeCount++;
}

void addEdgeDouble(int s, int e, int f, int c) {
    addEdge(s, e, f, c);
    addEdge(e, s, 0, -c);
}

bool SPFA() {
    memset(dist, 0x6f, sizeof(dist));
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
    for (int i = head[u]; i != -1; i = edge[i].next) {
        Edge &e = edge[i];
        Edge &e_reversed = edge[i ^ 1];
        if (!visited[e.end] && e.flow && dist[e.end] == dist[e.start] + e.cost) {
            int f = DFS(e.end, min(flow - answer, e.flow));
            if (f) {
                minCost += e.cost * f;
                e.flow -= f;
                e_reversed.flow += f;
                answer += f;
            }
        }
    }
    visited[u] = false;
    return answer;
}

void minCostMaxFlow() {
    while (SPFA()) {
        DFS(src, INF);
    }
}

int main() {
    memset(head, 0xff, sizeof(head));
    src = MAX - 1, target = MAX - 2;
    int N = 0, M = 0;
    cin >> N >> M;
    addEdgeDouble(src, 1, INF, 0);
    for (int i = 1; i <= N; i++) {
        int number = 0;
        cin >> number;
        addEdgeDouble(i, i + 1, INF - number, 0);
    }
    for (int i = 1; i <= M; i++) {
        int s = 0, t = 0, c = 0;
        cin >> s >> t >> c;
        addEdgeDouble(s, t + 1, INF, c);
    }
    addEdgeDouble(N + 1, target, INF, 0);
    minCostMaxFlow();
    cout << minCost;
    return 0;
}

