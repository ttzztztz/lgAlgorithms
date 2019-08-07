#include <iostream>
#include <deque>
#include <cstring>

using namespace std;

class Edge {
public:
    int start, end, flow, next;

    Edge() : start(0), end(0), flow(0), next(-1) {};

    Edge(int s, int e, int f, int n) : start(s), end(e), flow(f), next(n) {};
};

const int MAX = 1000, INF = 0x6f6f6f6f;
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

int DFS(int u, int flow) {
    if (u == target) {
        return flow;
    }

    int answer = 0;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        Edge &e = edge[i];
        Edge &e_reversed = edge[i ^ 1];
        if (e.flow && layer[e.end] == layer[e.start] + 1) {
            int f = DFS(e.end, min(e.flow, flow - answer));

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
    int answer = 0;
    while (BFS()) {
        int f = DFS(src, INF);
        answer += f;
    }
    return answer;
}

int main() {
    const int MAX_V = 55;
    int M = 0, N = 0, sum = 0;
    src = 0, target = 3 * MAX_V;
    memset(head, 0xff, sizeof(head));
    cin >> M >> N;

    for (int i = 1; i <= M; i++) {
        int value = 0;
        cin >> value;

        sum += value;
        addEdgeDouble(src, i, value);

        char tools[10000];
        memset(tools, 0, sizeof tools);
        cin.getline(tools, 10000);
        int ulen = 0, tool = 0;
        while (sscanf(tools + ulen, "%d", &tool) == 1) {
            addEdgeDouble(i, MAX_V + tool, INF);
            if (tool == 0) {
                ulen++;
            } else {
                while (tool) {
                    tool /= 10;
                    ulen++;
                }
            }
            ulen++;
        }
    }

    for (int i = 1; i <= N; i++) {
        int cost = 0;
        cin >> cost;
        addEdgeDouble(MAX_V + i, target, cost);
    }
    int flow = dinic();

    for (int i = 1; i <= M; i++) {
        if (layer[i] != -1) {
            cout << i << " ";
        }
    }
    cout << endl;
    for (int i = 1; i <= N; i++) {
        if (layer[i + MAX_V] != -1) {
            cout << i << " ";
        }
    }

    cout << endl << (sum - flow);
    return 0;
}