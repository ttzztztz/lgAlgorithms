#include<iostream>
#include<vector>
using namespace std;

const int MAX = 200005;
int map[MAX], N, timestamp, DFN[MAX], LOW[MAX];
bool inStack[MAX];
int result = 0x7fffffff;
vector<int> stack;

inline int min(int x, int y) {
	return x < y ? x : y;
}

void tarjan(int u) {
	inStack[u] = 1;
	stack.push_back(u);
	DFN[u] = LOW[u] = ++timestamp;
	int v = map[u];

	if (!DFN[v]) {
			tarjan(v);
			LOW[u] = min(LOW[u], LOW[v]);
	}
	else if (inStack[v]) {
		LOW[u] = min(LOW[u], DFN[v]);
	}

	if (LOW[u] == DFN[u]) {
		int v = -1, number = 0;
		do {
			v = stack.back();
			stack.pop_back();
			number++;
		} while (u != v && !stack.empty());
		if (number >= 3) {
			result = min(result, number);
		}
	}
	
}

int main() {
	cin >> N;
	for (int i = 1; i <= N;i++) {
		cin>>map[i];
	}
	for (int i = 1; i <= N;i++) {
		if (!inStack[i]) {
			tarjan(i);
		}
	}
	cout << result;
	return 0;
}