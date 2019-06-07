#include<iostream>
#include<cstring>
using namespace std;

const int MAX = 35;
int dimension = 0;
int edge[MAX][MAX];

inline int min(int x, int y) {
	return x < y ? x : y;
}

int main() {
	while (cin >> dimension && dimension != 0) {
		int result = 0;
		memset(edge, 0, sizeof(edge));

		for (int i = 1; i <= dimension;i++) {
			for (int j = i + 1; j <= dimension;j++) {
				cin >> edge[i][j];
			}
		}

		result = edge[1][2];
		for (int i = 3; i <= dimension;i++) {
			int tmp = 0x7fffffff;
			for (int j = 2; j <= i - 1;j++) {
				tmp = min((edge[1][i] + edge[j][i] - edge[1][j]) / 2, tmp);
			}
			result += tmp;
		}

		cout << result << endl;
	}
	return 0;
}