#include <iostream>
#include <cstring>

using namespace std;

class Edge {
public:
    int end, next;

    Edge() : end(0), next(-1) {};

    Edge(int e, int n) : end(e), next(n) {};
};

const int MAX = 200005;
int deep[MAX], father[MAX], heavySon[MAX], total[MAX], head[MAX];
int id[MAX], top[MAX];
int weight[MAX], newWeight[MAX];
Edge edge[MAX];

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
    int left, right, sum, total, lazyTag;

    TreeNode() : left(0), right(0), sum(0), total(0), lazyTag(-1) {};
};

TreeNode treeNode[MAX * 2];

void build(int u, int left, int right) {
    treeNode[u].left = left;
    treeNode[u].right = right;
    treeNode[u].total = right - left + 1;
    if (left == right) {
        treeNode[u].sum = 0;
        return;
    }

    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    build(2 * u, left, middle);
    build(2 * u + 1, middle + 1, right);
    treeNode[u].sum = treeNode[2 * u].sum + treeNode[2 * u + 1].sum;
}

void pushdown(int u) {
    if (treeNode[u].lazyTag == -1) {
        return;
    }

    treeNode[2 * u].sum = treeNode[2 * u].total * treeNode[u].lazyTag;
    treeNode[2 * u + 1].sum = treeNode[2 * u + 1].total * treeNode[u].lazyTag;
    treeNode[2 * u].lazyTag = treeNode[2 * u + 1].lazyTag = treeNode[u].lazyTag;

    treeNode[u].lazyTag = -1;
}

void set(int u, int left, int right, int val) {
    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        treeNode[u].lazyTag = val;
        treeNode[u].sum = treeNode[u].total * val;
        return;
    }

    pushdown(u);
    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (left <= middle) {
        set(2 * u, left, right, val);
    }
    if (right > middle) {
        set(2 * u + 1, left, right, val);
    }
    treeNode[u].sum = treeNode[2 * u].sum + treeNode[2 * u + 1].sum;
}

void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

void treeSet(int x, int y, int val) {
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) {
            swap(x, y);
        }
        set(1, id[top[x]], id[x], val);
        x = father[top[x]];
    }
    if (deep[x] > deep[y]) {
        swap(x, y);
    }
    set(1, id[x], id[y], val);
}

void addEdge(int u, int v) {
    static int edgeCount;

    edge[edgeCount] = Edge(v, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

int main() {
    ios::sync_with_stdio(false);

    memset(head, 0xff, sizeof(head));
    int N = 0, M = 0, R = 1;
    cin >> N;
    for (int i = 2; i <= N; i++) {
        int v = 0;
        cin >> v;
        v++;
        addEdge(i, v);
        addEdge(v, i);
    }
    dfs1(R, 0, 1);
    dfs2(R, R);
    build(1, 1, count);

    cin >> M;
    for (int _ = 1; _ <= M; _++) {
        string opt;
        int package = 0;
        cin >> opt >> package;
        package++;

        int previous = treeNode[1].sum;
        if (opt == "install") {
            treeSet(R, package, 1);
        } else if (opt == "uninstall") {
            set(1, id[package], id[package] + total[package] - 1, 0);
        }
        int after = treeNode[1].sum;
        cout << abs(previous - after) << endl;
    }

    return 0;
}
