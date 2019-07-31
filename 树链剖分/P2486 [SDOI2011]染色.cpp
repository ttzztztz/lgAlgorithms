#include <iostream>
#include <cstring>

using namespace std;

class Edge {
public:
    int end, next;

    Edge() : end(0), next(-1) {};

    Edge(int e, int n) : end(e), next(n) {};
};

const int MAX = 400005;
int deep[MAX], father[MAX], heavySon[MAX], total[MAX], head[MAX];
int id[MAX], newColor[MAX], top[MAX], color[MAX];
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
    newColor[count] = color[u];
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
    int left, right, sum, leftColor, rightColor, lazyTag;

    TreeNode() : left(0), right(0), sum(0), leftColor(0), rightColor(0), lazyTag(0) {};
};

TreeNode treeNode[MAX];

void pushup(int u) {
    treeNode[u].sum = treeNode[u * 2].sum + treeNode[u * 2 + 1].sum;
    if (treeNode[u * 2].rightColor == treeNode[u * 2 + 1].leftColor) {
        treeNode[u].sum--;
    }

    treeNode[u].leftColor = treeNode[u * 2].leftColor;
    treeNode[u].rightColor = treeNode[u * 2 + 1].rightColor;
}

void pushLazy(int u, int lazy) {
    treeNode[u].sum = 1;
    treeNode[u].lazyTag = lazy;
    treeNode[u].leftColor = treeNode[u].rightColor = lazy;
}

void pushdown(int u) {
    if (treeNode[u].lazyTag == 0) {
        return;
    }

    pushLazy(2 * u, treeNode[u].lazyTag);
    pushLazy(2 * u + 1, treeNode[u].lazyTag);

    treeNode[u].lazyTag = 0;
}

void build(int u, int left, int right) {
    treeNode[u].left = left;
    treeNode[u].right = right;
    if (left == right) {
        treeNode[u].sum = 1;
        treeNode[u].leftColor = treeNode[u].rightColor = newColor[left];
        return;
    }
    int middle = (left + right) / 2;

    build(u * 2, left, middle);
    build(u * 2 + 1, middle + 1, right);
    pushup(u);
}

void set(int u, int left, int right, int val) {
    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        pushLazy(u, val);
        return;
    }

    pushdown(u);
    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (left <= middle) {
        set(2 * u, left, right, val);
    }
    if (middle < right) {
        set(2 * u + 1, left, right, val);
    }
    pushup(u);
}

int query(int u, int left, int right) {
    int answer = 0;
    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        return treeNode[u].sum;
    }

    pushdown(u);
    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (left <= middle) {
        answer += query(2 * u, left, right);
    }

    if (middle < right) {
        answer += query(2 * u + 1, left, right);
    }

    if (left <= middle && middle < right) {
        if (treeNode[u * 2].rightColor == treeNode[u * 2 + 1].leftColor) {
            answer--;
        }
    }
    return answer;
}

void swap(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

int queryColor(int u, int key) {
    if (treeNode[u].left == key && treeNode[u].right == key) {
        return treeNode[u].leftColor;
    }

    pushdown(u);
    int middle = (treeNode[u].left + treeNode[u].right) / 2;
    if (key <= middle) {
        return queryColor(2 * u, key);
    } else {
        return queryColor(2 * u + 1, key);
    }
}

int treeQuery(int x, int y) {
    int answer = 0, position1 = -1, position2 = -1, leftColor = -1, rightColor = -1;
    while (top[x] != top[y]) {
        if (deep[top[x]] < deep[top[y]]) {
            swap(x, y);
            swap(position1, position2);
        }
        answer += query(1, id[top[x]], id[x]);
        leftColor = queryColor(1, id[top[x]]);
        rightColor = queryColor(1, id[x]);
        if (rightColor == position1) {
            answer--;
        }
        position1 = leftColor;
        x = father[top[x]];
    }
    if (deep[x] > deep[y]) {
        swap(x, y);
        swap(position1, position2);
    }

    answer += query(1, id[x], id[y]);
    leftColor = queryColor(1, id[x]);
    rightColor = queryColor(1, id[y]);
    if (leftColor == position1) {
        answer--;
    }
    if (rightColor == position2) {
        answer--;
    }
    return answer;
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
    memset(head, 0xff, sizeof(head));
    int N = 0, M = 0;
    cin >> N >> M;

    const int R = 1;

    for (int i = 1; i <= N; i++) {
        cin >> color[i];
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
        char opt = 0;
        cin >> opt;
        if (opt == 'C') {
            int a = 0, b = 0, c = 0;
            cin >> a >> b >> c;
            treeSet(a, b, c);
        } else if (opt == 'Q') {
            int a = 0, b = 0;
            cin >> a >> b;
            cout << treeQuery(a, b) << endl;
        }
    }
    return 0;
}
