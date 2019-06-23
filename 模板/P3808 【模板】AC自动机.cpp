#include<iostream>
#include<cstring>
#include<deque>
using namespace std;

class TrieNode {
public:
	int next[26];
	int count, fail;
	TrieNode() : count(0), fail(0) {
		memset(this->next, 0, sizeof(this->next));
	};
} nodes[1000005];

int answer = 0, nodeCount = 0;

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
		for (int j = now; j && nodes[j].count != -1;j=nodes[j].fail) {
			answer += nodes[j].count;
			nodes[j].count = -1;
		}
	}
}

char buffserStr[1000005];
int main() {
	int n = 0;
	cin >> n;
	for (int i = 0; i < n;i++) {
		cin >> buffserStr;
		insert(buffserStr);
	}
	build();

	cin >> buffserStr;
	query(buffserStr);

	cout << answer;
	return 0;
}