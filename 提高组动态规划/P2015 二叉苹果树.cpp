#include<iostream>
#include<cstring>
using namespace std;

class Node {
public:
	int apples, leftChild, rightChild;
	Node() : apples(0), leftChild(-1), rightChild(-1) {};
	Node(int a, int l, int r) : apples(a), leftChild(l), rightChild(r) {};
	bool addChild(int index) {
		if (this->leftChild == -1) {
			this->leftChild = index;
			return true;
		}
		else if (this->rightChild == -1) {
			this->rightChild = index;
			return true;
		}
		else {
			return false;
		}
	}
	bool isLeafNode() {
		return this->leftChild == -1 && this->rightChild == -1;
	}
};

const int MAX = 105;
int input[MAX][MAX], dp[MAX][MAX];
Node nodes[MAX];
int N, Q;

inline int max(int x, int y) {
	return x < y ? y : x;
}

void buildTree(int u) {
	for (int v = 1; v <= N; v++) {
		if (input[u][v] >= 0) {
			if (nodes[u].addChild(v)) {
				nodes[v].apples = input[u][v];
				input[u][v] = input[v][u] = -1;
				buildTree(v);
			}
		}
	}
}

void DP(int i, int j) {
	if (j == 0) {
		dp[i][j] = 0;
	}
	else if (nodes[i].isLeafNode()) {
		dp[i][j] = nodes[i].apples;
	}
	else {
		for (int k = 0; k < j; k++) {
			if (dp[nodes[i].leftChild][k] == 0) {
				DP(nodes[i].leftChild, k);
			}
			if (dp[nodes[i].rightChild][j - k - 1] == 0) {
				DP(nodes[i].rightChild, j - k - 1);
			}

			dp[i][j] = max(dp[i][j],
				dp[nodes[i].leftChild][k] + dp[nodes[i].rightChild][j - k - 1]
				+ nodes[i].apples
			);
		}
	}
}

int main() {
	memset(input, 0xff, sizeof(input));
	cin >> N >> Q;
	for (int i = 1; i < N; i++) {
		int from = 0, to = 0, weight = 0;
		cin >> from >> to >> weight;
		input[from][to] = weight;
		input[to][from] = weight;
	}

	buildTree(1);
	DP(1, Q + 1);

	cout << dp[1][Q + 1] << endl;
	return 0;
}