#include<iostream>
#include<cstring>
#include<deque>
#include<algorithm>
using namespace std;

class EndNode {
public:
	string s;
	int count;
	EndNode() : s(""), count(0) {};
} endNodes[155];

class TrieNode {
public:
	int next[26];
	int count, fail;
	EndNode* endnode;
	TrieNode() : count(0), fail(0), endnode(nullptr) {
		memset(this->next, 0, sizeof(this->next));
	};
} nodes[1000005];

int nodeCount = 0, endNodeCount = 0;
inline void insert(const char* str) {
	int len = strlen(str), now = 0;

	for (int i = 0; i < len;i++) {
		int index = str[i] - 'a';
		if (!nodes[now].next[index]) {
			nodes[now].next[index] = ++nodeCount;
		}
		now = nodes[now].next[index];
	}

	nodes[now].count++;
	nodes[now].endnode = endNodes + endNodeCount;
	nodes[now].endnode->s = str;
	endNodeCount++;
}

inline void build() {
	deque<int> queue;
	for (int i = 0; i < 26;i++) {
		int index = nodes[0].next[i];
		if (index) {
			nodes[index].fail = 0;
			queue.push_back(index);
		}
	}

	while (!queue.empty()) {
		int index = queue.front();
		queue.pop_front();

		for (int i = 0; i < 26;i++) {
			int nextIndex = nodes[index].next[i];
			if (nextIndex) {
				nodes[nodes[index].next[i]].fail = nodes[nodes[index].fail].next[i];
				queue.push_back(nodes[index].next[i]);
			}
			else {
				// 跳转移边的剪枝优化
				nodes[index].next[i] = nodes[nodes[index].fail].next[i];
			}
		}
	}
}

inline void query(const char* str) {
	int len = strlen(str), now = 0;
	for (int i = 0; i < len;i++) {
		int index = str[i] - 'a';
		now = nodes[now].next[index];
		for (int j = now; j;j=nodes[j].fail) {
			if (nodes[j].endnode) {
				nodes[j].endnode->count += nodes[j].count;
			}
		}
	}
}

char buffserStr[1000005];
int main() {
	int n = 0;
	while (cin >> n && n) {
		for (int i = 0; i <= endNodeCount; i++) {
			endNodes[i].count = 0;
			endNodes[i].s = "";
		}
		for (int i = 0; i <= nodeCount; i++) {
			nodes[i].count = 0;
			nodes[i].fail = 0;
			nodes[i].endnode = nullptr;
			memset(nodes[i].next, 0, sizeof(int) * 26);
		}
		nodeCount = endNodeCount = 0;


		for (int i = 0; i < n;i++) {
			cin >> buffserStr;
			insert(buffserStr);
		}
		build();
		cin >> buffserStr;
		query(buffserStr);

		stable_sort(endNodes, endNodes + endNodeCount, [](const EndNode& $1, const EndNode& $2)->bool {
			return $1.count > $2.count;
		});

		int maxCount = endNodes[0].count, currIndex = 0;
		cout << maxCount << endl;
		while (currIndex <= endNodeCount && endNodes[currIndex].count == maxCount) {
			cout << endNodes[currIndex].s << endl;
			currIndex++;
		}
	}
	return 0;
}