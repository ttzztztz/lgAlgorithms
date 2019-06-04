#include<iostream>
#include<algorithm>
using namespace std;

class Road {
public:
	int start, end, time;
	Road() : start(0), end(0), time(0) {};
	Road(int s, int e, int t) : start(s), end(e), time(t) {};
};

int N, M;
const int MAX = 100005;
Road road[MAX];
int parent[1005];

void init() {
	for (int i = 0; i < N + 1;i++) {
		parent[i] = i;
	}
}

int find(int x) {
	if (parent[x] == x) {
		return x;
	}
	return parent[x] = find(parent[x]);
}

void merge(int x, int y) {
	int parentX = find(x), parentY = find(y);

	if (parentX != parentY) {
		parent[parentX] = parentY;
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < M;i++) {
		int s = 0, e = 0, t = 0;
		cin >> s >> e >> t;
		road[i] = { s ,e ,t };
	}

	sort(road, road + M, [](const Road& $1, const Road& $2)->bool {
		return $1.time < $2.time;
	});

	init();

	int finishedCount = 0;
	for (int i = 0; i < M;i++) {
		const Road& r = road[i];
		int parentX = find(r.start), parentY = find(r.end);
		if (parentX != parentY) {
			finishedCount++;
			merge(parentX, parentY);
			if (finishedCount == N - 1) {
				cout << r.time;
				break;
			}
		}
	}

	if (finishedCount != N - 1) {
		cout << -1;
	}
	return 0;
}