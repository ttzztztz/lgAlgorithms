#include <iostream>
#include <cstring>

using namespace std;

class Edge {
public:
    int from, to, next;

    Edge() : from(0), to(0), next(-1) {};

    Edge(int f, int t, int n) : from(f), to(t), next(n) {};
};

const int MAX = 1000005;
int n, m, head[MAX], answer = 0, yParent[MAX];
Edge edge[MAX];
bool yUsed[MAX];

void addEdge(int u, int v) {
    static int edgeCount;

    edge[edgeCount] = Edge(u, v, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

bool solve(int u) {
    for (int i = head[u]; i != -1; i = edge[i].next) {
        if (!yUsed[edge[i].to]) {
            yUsed[edge[i].to] = true;
            if (!yParent[edge[i].to] || solve(yParent[edge[i].to])) {
                yParent[edge[i].to] = edge[i].from;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int e = 0;
    memset(head, 0xff, sizeof(head));
    cin >> n >> m >> e;
    for (int i = 0; i < e; i++) {
        int u = 0, v = 0;
        cin >> u >> v;
        if (v > m || u > n) {
            continue;
        }
        addEdge(u, v);
    }

    for (int i = 1; i <= n; i++) {
        memset(yUsed, 0, sizeof(yUsed));
        if (solve(i)) {
            answer++;
        }
    }

    cout << answer;
    return 0;
}