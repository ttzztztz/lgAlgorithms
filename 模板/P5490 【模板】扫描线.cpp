#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class TreeNode {
public:
    int left, right;
    long long total;
    int covered;

    TreeNode() : left(0), right(0), total(0), covered(0) {};
};

class Segment {
public:
    int left, right, height, flag;

    Segment() : left(0), right(0), height(0), flag(0) {};

    Segment(int l, int r, int h, int f) : left(l), right(r), height(h), flag(f) {};
};

TreeNode treeNode[1000005];
vector<int> allX;

int L(int u) {
    return u << 1;
}

int R(int u) {
    return (u << 1) | 1;
}

int M(int u) {
    return (treeNode[u].left + treeNode[u].right) >> 1;
}

void pushUp(int u) {
    if (treeNode[u].covered) {
        treeNode[u].total = allX[treeNode[u].right] - allX[treeNode[u].left - 1];
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

int main() {
    int N = 0;
    cin >> N;

    vector<Segment> segmentList;
    for (int i = 1; i <= N; i++) {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        cin >> x1 >> y1 >> x2 >> y2;

        allX.push_back(x1);
        allX.push_back(x2);

        segmentList.emplace_back(x1, x2, y1, 1);
        segmentList.emplace_back(x1, x2, y2, -1);
    }
    std::sort(allX.begin(), allX.end());
    auto endIt = std::unique(allX.begin(), allX.end());
    for (Segment &segment : segmentList) {
        segment.left = std::lower_bound(allX.begin(), endIt, segment.left) - allX.begin();
        segment.right = std::lower_bound(allX.begin(), endIt, segment.right) - allX.begin();
    }

    build(1, 1, endIt - allX.begin());
    std::sort(segmentList.begin(), segmentList.end(), [](const Segment &$1, const Segment &$2) -> bool {
        return $1.height < $2.height;
    });
    unsigned long long answer = 0L;
    for (int i = 0; i < segmentList.size(); i++) {
        const Segment& segment = segmentList[i];

        update(1, segment.left + 1, segment.right, segment.flag);
        if (i != segmentList.size() - 1) {
            answer += (segmentList[i + 1].height - segmentList[i].height) * treeNode[1].total;
        }
    }
    cout << answer << endl;
    return 0;
}