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
int id[MAX], newWeight[MAX], top[MAX], weight[MAX];
int MOD;
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

    TreeNode() : left(0), right(0), sum(0), total(0), lazyTag(0) {};
};

TreeNode treeNode[MAX];

void MODsum(int u) {
    treeNode[u].sum = (treeNode[u * 2].sum + treeNode[u * 2 + 1].sum + MOD) % MOD;
}

void build(int u, int left, int right) {
    treeNode[u].left = left;
    treeNode[u].right = right;
    treeNode[u].total = right - left + 1;
    if (left == right) {
        treeNode[u].sum = newWeight[left];
        return;
    }
    int middle = (left + right) / 2;

    build(u * 2, left, middle);
    build(u * 2 + 1, middle + 1, right);
    MODsum(u);
}

void pushdown(int u) {
    if (!treeNode[u].lazyTag) {
        return;
    }

    treeNode[2 * u].sum = (treeNode[2 * u].sum + treeNode[2 * u].total * treeNode[u].lazyTag) % MOD;
    treeNode[2 * u + 1].sum = (treeNode[2 * u + 1].sum + treeNode[2 * u + 1].total * treeNode[u].lazyTag) % MOD;
    treeNode[2 * u].lazyTag = (treeNode[2 * u].lazyTag + treeNode[u].lazyTag) % MOD;
    treeNode[2 * u + 1].lazyTag = (treeNode[2 * u + 1].lazyTag + treeNode[u].lazyTag) % MOD;

    treeNode[u].lazyTag = 0;
}

void increment(int u, int left, int right, int val) {
    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        treeNode[u].sum += treeNode[u].total * val;
        treeNode[u].lazyTag += val;
        return;
    }

    pushdown(u);
    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (left <= middle) {
        increment(2 * u, left, right, val);
    }
    if (middle < right) {
        increment(2 * u + 1, left, right, val);
    }
    MODsum(u);
}

int query(int u, int left, int right) {
    int answer = 0;

    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        return treeNode[u].sum;
    }
    pushdown(u);

    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (left <= middle) {
        answer = (answer + query(2 * u, left, right)) % MOD;
    }
    if (middle < right) {
        answer = (answer + query(2 * u + 1, left, right)) % MOD;
    }
    return answer;
}

void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

int treeQuery(int x, int y) {
    int answer = 0;
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) {
            swap(x, y);
        }
        answer = (answer + query(1, id[top[x]], id[x])) % MOD;
        x = father[top[x]];
    }
    if (deep[x] > deep[y]) {
        swap(x, y);
    }
    answer = (answer + query(1, id[x], id[y])) % MOD;
    return answer;
}

void treeIncrement(int x, int y, int val) {
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) {
            swap(x, y);
        }
        increment(1, id[top[x]], id[x], val);
        x = father[top[x]];
    }
    if (deep[x] > deep[y]) {
        swap(x, y);
    }
    increment(1, id[x], id[y], val);
}

void addEdge(int u, int v) {
    static int edgeCount;

    edge[edgeCount] = Edge(v, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

int main() {
    memset(head, 0xff, sizeof(head));
    int N = 0, M = 0, R = 0;
    cin >> N >> M >> R >> MOD;
    for (int i = 1; i <= N; i++) {
        cin >> weight[i];
    }
    for (int i = 1; i <= N - 1; i++) {
        int u = 0, v = 0;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    dfs1(R, 0, 1);
    dfs2(R, R);
    build(1, 1, N);
    for (int _ = 1; _ <= M; _++) {
        int opt = 0;
        cin >> opt;
        if (opt == 1) {
            int x = 0, y = 0, z = 0;
            cin >> x >> y >> z;
            treeIncrement(x, y, z % MOD);
        } else if (opt == 2) {
            int x = 0, y = 0;
            cin >> x >> y;
            cout << treeQuery(x, y) << endl;
        } else if (opt == 3) {
            int x = 0, z = 0;
            cin >> x >> z;
            increment(1, id[x], id[x] + total[x] - 1, z % MOD);
        } else if (opt == 4) {
            int x = 0;
            cin >> x;
            cout << query(1, id[x], id[x] + total[x] - 1) << endl;
        }
    }
    return 0;
}
