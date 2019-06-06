#include<iostream>
using namespace std;

const int MAX = 205;
const int INF = 100000;
int edge[MAX][MAX];
int finishedTime[MAX];
int N, M, Q;

int main() {
	cin >> N >> M;
	for (int i = 1; i <= N;i++) {
		cin >> finishedTime[i];
	}
	
	for (int i = 1; i <= N;i++) {
		for (int j = 1; j <= N;j++) {
			if (i == j) {
				edge[i][j] = 0;
			}
			else {
				edge[i][j] = INF;
			}
		}
	}

	for (int i = 1; i <= M;i++) {
		int s = 0, e = 0, w = 0;
		cin >> s >> e >> w;
		s++;
		e++;
		edge[s][e] = w;
		edge[e][s] = w;
	}
	cin >> Q;

	int k = 1;
	for (int i = 1; i <= Q;i++) {
		int x = 0, y = 0, t = 0;
		cin >> x >> y >> t;
		x++;
		y++;

		while (t >= finishedTime[k] && k <= N) {
			for (int u = 1; u <= N;u++) {
				for (int v = 1; v <= N;v++) {
					if (edge[u][v] > edge[u][k] + edge[k][v]) {
						edge[u][v] = edge[u][k] + edge[k][v];
					}
				}
			}
			k++;
		}

		if (edge[x][y] >= INF || finishedTime[x] > t || finishedTime[y] > t) {
			cout << -1 << endl;
		}
		else {
			cout << edge[x][y] << endl;
		}
	}

	return 0;
}