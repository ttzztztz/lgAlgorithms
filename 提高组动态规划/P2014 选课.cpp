#include <iostream>
#include <cstring>

using namespace std;

class Edge {
public:
    int end, next;

    Edge() : end(0), next(-1) {};

    Edge(int e, int n) : end(e), next(n) {};
};

const int MAX = 100005, MAXN = 3005;
Edge edge[MAX];
int head[MAXN], dp[MAXN][MAXN], N, M;

inline void addEdge(int start, int end) {
    static int edgeCount;

    edge[edgeCount] = {end, head[start]};
    head[start] = edgeCount;
    edgeCount++;
}

inline int max(int x, int y) {
    return x < y ? y : x;
}

inline int min(int x, int y) {
    return x < y ? x : y;
}

int DFS(int u) {
    int sum = 1;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        const int v = edge[i].end;
        sum += DFS(v);
        for (int j = min(M + 1, sum); j >= 1; j--) {
            for (int k = 0; k < j; k++) {
                dp[u][j] = max(dp[u][j], dp[v][k] + dp[u][j - k]);
            }
        }
    }
    return sum;
}

int main() {
    memset(head, 0xff, sizeof(head));
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int k = 0, s = 0;
        cin >> k >> s;
        addEdge(k, i);
        dp[i][1] = s;
    }

    DFS(0);
    cout << dp[0][M + 1];
    return 0;
}

