#include<iostream>
using namespace std;

class TreeNode {
public:
	int L, R;
	TreeNode* leftNode, * rightNode;
	long long sum, add, multiply;
	TreeNode()
		:L(0), R(0), leftNode(nullptr), rightNode(nullptr), sum(0), add(0), multiply(1) {};
	TreeNode(int l, int r, TreeNode* lNode, TreeNode* rNode)
		: L(l), R(r), leftNode(lNode), rightNode(rNode), sum(0), add(0), multiply(1) {};
};

const int MAX = 100005;
TreeNode nodeList[MAX * 4 + 20];
int nodeLength = 0, N, P;
TreeNode* root, * emptyNode;

void buildTree(TreeNode* node, int L, int R) {
	node->L = L;
	node->R = R;

	if (L == R) {
		return;
	}

	int mid = (L + R) / 2;

	node->leftNode = nodeList + nodeLength;
	node->leftNode->leftNode = emptyNode;
	node->leftNode->rightNode = emptyNode;
	nodeLength++;

	node->rightNode = nodeList + nodeLength;
	node->rightNode->leftNode = emptyNode;
	node->rightNode->rightNode = emptyNode;
	nodeLength++;

	buildTree(node->leftNode, L, mid);
	buildTree(node->rightNode, mid + 1, R);
}


void pushDown(TreeNode* node, int L, int R) {
	if (node == emptyNode) {
		return;
	}
	if (node->multiply == 1 && node->add == 0) {
		return;
	}

	if (node->L != node->R) {
		node->leftNode->multiply = (node->leftNode->multiply * node->multiply) % P;
		node->rightNode->multiply = (node->rightNode->multiply * node->multiply) % P;

		node->leftNode->add = ((node->leftNode->add * node->multiply) % P + node->add) % P;
		node->rightNode->add = ((node->rightNode->add * node->multiply) % P + node->add) % P;
	}

	node->sum = ((node->sum * node->multiply) % P + (node->add * (node->R - node->L + 1)) % P) % P;
	node->multiply = 1;
	node->add = 0;
}

void increment(TreeNode* node, int L, int R, long long inc) {
	if (node == emptyNode) {
		return;
	}
	pushDown(node, L, R);
	if (node->L == L && node->R == R) {
		node->add = (node->add + inc) % P;
		return;
	}

	int middle = (node->L + node->R) / 2;
	
	if (R <= middle) {
		increment(node->leftNode, L, R, inc);
	}
	else if (L > middle) {
		increment(node->rightNode, L, R, inc);
	}
	else {
		increment(node->leftNode, L, middle, inc);
		increment(node->rightNode, middle + 1, R, inc);
	}

	pushDown(node->leftNode, L, middle);
	pushDown(node->rightNode, middle + 1, R);

	node->sum = (node->leftNode->sum + node->rightNode->sum) % P;
}

void multiply(TreeNode* node, int L, int R, long long mul) {
	if (node == emptyNode) {
		return;
	}

	pushDown(node, L, R);
	if (node->L == L && node->R == R) {
		node->multiply = (node->multiply * mul) % P;
		node->add = (node->add * mul) % P;
		return;
	}

	int middle = (node->L + node->R) / 2;

	if (R <= middle) {
		multiply(node->leftNode, L, R, mul);
	}
	else if (L > middle) {
		multiply(node->rightNode, L, R, mul);
	}
	else {
		multiply(node->leftNode, L, middle, mul);
		multiply(node->rightNode, middle + 1, R, mul);
	}

	pushDown(node->leftNode, L, middle);
	pushDown(node->rightNode, middle + 1, R);

	node->sum = (node->leftNode->sum + node->rightNode->sum) % P;
}


long long query(TreeNode* node, int L, int R) {
	if (node == emptyNode) {
		return 0;
	}
	pushDown(node, L, R);
	if (node->L == L && node->R == R) {
		return node->sum;
	}

	long long result = 0;
	int middle = (node->L + node->R) / 2;

	if (R <= middle) {
		result = query(node->leftNode, L, R) % P;
	}
	else if (L > middle) {
		result = query(node->rightNode, L, R) % P;
	}
	else {
		result = query(node->leftNode, L, middle) % P;
		result = (result + (query(node->rightNode, middle + 1, R) % P)) % P;
	}
	return result;
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
	cin >> N >> P;

	emptyNode = new TreeNode();
	root = new TreeNode(1, N, emptyNode, emptyNode);
	buildTree(root, 1, N);

	for (int i = 1; i <= N; i++) {
		int number = 0;
		cin >> number;
		insert(root, i, number);
	}

	cin >> M;

	for (int i = 0; i < M; i++) {
		int opt = 0;
		cin >> opt;
		if (opt == 1) {// for each x in [a, b], x *= b
			int x = 0, y = 0, k = 0;
			cin >> x >> y >> k;
			multiply(root, x, y, k);
		}
		else if (opt == 2) {// for each x in [a, b] , x += k
			int x = 0, y = 0, k = 0;
			cin >> x >> y >> k;
			increment(root, x, y, k);
		}
		else if (opt == 3) {// query sum [a, b]
			int x = 0, y = 0;
			cin >> x >> y;
			cout << (query(root, x, y) % P) << endl;
		}
	}

	return 0;
}