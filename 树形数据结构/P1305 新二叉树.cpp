#include<iostream>
#include<list>
using namespace std;

char tree[256][2];
int n;
list<char> rootCollection;

void recursive(char root) {
	if (root == '*' || !root) {
		return;
	}

	cout << root;
	recursive(tree[root][0]);
	recursive(tree[root][1]);
}

int main() {
	cin >> n;

	for (int i = 0; i < n;i++) {
		char root = '\0', left = '\0', right = '\0';
		cin >> root >> left >> right;

		rootCollection.push_back(root);
		if (left != '*') {
			rootCollection.remove(left);
		}
		if (right != '*') {
			rootCollection.remove(right);
		}

		tree[root][0] = left;
		tree[root][1] = right;
	}

	recursive(*rootCollection.begin());

	return 0;
}