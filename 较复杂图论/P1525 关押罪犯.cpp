#include<iostream>
#include<algorithm>
using namespace std;

class Relation {
public:
	int x, y, weight;
	Relation() : x(0), y(0), weight(0) {};
	Relation(int _x, int _y, int w) : x(_x), y(_y), weight(w) {};
};

const int MAX = 20005;
int parent[MAX], defense[MAX];
int N, M;
Relation relation[100005];


inline void init() {
	for (int i = 0; i < MAX;i++) {
		parent[i] = i;
	}
}

inline int find(int x) {
	if (parent[x] == x) {
		return x;
	}
	else {
		return parent[x] = find(parent[x]);
	}
}

inline void merge(int x, int y) {
	int parentX = find(x), parentY = find(y);
	if (parentX != parentY) {
		parent[parentX] = parentY;
	}
}

int main() {
	init();
	cin >> N >> M;
	for (int i = 0; i < M;i++) {
		int x = 0, y = 0, w = 0;
		cin >> x >> y >> w;
		relation[i] = { x, y ,w };
	}

	sort(relation, relation + M, [](const Relation& $1, const Relation $2)->bool {
		return $1.weight > $2.weight;
	});

	for (int i = 0; i < M;i++) {
		const Relation& r = relation[i];
		int parentX = find(r.x), parentY = find(r.y);

		if (parentX == parentY) {
			cout << r.weight;
			return 0;
		}
		else {
			if (defense[r.x]) {
				merge(defense[r.x], r.y);
			}
			else {
				defense[r.x] = r.y;
			}

			if (defense[r.y]) {
				merge(defense[r.y], r.x);
			}
			else {
				defense[r.y] = r.x;
			}

		}
	}

	cout << 0;
	return 0;
}