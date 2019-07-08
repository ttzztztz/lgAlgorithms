#include <iostream>
#include <cstring>
#include <deque>
#include <cmath>
#include <vector>

using namespace std;

class Edge {
public:
    int start, end, flow, next;

    Edge() : start(0), end(0), flow(0), next(-1) {};

    Edge(int s, int e, int f, int n) : start(s), end(e), flow(f), next(n) {};
};

const int MAX = 50005, INF = 0x7f7f7f7f, MAXN = 2000;
Edge edge[MAX * 2];
int head[MAX], layer[MAX], src, target;
bool visited[MAXN];

inline int ID(int x, int y) {
    return 2 * (x - 1) + y;
}

inline int max(int x, int y) {
    return x < y ? y : x;
}

inline int min(int x, int y) {
    return x < y ? x : y;
}

inline void addEdge(int s, int e, int f) {
    static int edgeCount;

    edge[edgeCount] = {s, e, f, head[s]};
    head[s] = edgeCount;
    edgeCount++;
}

inline void addEdgeDouble(int s, int e, int f) {
    addEdge(s, e, f);
    addEdge(e, s, 0);
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

inline int dinic() {
    int answer = 0, f = 0;
    while (BFS()) {
        while ((f = DFS(src, INF))) {
            answer += f;
        }
    }
    return answer;
}

inline bool isFullSquareNumber(int x) {
    int number = sqrt(x);
    return number * number == x;
}

void DFS_result(int u) {
    if (visited[u]) {
        return;
    }
    visited[u] = true;
    cout << u << " ";
    for (int i = head[ID(u, 0)]; i != -1; i = edge[i].next) {
        const int v = (edge[i].end / 2) + 1;
        if (edge[i].flow == 0 && edge[i].end != target) {
            if (!visited[v]) {
                DFS_result(v);
            }
        }
    }
}

int N = 0;

int main() {
    memset(head, 0xff, sizeof(head));
    vector<int> firstBall;

    src = MAX - 1, target = MAX - 2;
    cin >> N;
    int ballCount = 0, containerCount = 0;
    while (containerCount <= N) {
        int nextBall = ++ballCount;
        addEdgeDouble(src, ID(nextBall, 0), 1);
        addEdgeDouble(ID(nextBall, 1), target, 1);
        for (int i = 1; i < nextBall; i++) {
            if (isFullSquareNumber(i + nextBall)) {
                addEdgeDouble(ID(i, 0), ID(nextBall, 1), 1);
            }
        }
        int tempFlow = dinic();
        if (!tempFlow) {
            firstBall.push_back(nextBall);
            containerCount++;
        }
    }
    ballCount--;
    firstBall.pop_back();
    cout << ballCount << endl;

    for (int u: firstBall) {
        DFS_result(u);
        cout << endl;
    }

    return 0;
}

