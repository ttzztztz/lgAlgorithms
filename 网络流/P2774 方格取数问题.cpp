#include<iostream>
#include<deque>
#include<cstring>

using namespace std;

class Edge {
public:
    int from, to, flow, next;

    Edge() : from(0), to(0), flow(0), next(-1) {};

    Edge(int _u, int _v, int f, int n) : from(_u), to(_v), flow(f), next(n) {};
};

const int MAX = 10005, INF = 0x7fffffff;
Edge edge[MAX * 4];
int head[MAX * 2], src, target, layer[MAX];

int min(int a, int b) {
    return a < b ? a : b;
}

int edgeCount;

void addEdge(int u, int v, int f) {
    edge[edgeCount] = Edge(u, v, f, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

void addEdgeDouble(int u, int v, int f) {
    addEdge(u, v, f);
    addEdge(v, u, 0);
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
            if (layer[e.to] == -1 && e.flow) {
                layer[e.to] = layer[e.from] + 1;
                if (e.to == target) {
                    return true;
                } else {
                    queue.push_back(e.to);
                }
            }
        }
    }
    return false;
}

int DFS(int u, int flow) {
    if (u == target) {
        return flow;
    }
    int answer = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        Edge &e = edge[i];
        Edge &e_reversed = edge[i ^ 1];
        if (e.flow && layer[e.to] == layer[e.from] + 1) {
            int f = DFS(e.to, min(e.flow, flow - answer));

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
        while ((f = DFS(src, INF))) {
            answer += f;
        }
    }
    return answer;
}

int matrix[105][105];

int main() {
    memset(head, 0xff, sizeof(head));
    int m = 0, n = 0, total = 0;
    cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> matrix[i][j];
            total += matrix[i][j];
        }
    }

    src = 0, target = 10002;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if ((i + j) % 2) {
                addEdgeDouble((i - 1) * n + j, target, matrix[i][j]);
            } else {
                addEdgeDouble(src, (i - 1) * n + j, matrix[i][j]);

                if (i - 1 >= 1) {
                    addEdgeDouble((i - 1) * n + j, (i - 2) * n + j, INF);
                }
                if (j - 1 >= 1) {
                    addEdgeDouble((i - 1) * n + j, (i - 1) * n + j - 1, INF);
                }
                if (i + 1 <= m) {
                    addEdgeDouble((i - 1) * n + j, i * n + j, INF);
                }
                if (j + 1 <= n) {
                    addEdgeDouble((i - 1) * n + j, (i - 1) * n + j + 1, INF);
                }
            }
        }
    }

    int flow = dinic();
    cout << (total - flow);
    return 0;
}