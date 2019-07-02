#include <iostream>
#include <cstring>

using namespace std;

class Edge {
public:
    int from, to, next;

    Edge() : from(0), to(0), next(-1) {};

    Edge(int f, int t, int n) : from(f), to(t), next(n) {};
};

Edge edge[2000005];
int head[2000005], yParent[2000005];
bool yVisited[2000005];

bool solve(int x) {
    for (int i = head[x]; i != -1; i = edge[i].next) {
        const int y = edge[i].to;
        if (!yVisited[y]) {
            yVisited[y] = true;
            if (!yParent[y] || solve(yParent[y])) {
                yParent[y] = x;
                return true;
            }
        }
    }
    return false;
}

void addEdge(int u, int v) {
    static int edgeCount;

    edge[edgeCount] = Edge(u, v, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

int max(int x, int y) {
    return x < y ? y : x;
}

int main() {
    memset(head, 0xff, sizeof(head));
    int N = 0, maxIndex = 0;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int a = 0, b = 0;
        cin >> a >> b;

        addEdge(a, i);
        addEdge(b, i);
        maxIndex = max(maxIndex, a);
        maxIndex = max(maxIndex, b);
    }

    int answer = 0;
    for (int i = 1; i <= maxIndex; i++) {
        memset(yVisited, 0, sizeof(yVisited));
        if (solve(i)) {
            answer++;
        } else {
            break;
        }
    }
    cout << answer;

    return 0;
}