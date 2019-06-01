#include<iostream>
using namespace std;
int N;

class TreeNode {
public:
	int L, R;
	TreeNode* leftNode, * rightNode;
	long long sum, increment;
	TreeNode() :L(0), R(0), leftNode(nullptr), rightNode(nullptr), sum(0), increment(0) {};
	TreeNode(int l, int r, TreeNode* lNode, TreeNode* rNode) : L(l), R(r), leftNode(lNode), rightNode(rNode), sum(0), increment(0) {};
};

const int MAX = 100005;
TreeNode nodeList[MAX * 4 + 20];
int nodeLength = 0;
TreeNode* root;

void buildTree(TreeNode* node, int L, int R) {
	node->L = L;
	node->R = R;

	if (L == R) {
		return;
	}

	int mid = (L + R) / 2;

	node->leftNode = nodeList + nodeLength;
	nodeLength++;

	node->rightNode = nodeList + nodeLength;
	nodeLength++;

	buildTree(node->leftNode, L, mid);
	buildTree(node->rightNode, mid + 1, R);
}

void increment(TreeNode* node, int L, int R, long long inc) {
	if (node->L == L && node->R == R) {
		node->increment += inc;
		return;
	}

	node->sum += inc * (R - L + 1);
	int mid = (node->L + node->R) / 2;
	if (L > mid) {
		increment(node->rightNode, L, R, inc);
	} else if (R <= mid){
		increment(node->leftNode, L, R, inc);
	}
	else {
		increment(node->leftNode, L, mid, inc);
		increment(node->rightNode, mid + 1, R, inc);
	}

}

long long query(TreeNode* node, int L, int R) {
	if (node->L == L && node->R == R) {
		return node->sum + node->increment * (R - L + 1);
	}

	int mid = (node->L + node->R) / 2;
	node->sum += node->increment * (node->R - node->L + 1);
	increment(node->leftNode, node->L, mid, node->increment);
	increment(node->rightNode, mid + 1, node->R, node->increment);
	node->increment = 0;

	if (R <= mid) {
		return query(node->leftNode, L, R);
	}
	else if (L > mid) {
		return query(node->rightNode, L, R);
	}
	else {
		return query(node->leftNode, L, mid) + query(node->rightNode, mid + 1, R);
	}
}

void insert(TreeNode* node, int index, int data) {
	if (node->leftNode == node->rightNode) {
		node->sum = data;
		return;
	}

	node->sum += data;

	int mid = (node->L + node->R) / 2;
	if (index <= mid) {
		insert(node->leftNode, index, data);
	}
	else {
		insert(node->rightNode, index, data);
	}
}

int main() {
	int M = 0;
	cin >> N >> M;

	root = new TreeNode(1, N, nullptr, nullptr);
	buildTree(root, 1, N);

	for (int i = 1; i <= N;i++) {
		int number = 0;
		cin >> number;
		insert(root, i, number);
	}

	for (int i = 0; i < M;i++) {
		int opt = 0;
		cin >> opt;
		if (opt == 1) {// for each x in [a, b] , x+= k
			int x = 0, y = 0, k = 0;
			cin >> x >> y >> k;
			increment(root, x, y, k);
		}
		else if (opt == 2) {// query sum [a, b]
			int x = 0, y = 0;
			cin >> x >> y;
			cout << query(root, x, y) << endl;
		}
	}

	return 0;
}