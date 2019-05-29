#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int vertexCount = 0, edgeCount = 0;

class Edge {
public:
	int start, end, weight;
	Edge(int s, int e, int w) :start(s), end(e), weight(w) {};
};

vector<Edge> edge;
const int MAX = 300000;
int parent[MAX], ranks[MAX];

void init() {
	for (int i = 0; i < MAX;i++) {
		parent[i] = i;
		ranks[i] = 0;
	}
}

int findParent(int x) {
	if (parent[x] == x) {
		return x;
	}

	return parent[x] = findParent(parent[x]);
}

void merge(int x, int y) {
	int parentX = findParent(x), parentY = findParent(y);
	if (ranks[parentX] < ranks[parentY]) {
		parent[parentX] = parentY;
	}
	else {
		if (ranks[parentX] == ranks[parentY]) {
			ranks[parentX] ++;
		}
		parent[parentY] = parentX;
	}
}

int main() {
	cin >> vertexCount >> edgeCount;
	for (int i = 0; i < edgeCount;i++) {
		int s = 0, e = 0, w = 0;
		cin >> s >> e >> w;
		edge.push_back(Edge(s, e, w));
	}

	sort(edge.begin(), edge.end(), [](Edge& $1, Edge& $2)->bool {
		return $1.weight < $2.weight;
	});
	init();

	int result = 0;
	for (Edge& e: edge) {
		int parentX = findParent(e.start), parentY = findParent(e.end);
		if (parentX != parentY) {
			merge(parentX, parentY);
			result += e.weight;
		}
	}

	cout << result;
	return 0;
}