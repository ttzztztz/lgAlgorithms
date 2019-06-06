#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N, M;

class Edge {
public:
	int start, end, weight;
	Edge(int s, int e, int w) :start(s), end(e), weight(w) {};
};

vector<Edge> edge;
const int MAX = 300000;
int parent[MAX], ranks[MAX];

inline int max(int x, int y) {
	return x < y ? y : x;
}

void init() {
	for (int i = 0; i < MAX; i++) {
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
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int start = 0, end = 0, weight = 0;
		cin >> start >> end >> weight;
		edge.push_back({ start, end, weight });
	}

	sort(edge.begin(), edge.end(), [](Edge& $1, Edge& $2)->bool {
		return $1.weight < $2.weight;
		});
	init();

	int finishedCount = 0, result = 0, selected = 0;
	for (Edge& e : edge) {
		if (finishedCount == N - 1) {
			break;
		}
		int parentX = findParent(e.start), parentY = findParent(e.end);
		if (parentX != parentY) {
			merge(parentX, parentY);
			finishedCount++;
			result = max(result, e.weight);
			selected++;
		}
	}

	cout << selected << " " << result;

	return 0;
}