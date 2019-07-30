// luogu-judger-enable-o2
#include <iostream>
#include <cstring>

using namespace std;

class Edge {
public:
    int end, next;

    Edge() : end(0), next(-1) {};

    Edge(int e, int n) : end(e), next(n) {};
};

const int MAX = 60005;
int deep[MAX], father[MAX], heavySon[MAX], total[MAX], head[MAX];
int id[MAX], newWeight[MAX], top[MAX], weight[MAX];
Edge edge[MAX];

int max(int x, int y) {
    return x < y ? y : x;
}

int dfs1(int u, int f, int d) {
    deep[u] = d;
    father[u] = f;
    total[u] = 1;

    int maxSon = -1;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        const int v = edge[i].end;
        if (v == f) {
            continue;
        }
        total[u] += dfs1(v, u, d + 1);
        if (total[v] > maxSon) {
            maxSon = total[v];
            heavySon[u] = v;
        }
    }
    return total[u];
}

int count = 0;

void dfs2(int u, int maxTop) {
    id[u] = ++count;
    newWeight[count] = weight[u];
    top[u] = maxTop;

    if (!heavySon[u]) {
        return;
    }
    dfs2(heavySon[u], maxTop);
    for (int i = head[u]; i != -1; i = edge[i].next) {
        const int v = edge[i].end;
        if (v == father[u] || v == heavySon[u]) {
            continue;
        }
        dfs2(v, v);
    }
}

class TreeNode {
public:
    int left, right, sum, total, max;

    TreeNode() : left(0), right(0), sum(0), total(0), max(-999999) {};
};

TreeNode treeNode[MAX];

void pushdown(int u) {
    treeNode[u].sum = treeNode[u * 2].sum + treeNode[u * 2 + 1].sum;
    treeNode[u].max = max(treeNode[u * 2].max, treeNode[u * 2 + 1].max);
}

void build(int u, int left, int right) {
    treeNode[u].left = left;
    treeNode[u].right = right;
    treeNode[u].total = right - left + 1;
    if (left == right) {
        treeNode[u].sum = newWeight[left];
        treeNode[u].max = newWeight[left];
        return;
    }
    int middle = (left + right) / 2;

    build(u * 2, left, middle);
    build(u * 2 + 1, middle + 1, right);
    pushdown(u);
}

void setMax(int u, int left, int right, int val) {
    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        treeNode[u].max = max(val, treeNode[u].max);
        return;
    }

    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (left <= middle) {
        setMax(2 * u, left, right, val);
    }
    if (middle < right) {
        setMax(2 * u + 1, left, right, val);
    }
    pushdown(u);
}

int querySum(int u, int left, int right) {
    int answer = 0;

    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        return treeNode[u].sum;
    }

    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (left <= middle) {
        answer = answer + querySum(2 * u, left, right);
    }
    if (middle < right) {
        answer = answer + querySum(2 * u + 1, left, right);
    }
    return answer;
}

int queryMax(int u, int left, int right) {
    int answer = -999999;
    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        return treeNode[u].max;
    }

    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (left <= middle) {
        answer = max(answer, queryMax(2 * u, left, right));
    }
    if (middle < right) {
        answer = max(answer, queryMax(2 * u + 1, left, right));
    }
    return answer;
}

void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

int treeQuerySum(int x, int y) {
    int answer = 0;
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) {
            swap(x, y);
        }
        answer = answer + querySum(1, id[top[x]], id[x]);
        x = father[top[x]];
    }
    if (deep[x] > deep[y]) {
        swap(x, y);
    }
    answer = answer + querySum(1, id[x], id[y]);
    return answer;
}

int treeQueryMax(int x, int y) {
    int answer = -999999;

    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) {
            swap(x, y);
        }
        answer = max(answer, queryMax(1, id[top[x]], id[x]));
        x = father[top[x]];
    }

    if (deep[x] > deep[y]) {
        swap(x, y);
    }
    answer = max(answer, queryMax(1, id[x], id[y]));
    return answer;
}

void update(int u, int key, int val) {
    if (treeNode[u].left == treeNode[u].right) {
        treeNode[u].sum = val;
        treeNode[u].max = val;
        return;
    }
    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (key <= middle) {
        update(2 * u, key, val);
    }
    if (key > middle) {
        update(2 * u + 1, key, val);
    }
    pushdown(u);
}

void addEdge(int u, int v) {
    static int edgeCount;

    edge[edgeCount] = Edge(v, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

int main() {
    memset(head, 0xff, sizeof(head));
    int N = 0, Q = 0;
    cin >> N;
    for (int i = 1; i <= N - 1; i++) {
        int u = 0, v = 0;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i <= N; i++) {
        cin >> weight[i];
    }
    cin >> Q;
    dfs1(1, 0, 1);
    dfs2(1, 1);
    build(1, 1, N);
    for (int _ = 1; _ <= Q; _++) {
        string opt;
        cin >> opt;
        if (opt == "QMAX") {
            int u = 0, v = 0;
            cin >> u >> v;
            cout << treeQueryMax(u, v) << endl;
        } else if (opt == "QSUM") {
            int u = 0, v = 0;
            cin >> u >> v;
            cout << treeQuerySum(u, v) << endl;
        } else if (opt == "CHANGE") {
            int u = 0, t = 0;
            cin >> u >> t;
            update(1, id[u], t);
        }
    }
    return 0;
}