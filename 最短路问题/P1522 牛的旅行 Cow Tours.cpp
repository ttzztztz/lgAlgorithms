#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

const int MAX = 155;
const int INF = 99999999;
int N;
pair<int, int> map[MAX];

double farthestPointDistance[MAX];
double dist[MAX][MAX];

int color[MAX], blockCount = 0;

double calcDistance(pair<int, int> $1, pair<int, int> $2) {
	auto [x1, y1] = $1;
	auto [x2, y2] = $2;

	return sqrt(($1.first - $2.first) * ($1.first - $2.first) + ($1.second - $2.second) * ($1.second - $2.second));
}

void dfs(int u, int newColor) {
	for (int v = 0; v < N;v++) {
		if (dist[u][v] > 0 && !color[v] && dist[u][v] < INF) {
			color[v] = newColor;
			dfs(v, newColor);
		}
	}
}

double max(double x, double y) {
	return x < y ? y : x;
}

double min(double x, double y) {
	return x < y ? x : y;
}

int main() {
	char buffer[MAX];
	memset(buffer, 0, sizeof(buffer));

	cin >> N;
	for (int i = 0; i < N;i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		map[i] = { x, y };
	}

	for (int i = 0; i < N;i++) {
		for (int j = 0; j < N;j++) {
			if (i == j) {
				dist[i][j] = 0;
			}
			else {
				dist[i][j] = INF;
			}
		}
	}

	for (int i = 0; i < N;i++) {
		cin >> buffer;
		for (int j = 0; j < N;j++) {
			if (buffer[j] == '1') {
				dist[i][j] = calcDistance(map[i], map[j]);
			}
		}
	}

	for (int i = 0; i < N;i++) {
		if (!color[i]) {
			dfs(i, ++blockCount);
		}
	}

	for (int k = 0; k < N;k++) {
		for (int i = 0; i < N;i++) {
			for (int j = 0; j < N;j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	double maxDist = 0, minDist = 0x7fffffff;
	for (int i = 0; i < N;i++) {
		for (int j = 0; j < N;j++) {
			if (dist[i][j] < INF && dist[i][j] > 0) {
				if (farthestPointDistance[i] < dist[i][j]) {
					farthestPointDistance[i] = dist[i][j];
				}
			}
			maxDist = max(maxDist, farthestPointDistance[i]);
		}
	}

	for (int i = 0; i < N;i++) {
		for (int j = 0; j < N;j++) {
			if (dist[i][j] >= INF) {
				minDist = min(minDist, farthestPointDistance[i] + farthestPointDistance[j] + calcDistance(map[i], map[j]));
			}
		}
	}

	printf("%.6f", max(minDist, maxDist));
	return 0;
}