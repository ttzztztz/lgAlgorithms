#include<iostream>
using namespace std;

int erasedArr[100005];

enum Relation {
	L, R
};

class SplayNode {
public:
	SplayNode* parent, * children[2];
	int id;
	SplayNode() : parent(nullptr), id(-1) {
		children[0] = nullptr;
		children[1] = nullptr;
	}
	SplayNode(SplayNode* p, int key) : parent(p), id(key) {
		children[0] = nullptr;
		children[1] = nullptr;
	}
};

SplayNode* root;

Relation getRelation(SplayNode* node) {
	if (!node || node->parent == nullptr) {
		return L;
	}
	return node->parent->children[L] == node ? L : R;
}

Relation reverseRelation(Relation relation) {
	return relation == L ? R : L;
}

SplayNode* grandParent(SplayNode* node) {
	if (!node || !node->parent) {
		return nullptr;
	}

	return node->parent->parent;
}

void setSon(SplayNode* parent, SplayNode* son, Relation relation) {
	if (parent) {
		parent->children[relation] = son;
	}
	if (son) {
		son->parent = parent;
	}
}

void rotate(SplayNode* node) {
	SplayNode* grandparent = grandParent(node);
	SplayNode* parent = node->parent;
	SplayNode* children = node->children[reverseRelation(getRelation(node))];

	Relation nodeRelation = getRelation(node);

	setSon(parent, children, nodeRelation);
	setSon(grandparent, node, getRelation(parent));
	setSon(node, parent, reverseRelation(nodeRelation));
}

void splay(SplayNode* node, SplayNode* target = nullptr) {
	if (node == nullptr) {
		return;
	}

	while (node && node->parent != target) {
		SplayNode* parent = node->parent;
		SplayNode* grandparent = grandParent(node);
		if (grandparent) {
			if (getRelation(parent) == getRelation(grandparent)) {
				rotate(node->parent);
			}
			else {
				rotate(node);
			}
		}
		rotate(node);
	}

	if (target == nullptr) {
		root = node;
	}
}

SplayNode* inserted[100005];
bool isFirst = true;

void output(SplayNode* root) {
	if (!root) {
		return;
	}

	output(root->children[L]);
	if (!erasedArr[root->id]) {
		if (isFirst) {
			cout << root->id;
			isFirst = false;
		}
		else {
			cout << " " << root->id;
		}
	}
	output(root->children[R]);
}

void erase(int key) {
	if (erasedArr[key]) {
		return;
	}
	else {
		erasedArr[key] = 1;
	}
}

void insert(int key, int beside, Relation position) {
	SplayNode* besideNode = inserted[beside];
	splay(besideNode);
	SplayNode* curr = besideNode;
	SplayNode* newNode;

	Relation reversedPosition = reverseRelation(position);

	if (!curr->children[position]) {
		newNode = new SplayNode(curr, key);
		curr->children[position] = newNode;
	}
	else {
		curr = curr->children[position];
		while (curr && curr->children[reversedPosition]) {
			curr = curr->children[reversedPosition];
		}
		newNode = new SplayNode(curr, key);
		curr->children[reversedPosition] = newNode;
	}

	inserted[key] = newNode;
}

int main() {
	root = new SplayNode(nullptr, 1);
	inserted[1] = root;

	int N = 0, M = 0;
	cin >> N;
	for (int i = 2; i <= N; i++) {
		int beside = 0, position = 0;
		cin >> beside >> position;
		insert(i, beside, position == 0 ? L : R);

		int q = 0;
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		int key = 0;
		cin >> key;
		erase(key);
	}

	output(root);
	cout << endl;

	return 0;
}