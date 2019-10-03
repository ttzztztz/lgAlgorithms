#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

class TreeNode {
public:
    int left, right, total, covered;

    TreeNode() : left(0), right(0), total(0), covered(0) {};
};

class Segment {
public:
    int left, right, height, flag;

    Segment() : left(0), right(0), height(0), flag(0) {};

    Segment(int l, int r, int h, int f) : left(l), right(r), height(h), flag(f) {};
};

const int MAX = 25005;
TreeNode treeNode[MAX];
vector<int> X, Y;
vector<Segment> segment1, segment2;
int step = 1;

int L(int u) {
    return (u << 1);
}

int R(int u) {
    return (u << 1) | 1;
}

int M(int u) {
    return (treeNode[u].left + treeNode[u].right) >> 1;
}

void pushUp(int u) {
    if (treeNode[u].covered) {
        if (step == 1) {
            treeNode[u].total = X[treeNode[u].right] - X[treeNode[u].left - 1];
        } else {
            treeNode[u].total = Y[treeNode[u].right] - Y[treeNode[u].left - 1];
        }
    } else if (treeNode[u].left == treeNode[u].right) {
        treeNode[u].total = 0;
    } else {
        treeNode[u].total = treeNode[L(u)].total + treeNode[R(u)].total;
    }
}

void build(int u, int left, int right) {
    treeNode[u].left = left;
    treeNode[u].right = right;
    treeNode[u].total = treeNode[u].covered = 0;
    if (left == right) {
        return;
    }

    int middle = (left + right) >> 1;
    if (left <= middle) {
        build(L(u), left, middle);
    }
    if (middle < right) {
        build(R(u), middle + 1, right);
    }
    pushUp(u);
}

void update(int u, int left, int right, int flag) {
    if (left <= treeNode[u].left && treeNode[u].right <= right) {
        treeNode[u].covered += flag;
        pushUp(u);
        return;
    }

    int middle = M(u);
    if (left <= middle) {
        update(L(u), left, right, flag);
    }
    if (middle < right) {
        update(R(u), left, right, flag);
    }
    pushUp(u);
}

void init() {
    memset(treeNode, 0, sizeof(treeNode));
}

int main() {
    auto comp = [](const Segment &$1, const Segment &$2) -> bool {
        if ($1.height == $2.height) {
            return $1.flag > $2.flag;
        } else {
            return $1.height < $2.height;
        }
    };

    int N = 0;
    ios::sync_with_stdio(false);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
        cin >> x1 >> y1 >> x2 >> y2;

        segment1.emplace_back(x1, x2, y1, 1);
        segment1.emplace_back(x1, x2, y2, -1);
        X.push_back(x1);
        X.push_back(x2);

        segment2.emplace_back(y1, y2, x1, 1);
        segment2.emplace_back(y1, y2, x2, -1);
        Y.push_back(y1);
        Y.push_back(y2);
    }
    int answer = 0;

    init();
    step = 1;
    std::sort(X.begin(), X.end());
    auto itX = std::unique(X.begin(), X.end());
    for (Segment &segment : segment1) {
        segment.left = std::lower_bound(X.begin(), itX, segment.left) - X.begin();
        segment.right = std::lower_bound(X.begin(), itX, segment.right) - X.begin();
    }
    build(1, 1, itX - X.begin());
    std::sort(segment1.begin(), segment1.end(), comp);
    for (const Segment &segment: segment1) {
        int before = treeNode[1].total;
        update(1, segment.left + 1, segment.right, segment.flag);
        int after = treeNode[1].total;
        answer += abs(before - after);
    }

    init();
    step = 2;
    std::sort(Y.begin(), Y.end());
    auto itY = std::unique(Y.begin(), Y.end());
    for (Segment &segment : segment2) {
        segment.left = std::lower_bound(Y.begin(), itY, segment.left) - Y.begin();
        segment.right = std::lower_bound(Y.begin(), itY, segment.right) - Y.begin();
    }
    build(1, 1, itY - Y.begin());
    std::sort(segment2.begin(), segment2.end(), comp);
    for (const Segment &segment: segment2) {
        int before = treeNode[1].total;
        update(1, segment.left + 1, segment.right, segment.flag);
        int after = treeNode[1].total;
        answer += abs(before - after);
    }

    cout << answer;
    return 0;
}