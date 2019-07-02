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

const int MAX = 3005, MAXV = 505, INF = 0x5fffffff;
Edge edge[MAX * 4];
int head[MAX * 2], src, target, layer[MAX], dp[MAXV], number[MAXV];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a < b ? b : a;
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

int main() {
    memset(head, 0xff, sizeof(head));
    int N = 0;
    cin >> N;

    if (N == 1) {
        cout << 1 << endl << 1 << endl << 1 << endl;
        return 0;
    }
    src = 0;
    target = 501;

    for (int i = 1; i <= N; i++) {
        cin >> number[i];
        dp[i] = 1;
    }
    for (int i = 2; i <= N; i++) {
        for (int j = 1; j < i; j++) {
            if (number[i] >= number[j]) {
                dp[i] = max(dp[j] + 1, dp[i]);
            }
        }
    }
    int maxLen = 0;
    for (int i = 1; i <= N; i++) {
        maxLen = max(maxLen, dp[i]);
    }
    cout << maxLen << endl;

    if (maxLen == 1) { // 特判 为1 的情况
        cout << N << endl << N << endl;
        return 0;
    }

    for (int i = 1; i <= N; i++) {
        addEdgeDouble(i, i + N, 1);
        if (dp[i] == 1) {
            addEdgeDouble(src, i, 1);
        } else if (dp[i] == maxLen) {
            addEdgeDouble(i + N, target, 1);
        }

        for (int j = 1; j < i; j++) {
            if (dp[j] + 1 == dp[i] && number[j] <= number[i]) {
                addEdgeDouble(j + N, i, 1);
            }
        }
    }

    int result = dinic();
    cout << result << endl;
    addEdgeDouble(src, 1, INF);
    addEdgeDouble(1, 1 + N, INF);
    if (dp[N] == maxLen) { // 不多于加边，在残量网络上乱搞
        addEdgeDouble(N, N + N, INF);
        addEdgeDouble(N + N, target, INF);
    }

    result += dinic();
    cout << result << endl;
    return 0;
}