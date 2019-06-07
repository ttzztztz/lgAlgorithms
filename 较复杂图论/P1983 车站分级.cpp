#include<iostream>
#include<vector>
#include<cstring>
#include<deque>
using namespace std;

class MinEdge {
public:
	int end, layer;
	MinEdge() : end(0), layer(0) {};
	MinEdge(int e, int l) : end(e), layer(l) {};
};

int park[1005], inDegree[1005];
int edge[1005][1005];
int n, m, result;

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline void addEdge(int s, int e) {
	static int edgeCount;
	if (s == e || edge[s][e]) {
		return;
	}

	edge[s][e] = 1;
	edgeCount++;
	inDegree[e]++;
}

inline void tpSort() {
	deque<MinEdge> queue;
	
	for (int i = 1; i <= n;i++) {
		if (inDegree[i] == 0) {
			queue.push_back({ i, 1 });
		}
	}

	while (!queue.empty()) {
		auto [u, layer] = queue.front();
		result = max(result, layer);
		queue.pop_front();

		for (int v = 1; v <= n;v++) {
			if (edge[u][v]) {
				inDegree[v]--;
				if (!inDegree[v]) {
					queue.push_back({ v, layer + 1 });
				}
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m;i++) {
		int stationNumber = 0;
		memset(park, 0, sizeof(park));
		vector<int> parkArr;

		cin >> stationNumber;
		for (int j = 1; j <= stationNumber; j++) {
			int number = 0;
			cin >> number;
			park[number] = 1;
			parkArr.push_back(number);
		}

		for (int j = parkArr.front(); j <= parkArr.back(); j++) {
			if (!park[j]) {
				for (int k = 0; k < parkArr.size();k++) {
					addEdge(j, parkArr[k]);
				}
			}
		}
			
	}

	tpSort();
	cout << result;
	return 0;
}
