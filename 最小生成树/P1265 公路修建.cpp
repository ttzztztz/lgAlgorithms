#include<iostream>
#include<cmath>
using namespace std;

class Edge {
public:
	double start, end;
	Edge(double s, double e) :start(s), end(e) {};
};

const int MAX = 5005;
pair<double, double> point[MAX];
double dist[MAX];
bool visited[MAX];

double calcDist(int i, int j) {
	auto [x1, y1] = point[i];
	auto [x2, y2] = point[j];
	return sqrt((double)(x1 - x2) * (x1 - x2) + (double)(y1 - y2) * (y1 - y2));
}

int main() {
	int N = 0;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		double x = 0, y = 0;
		cin >> x >> y;
		point[i] = {x, y};
		dist[i] = 0x7fffffff;
	}

	double result = 0;
	dist[1] = 0;

	for (int i = 1; i <= N;i++) {
		double minWeight = 0x7fffffff;
		int minIndex = -1;

		for (int j = 1; j <= N;j++) {
			if (!visited[j] && dist[j] < minWeight) {
				minWeight = dist[j];
				minIndex = j;
			}
		}

		if (minIndex != -1) {
			result += minWeight;
			visited[minIndex] = true;

			for (int j = 1; j <= N; j++) {
				double distNow = calcDist(minIndex, j);
				if (distNow < dist[j]) {
					dist[j] = distNow;
				}
			}
		}
		
	}

	printf("%.2lf", result);
	return 0;
}