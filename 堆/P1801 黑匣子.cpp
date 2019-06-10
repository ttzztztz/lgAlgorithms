#include<iostream>

enum Relation {
	L, R
};

class SplayNode {
public:
	int count, value, size;
	SplayNode* child[2];
	SplayNode* parent;
	SplayNode() : count(1), value(0), size(1), parent(nullptr) {
		child[L] = nullptr;
		child[R] = nullptr;
	};
	SplayNode(SplayNode* p, int v) :value(v), size(1), count(1), parent(p) {
		child[L] = nullptr;
		child[R] = nullptr;
	}
};

Relation getRelation(SplayNode* node) {
	if (node->parent) {
		return node->parent->child[L] == node ? L : R;
	}
	else {
		return L;
	}
}

SplayNode* getGrandParent(SplayNode* node) {
	return node->parent ? node->parent->parent : nullptr;
}

Relation reverseRelation(Relation r) {
	return r == L ? R : L;
}

void setSon(SplayNode* parent, SplayNode* son, Relation relation) {
	if (parent) {
		parent->child[relation] = son;
	}
	if (son) {
		son->parent = parent;
	}
}

void maintain(SplayNode* node) {
	if (node) {
		int leftSize = node->child[L] ? node->child[L]->size : 0;
		int rightSize = node->child[R] ? node->child[R]->size : 0;

		node->size = leftSize + rightSize + node->count;
	}
}

void rotate(SplayNode* node) {
	if (!node) {
		return;
	}

	SplayNode* parent = node->parent;
	SplayNode* grandParent = getGrandParent(node);
	SplayNode* child = node->child[reverseRelation(getRelation(node))];
	Relation nodeRelation = getRelation(node);


	setSon(parent, child, nodeRelation);
	setSon(grandParent, node, getRelation(parent));
	setSon(node, parent, reverseRelation(nodeRelation));

	maintain(parent);
	maintain(node);
}

SplayNode* root;

void splay(SplayNode* curr, SplayNode* target = nullptr) {
	if (!curr) {
		return;
	}

	while (curr && curr->parent != target) {
		SplayNode* parent = curr->parent;
		SplayNode* grandparent = getGrandParent(curr);

		if (grandparent) {
			if (getRelation(parent) == getRelation(grandparent)) {
				rotate(parent);
			}
			else {
				rotate(curr);
			}
		}
		rotate(curr);
	}

	if (!target) {
		root = curr;
	}
}

int rank(SplayNode* node) {
	if (!node) {
		return 0;
	}
	else {
		return node->child[L] ? node->child[L]->size : 0;
	}
}

void insert(SplayNode* curr, int val) {
	SplayNode* previous = nullptr;
	while (curr && curr->value != val) {
		previous = curr;
		curr = curr->child[val < curr->value ? L : R];
	}

	if (curr) {
		curr->count++;
		maintain(curr);
	}
	else {
		Relation r = val < previous->value ? L : R;
		previous->child[r] = new SplayNode(previous, val);
		curr = previous->child[r];
	}
	splay(curr);
}

SplayNode* select(SplayNode* node, int k) {
	SplayNode* curr = node;

	while (!(k >= rank(curr) && k < rank(curr) + curr->count)) {
		if (k < rank(curr)) {
			curr = curr->child[L];
		}
		else {
			k -= rank(curr) + curr->count;
			curr = curr->child[R];
		}
	}

	splay(curr);
	return curr;
}

int arr[200005], now = 1, indicator = 0;
int main() {
	root = new SplayNode(nullptr, 0);
	int N = 0, M = 0;
	std::cin >> M >> N;

	for (int i = 1; i <= M;i++) {
		std::cin >> arr[i];
	}

	for (int i = 0; i < N;i++) {
		int query = 0;
		std::cin >> query;
		if (now == 1) {
			root->value = arr[1];
			now++;
		}
		while (query >= now) {
			insert(root, arr[now]);
			now++;
		}
		SplayNode* result = select(root, indicator++);
		std::cout << result->value << std::endl;
	}

	return 0;
}