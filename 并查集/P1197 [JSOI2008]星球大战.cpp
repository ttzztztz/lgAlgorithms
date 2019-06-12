#include<iostream>
#include<cstring>
using namespace std;

class Edge {
public:
	int from, to, next;
	Edge() :from(-1), to(-1), next(-1) {};
	Edge(int f, int t, int n) : from(f), to(t), next(n) {};
};

const int MAX = 400005;
int parent[MAX], head[MAX], brokenOrder[MAX], answer[MAX];
bool broken[MAX], check[MAX];
int N, M, k, edgeCount;
Edge edge[MAX];

void init() {
	for (int i = 0; i < MAX;i++) {
		parent[i] = i;
	}
	memset(head, 0xff, sizeof(head));
}

int findParent(int x) {
	if (parent[x] == x) {
		return parent[x];
	}
	else {
		return parent[x] = findParent(parent[x]);
	}
}

void merge(int x, int y) {
	int parentX = findParent(x), parentY = findParent(y);
	parent[parentX] = parentY;
}

void addEdge(int from, int to) {
	edge[edgeCount] = { from , to , head[from] };
	head[from] = edgeCount;
	edgeCount++;
}

int calcResult() {
	int result = 0;
	for (int i = 1; i <= N; i++) {
		int parent = findParent(i);
		if (!check[parent] && !broken[i]) {
			result++;
			check[parent] = true;
		}
	}
	return result;
}

int main() {
	init();
	cin >> N >> M;
	for (int i = 1; i <= M;i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		x++; y++;

		addEdge(x, y);
		addEdge(y, x);
	}
	cin >> k;
	for (int i = 0; i < k;i++) {
		int v = 0;
		cin >> v;
		v++;

		brokenOrder[i] = v;
		broken[v] = true;
	}

	for (int i = 0; i < edgeCount; i += 2) {
		Edge& e = edge[i];
		if (!broken[e.from] && !broken[e.to]) {
			merge(e.from, e.to);
		}
	}

	answer[k] = calcResult();

	int tempAnswer = answer[k];
	for (int i = k - 1; i >= 0; i--) {
		tempAnswer++;
		int newPoint = brokenOrder[i];
		broken[newPoint] = false;
		for (int j = head[newPoint]; j != -1;j=edge[j].next) {
			Edge& _e = edge[j];
			if (!broken[_e.from] && !broken[_e.to]) {
				int parentX = findParent(_e.from), parentY = findParent(_e.to);
				if (parentX != parentY) {
					merge(_e.from, _e.to);

					tempAnswer--;
				}
			}
		}
		answer[i] = tempAnswer;
	}

	for (int i = 0; i <= k;i++) {
		cout << answer[i] << endl;
	}

	return 0;
}