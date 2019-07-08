#include <iostream>
#include <cstring>

using namespace std;

class Edge {
public:
    int end, next, cost;

    Edge() : end(0), next(-1), cost(0) {};

    Edge(int e, int n, int c) : end(e), next(n), cost(c) {};
};

const int MAX = 100005, MAXN = 3005, INF = 0x5f5f5f5f;
Edge edge[MAX];
int N, M, head[MAXN], dp[MAXN][MAXN];

void addEdge(int start, int end, int cost) {
    static int edgeCount;

    edge[edgeCount] = {end, head[start], cost};
    head[start] = edgeCount;
    edgeCount++;
}

inline int max(int x, int y) {
    return x < y ? y : x;
}

int DFS(int u) {
    if (u >= N - M + 1) {
        return 1;
    } else {
        int sum = 0;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            const int v = edge[i].end, cost = edge[i].cost;
            sum += DFS(v);
            for (int j = sum; j >= 1; j--) {
                for (int k = 0; k <= j; k++) {
                    dp[u][j] = max(dp[u][j], dp[u][k] + dp[v][j - k] - cost);
                }
            }
        }
        return sum;
    }
}

int main() {
    memset(head, 0xff, sizeof(head));
    cin >> N >> M;
    for (int i = 1; i <= N - M; i++) {
        int K = 0;
        cin >> K;
        for (int j = 1; j <= K; j++) {
            int A = 0, C = 0;
            cin >> A >> C;
            addEdge(i, A, C);
        }
    }
    for (int i = 1; i <= N; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= N; j++) {
            dp[i][j] = -INF;
        }
    }
    for (int i = N - M + 1; i <= N; i++) {
        cin >> dp[i][1];
    }
    DFS(1);
    for (int i = N; i >= 1; i--) {
        if (dp[1][i] >= 0) {
            cout << i;
            break;
        }
    }
    return 0;
}

