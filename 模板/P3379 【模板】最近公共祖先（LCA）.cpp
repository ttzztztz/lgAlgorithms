#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Edge {
public:
    int end, next;

    Edge() : end(0), next(-1) {};

    Edge(int e, int n) : end(e), next(n) {};
};

const int MAX = 1000005, MAXLOGN = 25;
int head[MAX], deep[MAX], father[MAX][MAXLOGN];
int N = 0, M = 0, S = 0;
Edge edge[MAX];

void addEdge(int start, int end) {
    static int edgeCount;

    edge[edgeCount] = {end, head[start]};
    head[start] = edgeCount;
    edgeCount++;
}

void dfs(int u, int f, int d) {
    deep[u] = d;
    father[u][0] = f;

    for (int j = 1; j < (log2(d) + 1); j++) {
        father[u][j] = father[father[u][j - 1]][j - 1];
    }

    for (int i = head[u]; i != -1; i = edge[i].next) {
        const int end = edge[i].end;
        if (end == f) {
            continue;
        }
        dfs(end, u, d + 1);
    }
}

void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

int query(int u, int v) {
    if (deep[u] < deep[v]) {
        swap(u, v);
    }

    if (deep[u] != deep[v]) {
        for (int k = MAXLOGN - 1; k >= 0; k--) {
            if (deep[father[u][k]] >= deep[v]) {
                u = father[u][k];
            }
        }
    }

    if (u != v) {
        for (int k = MAXLOGN - 1; k >= 0; k--) {
            if (father[u][k] != father[v][k]) {
                u = father[u][k];
                v = father[v][k];
            }
        }
        return father[u][0];
    }

    return u;
}

int main() {
    ios::sync_with_stdio(false);
    memset(head, 0xff, sizeof(head));
    cin >> N >> M >> S;
    for (int i = 1; i <= N - 1; i++) {
        int start = 0, end = 0;
        cin >> start >> end;
        addEdge(start, end);
        addEdge(end, start);
    }

    dfs(S, 0, 1);
    for (int i = 1; i <= M; i++) {
        int u = 0, v = 0;
        cin >> u >> v;
        cout << query(u, v) << endl;
    }
    return 0;
}
