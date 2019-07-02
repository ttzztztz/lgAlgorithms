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

const int MAX = 3005, INF = 0x5fffffff;
Edge edge[MAX * 4];
int head[MAX * 2], yParent[MAX], src, target, layer[MAX];
bool yVisit[MAX];

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
                if (e.v == target) {
                    return true;
                } else {
                    queue.push_back(e.v);
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
        if (e.flow && layer[e.v] == layer[e.u] + 1) {
            int f = DFS_Dinic(e.v, min(e.flow, flow - answer));

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

int cateProblemNumber[MAX], problemCateEdgeNumber[MAX * 2][MAX * 2];

int main() {
    memset(head, 0xff, sizeof(head));
    int k = 0, n = 0, m = 0;
    cin >> k >> n;
    src = 3001;
    target = 3000;
    for (int i = 1; i <= k; i++) {
        cin >> cateProblemNumber[i];
        m += cateProblemNumber[i];
        addEdgeDouble(n + i, target, cateProblemNumber[i]);
    }

    for (int i = 1; i <= n; i++) {
        int cates = 0;
        cin >> cates;
        for (int j = 1; j <= cates; j++) {
            int cate = 0;
            cin >> cate;
            problemCateEdgeNumber[i][cate] = addEdgeDouble(i, n + cate, 1);
        }
        addEdgeDouble(src, i, 1);
    }
    int flow = dinic();

    if (flow == m) {
        for (int cate = 1; cate <= k; cate++) {
            cout << cate << ": ";
            for (int problem = 1; problem <= n; problem++) {
                if (problemCateEdgeNumber[problem][cate] && edge[problemCateEdgeNumber[problem][cate]].flow == 0) {
                    cout << problem << " ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "No Solution!";
    }

    return 0;
}