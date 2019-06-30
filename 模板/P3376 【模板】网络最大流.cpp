#include <iostream>
#include <cstring>
#include <deque>

using namespace std;

class Edge {
public:
    int start, end, flow, next;

    Edge() : start(0), end(0), flow(0), next(-1) {};

    Edge(int s, int e, int f, int n) : start(s), end(e), flow(f), next(n) {};
};

const int MAX = 300000, INF = 0x6f6f6f6f;
Edge edge[MAX];
int head[MAX], src, target, layer[MAX];

int min(int x, int y) {
    return x < y ? x : y;
}

void addEdge(int u, int v, int f) {
    static int edgeCount;

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
    for (int i = head[u]; i != -1; i = edge[i].next) {
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
        while ((f = DFS_Dinic(src, INF))) {
            answer += f;
        }
    }
    return answer;
}

int N, M;

int main() {
    memset(head, 0xff, sizeof(head));
    cin >> N >> M >> src >> target;
    for (int i = 0; i < M; i++) {
        int start = 0, end = 0, flow = 0;
        cin >> start >> end >> flow;
        addEdgeDouble(start, end, flow);
    }

    int flow = dinic();
    cout << flow;
    return 0;
}