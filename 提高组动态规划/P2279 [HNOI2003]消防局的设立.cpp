#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 1005;
int parent[MAX], minDistance[MAX], depth[MAX], base[MAX];

inline int min(int x, int y) {
	return x < y ? x : y;
}

int main() {
	int N = 0, answer = 0;
	cin >> N;

	parent[1] = 1;
	minDistance[1] = N;
	depth[1] = 0;
	base[1] = 1;

	for (int i = 2; i <= N;i++) {
		int _parent = 0;
		cin >> _parent;
		parent[i] = _parent;
		minDistance[i] = N;
		depth[i] = depth[_parent] + 1;
		base[i] = i;
	}

	sort(base + 1, base + 1 + N, [](const int $1, const int $2)->bool {
		return depth[$1] > depth[$2];
	});
	for (int i = 1; i <= N;i++) {
		int father = parent[base[i]], grandFather = parent[father];
		
		minDistance[base[i]] = min(
			minDistance[base[i]],
			min(
				minDistance[grandFather] + 2,
				minDistance[father] + 1
			)
		);

		if (minDistance[base[i]] > 2) {
			answer++;
			minDistance[base[i]] = 2;
			minDistance[grandFather] = 0;
			minDistance[parent[grandFather]] = min(minDistance[parent[grandFather]], 1);
			minDistance[parent[parent[grandFather]]] = min(minDistance[parent[parent[grandFather]]], 2);
		}
	}

	cout << answer;
	return 0;
}
