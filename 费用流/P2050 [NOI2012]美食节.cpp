#include <iostream>
#include <cstring>
#include <deque>

using namespace std;

class Edge {
public:
    int start, end, flow, cost, next, chef;

    Edge() : start(0), end(0), flow(0), cost(0), next(-1), chef(0) {};

    Edge(int s, int e, int f, int c, int n, int chef) :
            start(s), end(e), flow(f), cost(c), next(n), chef(chef) {};
};

const int MAX = 2000005, MAXN = 120, MAXV = 40005, MAXC = 105, INF = 0x5f5f5f5f;
Edge edge[MAX];
int head[MAXV], flow[MAXV], src, target, dist[MAXV], piece[MAXC], previous[MAXV], cookTimes[MAXC], edgeCount;
int matrix[MAXN][MAXN], vertexCount;
bool visited[MAXV];

int min(int x, int y) {
    return x < y ? x : y;
}

void addEdge(int u, int v, int f, int c, int chef) {
    edge[edgeCount] = Edge(u, v, f, c, head[u], chef);
    head[u] = edgeCount;
    edgeCount++;
}

bool SPFA() {
    memset(dist, 0x5f, sizeof(dist));
    memset(flow, 0, sizeof(flow));
    memset(previous, 0, sizeof(previous));
//    memset(visited, 0, sizeof(visited));

    deque<int> queue;
    queue.push_back(src);
    visited[src] = true;
    dist[src] = 0;
    flow[src] = INF;

    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        visited[u] = false;

        for (int i = head[u]; i != -1; i = edge[i].next) {
            const Edge &e = edge[i];
            if (e.flow && dist[e.end] > dist[e.start] + e.cost) {
                dist[e.end] = dist[e.start] + e.cost;
                previous[e.end] = i;
                flow[e.end] = min(flow[e.start], e.flow);
                if (!visited[e.end]) {
                    queue.push_back(e.end);
                    visited[e.end] = true;
                }
            }
        }
    }

    return flow[target];
}

int minCost = 0;
int N, M;

void addEdgeDouble(int u, int v, int f, int c, int chef) {
    addEdge(u, v, f, c, chef);
    addEdge(v, u, 0, -c, chef);
}

int main() {
    memset(head, 0xff, sizeof(head));
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> piece[i];
    }
    src = MAXV - 2, target = MAXV - 1;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> matrix[i][j];
        }
    }
    for (int i = 1; i <= N; i++) {
        addEdgeDouble(src, ++vertexCount, piece[i], 0, 0);
    }
    vertexCount++;
    for (int i = 1; i <= M; i++, vertexCount++) {
        for (int j = 1; j <= N; j++) {
            addEdgeDouble(j, vertexCount, 1, matrix[j][i], 0);
        }
        cookTimes[i] = 1;
        addEdgeDouble(vertexCount, target, 1, 0, i);
    }
    while (SPFA()) {
        minCost += flow[target] * dist[target];
        int u = target;
        while (u != src) {
            const int i = previous[u];
            edge[i].flow -= flow[target];
            edge[i ^ 1].flow += flow[target];

            u = edge[previous[u]].start;
        }

        int cookChef = edge[previous[target]].chef;
        vertexCount++;
        cookTimes[cookChef]++;
        for (int i = 1; i <= N; i++) {
            addEdgeDouble(i, vertexCount, 1, matrix[i][cookChef] * cookTimes[cookChef], 0);
        }
        addEdgeDouble(vertexCount, target, 1, 0, cookChef);
    }
    cout << minCost;
    return 0;
}

