#include<iostream>
#include<queue>
#include<vector>
using namespace std;

class Node {
public:
	int index, money;
	Node()
		: index(0), money(0) {};
	Node(int i, int m)
		: index(i), money(m) {};
	bool operator< (const Node& $2) const {
		return this->money < $2.money;
	}
};

const int MAX = 500005;
bool visited[MAX];
int N, K, L[MAX], R[MAX];
priority_queue<Node> list;
Node nodeList[MAX];

int main() {
	cin >> N >> K;

	long long answer = 0;
	for (int i = 1; i <= N; i++) {
		int money = 0;
		cin >> money;
		Node newNode(i, money);
		L[i] = i - 1;
		R[i] = i + 1;
		list.push(newNode);
		nodeList[i] = newNode;
	}

	int offset = 0;
	while (offset < K && !list.empty()) {
		Node node;
		do {
			node = list.top();
			list.pop();
		} while (visited[node.index] && !list.empty());

		if (!visited[node.index]) {
			if (node.money <= 0) {
				break;
			}
			answer += node.money;

			visited[L[node.index]] = true;
			visited[R[node.index]] = true;

			int money = nodeList[R[node.index]].money + nodeList[L[node.index]].money - node.money;
			nodeList[node.index].money = money;

			L[node.index] = L[L[node.index]];
			R[node.index] = R[R[node.index]];

			R[L[node.index]] = node.index;
			L[R[node.index]] = node.index;

			list.push({ node.index, money });
		}
		offset++;
	}

	cout << answer;
	return 0;
}