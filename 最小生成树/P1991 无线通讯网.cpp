#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int P, S;

class Edge {
public:
	int start, end;
	double weight;
	Edge(int s, int e, double w) :start(s), end(e), weight(w) {};
};

vector<Edge> edge;
const int MAX = 10005;
int parent[MAX], ranks[MAX];
pair<int, int> position[MAX];

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
	cin >> S >> P;

	for (int i = 1; i <= P; i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		position[i] = { x, y };
	}

	for (int i = 1; i <= P;i++) {
		for (int j = i + 1; j <= P;j++) {
			auto [x1, y1] = position[i];
			auto [x2, y2] = position[j];
			double dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
			edge.push_back({ i,j,dist });
		}
	}

	sort(edge.begin(), edge.end(), [](Edge& $1, Edge& $2)->bool {
		return $1.weight < $2.weight;
		});
	init();

	double result = 0;
	int edgeSize = edge.size();
	int remainVertex = P - S;
	for (int i = 0; i < edgeSize && remainVertex > 0;i++) {
		const Edge& e = edge[i];
		int parentX = findParent(e.start), parentY = findParent(e.end);
		if (parentX != parentY) {
			merge(parentX, parentY);
			result = max(result, e.weight);
			remainVertex--;
		}
	}

	printf("%.2f", result);

	return 0;
}