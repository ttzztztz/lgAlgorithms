#include <iostream>
#include <algorithm>

using namespace std;

class TreeNode {
public:
    int leftNode, rightNode, sum;

    TreeNode() : leftNode(0), rightNode(0), sum(0) {};
};

const int MAX = 200005;
int number[MAX], uniqueNumber[MAX], root[MAX << 5];
TreeNode treeNode[MAX << 5];

int nodeCount = 0;

int build(int left, int right) {
    int root = ++nodeCount;
    treeNode[root].sum = 0;

    if (left < right) {
        int middle = (left + right) / 2;

        treeNode[root].leftNode = build(left, middle);
        treeNode[root].rightNode = build(middle + 1, right);
    }
    return root;
}

int query(int u, int v, int left, int right, int k) {
    if (left >= right) {
        return left;
    }

    int leftNodeU = treeNode[u].leftNode, leftNodeV = treeNode[v].leftNode;
    int rightNodeU = treeNode[u].rightNode, rightNodeV = treeNode[v].rightNode;

    int x = treeNode[leftNodeV].sum - treeNode[leftNodeU].sum;
    int middle = (left + right) / 2;
    if (x >= k) {
        return query(leftNodeU, leftNodeV, left, middle, k);
    } else {
        return query(rightNodeU, rightNodeV, middle + 1, right, k - x);
    }
}

int insert(int previous, int left, int right, int val) {
    int root = ++nodeCount;
    treeNode[root].leftNode = treeNode[previous].leftNode;
    treeNode[root].rightNode = treeNode[previous].rightNode;
    treeNode[root].sum = treeNode[previous].sum + 1;

    if (left < right) {
        int middle = (left + right) / 2;
        if (val <= middle) {
            treeNode[root].leftNode = insert(treeNode[previous].leftNode, left, middle, val);
        } else {
            treeNode[root].rightNode = insert(treeNode[previous].rightNode, middle + 1, right, val);
        }
    }
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    int N = 0, M = 0;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        cin >> number[i];
        uniqueNumber[i] = number[i];
    }

    sort(uniqueNumber + 1, uniqueNumber + 1 + N);
    int upperBound = unique(uniqueNumber + 1, uniqueNumber + 1 + N) - (uniqueNumber + 1);
    root[0] = build(1, upperBound);

    for (int i = 1; i <= N; i++) {
        int val = lower_bound(uniqueNumber + 1, uniqueNumber + 1 + upperBound, number[i]) - uniqueNumber;
        root[i] = insert(root[i - 1], 1, upperBound, val);
    }

    for (int _ = 1; _ <= M; _++) {
        int x = 0, y = 0, z = 0;
        cin >> x >> y >> z;
        int rank = query(root[x - 1], root[y], 1, upperBound, z);
        cout << uniqueNumber[rank] << endl;
    }
    return 0;
}
