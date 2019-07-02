#include<iostream>
#include<deque>
#include<cstring>

using namespace std;

class Edge {
public:
    int u, v, flow, next;

    Edge() : u(0), v(0), flow(0), next(-1) {};

    Edge(int _u, int _v, int f, int n) : u(_u), v(_v), flow(f), next(n) {};
};

const int MAX = 24005, MAXV = 505, INF = 0x5fffffff;
Edge edge[MAX];
int head[MAXV], src, target, layer[MAXV];
bool visited[MAXV];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a < b ? b : a;
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
            if (layer[e.v] == -1 && e.flow) {
                layer[e.v] = layer[e.u] + 1;
                queue.push_back(e.v);
            }
        }
    }
    return layer[target] >= 0;
}

int DFS_Dinic(int u, int flow) {
    if (u == target) {
        return flow;
    }
    int answer = 0;
    for (int i = head[u]; i != -1 && flow; i = edge[i].next) {
        Edge &e = edge[i];
        Edge &e_reversed = edge[i ^ 1];
        if (e.flow && layer[e.v] == layer[e.u] + 1) {
            int f = DFS_Dinic(e.v, min(e.flow, flow - answer));

            e.flow -= f;
            e_reversed.flow += f;
            answer += f;
            if (flow == answer) {
                break;
            }
        }
    }

    if (!answer) {
        layer[u] = -1;
    }
    return answer;
}

int dinic() {
    int answer = 0;
    while (BFS()) {
        answer += DFS_Dinic(src, INF);
    }
    return answer;
}

int edgeId[MAXV][MAXV];

int addEdge(int u, int v, int f) {
    static int edgeCount;

    edge[edgeCount] = Edge(u, v, f, head[u]);
    head[u] = edgeCount;
    edgeCount++;

    return edgeCount - 1;
}

int addEdgeDouble(int u, int v, int f) {
    int answer = addEdge(u, v, f);
    addEdge(v, u, 0);

    return answer;
}

int n = 0, m = 0;

void dfs(int u) {
    visited[u] = true;
    cout << u << " ";
    for (int v = 1; v <= n; v++) {
        if (!visited[v] && edgeId[u][v] != -1 && edge[edgeId[u][v]].flow == 0) {
            dfs(v);
        }
    }
}

int main() {
    memset(head, 0xff, sizeof(head));
    memset(edgeId, 0xff, sizeof(edgeId));

    src = 0;
    target = 500;

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int start = 0, end = 0;
        cin >> start >> end;
        edgeId[start][end] = addEdgeDouble(start, n + end, 1);
    }
    for (int i = 1; i <= n; i++) {
        addEdgeDouble(0, i, 1);
        addEdgeDouble(i + n, target, 1);
    }
    int flow = dinic();
    for (int u = 1; u <= n; u++) {
        if (!visited[u]) {
            dfs(u);
            cout << endl;
        }
    }
    cout << (n - flow);
    return 0;
}