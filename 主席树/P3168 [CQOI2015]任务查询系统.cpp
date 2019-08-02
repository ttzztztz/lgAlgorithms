#include <iostream>
#include <algorithm>

using namespace std;


class TreeNode {
public:
    int leftNode, rightNode, sum, count;

    TreeNode() : leftNode(0), rightNode(0), sum(0), count(0) {};
};

const int MAX = 200005;
pair<int, int> taskList[MAX * 2];
TreeNode treeNode[MAX << 5];
int root[MAX << 5], upperBound;

int originPriority[MAX], originPriorityCount = 0;

int nodeCount = 0;

int build(int left, int right) {
    int u = ++nodeCount;

    if (left < right) {
        int middle = (left + right) / 2;

        treeNode[u].leftNode = build(left, middle);
        treeNode[u].rightNode = build(middle + 1, right);
    }
    return u;
}

int query(int u, int left, int right, int k) {
    if (left >= right) {
        return treeNode[u].sum / treeNode[u].count * k;
    }

    int middle = (left + right) / 2;
    int x = treeNode[treeNode[u].leftNode].count;
    if (k <= x) {
        return query(treeNode[u].leftNode, left, middle, k);
    } else {
        return treeNode[treeNode[u].leftNode].sum + query(treeNode[u].rightNode, middle + 1, right, k - x);
    }
}

int insert(int previous, int left, int right, int rank, int k) {
    int u = ++nodeCount;

    int valueAbs = originPriority[rank - 1];
    treeNode[u] = treeNode[previous];

    if (left < right) {
        int middle = (left + right) / 2;
        if (rank <= middle) {
            treeNode[u].leftNode = insert(treeNode[previous].leftNode, left, middle, rank, k);
        } else {
            treeNode[u].rightNode = insert(treeNode[previous].rightNode, middle + 1, right, rank, k);
        }

        treeNode[u].count = treeNode[treeNode[u].leftNode].count + treeNode[treeNode[u].rightNode].count;
        treeNode[u].sum = treeNode[treeNode[u].leftNode].sum + treeNode[treeNode[u].rightNode].sum;
    } else {
        treeNode[u].count += k;
        treeNode[u].sum += k * valueAbs;
    }

    return u;
}

int main() {
    int M = 0, N = 0, taskListCount = 0;

    cin >> M >> N;
    for (int i = 1; i <= M; i++) {
        int start = 0, end = 0, priority = 0;
        cin >> start >> end >> priority;
        taskList[taskListCount] = {start, priority};
        originPriority[originPriorityCount] = priority;
        taskListCount++;
        originPriorityCount++;

        taskList[taskListCount] = {end + 1, -priority};
        taskListCount++;
    }

    sort(taskList, taskList + taskListCount,
         [](const pair<int, int> &$1, const pair<int, int> &$2) -> bool {
             return $1.first < $2.first;
         });

    sort(originPriority, originPriority + originPriorityCount);
    upperBound = unique(originPriority, originPriority + originPriorityCount) - originPriority;
    root[0] = build(1, upperBound);

    int taskListPtr = 0;
    for (int t = 1; t <= N; t++) {
        root[t] = root[t - 1];

        while (taskList[taskListPtr].first == t) {
            if (taskListPtr >= taskListCount) {
                break;
            }

            auto[time, priority] = taskList[taskListPtr];
            if (time == t) {
                int rank = lower_bound(originPriority, originPriority + upperBound, priority < 0 ? -priority : priority)
                           - originPriority + 1;

                root[t] = insert(root[t], 1, upperBound, rank, priority < 0 ? -1 : 1);
                taskListPtr++;
            }
        }
    }

    int pre = 1;
    for (int i = 1; i <= N; i++) {
        int X = 0, A = 0, B = 0, C = 0;
        cin >> X >> A >> B >> C;
        int K = ((long long)A * pre + B) % C + 1;

        if (treeNode[root[X]].count <= K) {
            pre = treeNode[root[X]].sum;
        } else {
            pre = query(root[X], 1, upperBound, K);
        }
        cout << pre << endl;
    }
    return 0;
}