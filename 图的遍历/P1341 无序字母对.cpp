#include<iostream>
#include<vector>
using namespace std;

const int MAX = 125;
int edge[MAX][MAX], degree[MAX];
int N;
vector<char> stack;

void dfs(int u) {
	for (int i = 0; i < MAX;i++) {
		if (edge[u][i]) {
			edge[u][i] = 0;
			edge[i][u] = 0;
			dfs(i);
		}
	}
	stack.push_back(u);
}

// 欧拉路 -> 找奇数度，字典序最小的节点
// 欧拉图 -> 找字典序最小的节点

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		char ch1 = '\0', ch2 = '\0';
		cin >> ch1 >> ch2;
		edge[ch1][ch2] = 1;
		edge[ch2][ch1] = 1;

		degree[ch1]++;
		degree[ch2]++;
	}

	int oddCount = 0, startPoint = 0;
	for (int i = 0; i < MAX;i++) {
		if (degree[i] && degree[i] & 1) {
			oddCount++;
			if(!startPoint) {
				startPoint = i;
			}
		}
	}

	if (!startPoint) {
		for (int i = 0; i < MAX; i++) {
			if (degree[i]) {
				startPoint = i;
				break;
			}
		}
	}

	if (!(oddCount == 0 || oddCount == 2)) {
		cout << "No Solution";
	}
	else {
		dfs(startPoint);
		for (int i = stack.size() - 1; i >= 0;i--) {
			cout << stack[i];
		}
	}

	return 0;
}