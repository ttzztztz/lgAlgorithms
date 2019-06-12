#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<sstream>
using namespace std;

class Edge {
public:
	int start, end, next;
	Edge() :start(0), end(0), next(-1) {};
	Edge(int s, int e, int n) : start(s), end(e), next(n) {};
};

const int MAX = 50005;
int head[MAX * 2];
Edge edge[MAX * 2];
int N, M, maxContain;

const int MAX_VERTEX = 5005;
int DFN[MAX_VERTEX], LOW[MAX_VERTEX];
vector<int> stack;
string maxList;
bool inStack[MAX_VERTEX];

void init() {
	memset(head, 0xff, sizeof(head));
}

void addEdge(int s, int e) {
	static int edgeCount;

	edge[edgeCount] = Edge(s, e, head[s]);
	head[s] = edgeCount;
	edgeCount++;
}

inline int min(int x, int y) {
	return x < y ? x : y;
}

inline void tarjan(int u) {
	static int offset;
	inStack[u] = true;
	stack.push_back(u);
	DFN[u] = LOW[u] = ++offset;
	for (int i = head[u]; i != -1; i = edge[i].next) {
		const Edge& e = edge[i];
		int v = e.end;

		if (!DFN[v]) {
			tarjan(v);
			LOW[u] = min(LOW[v], LOW[u]);
		}
		else if (inStack[v]) {
			LOW[u] = min(DFN[v], LOW[u]);
		}
	}

	if (DFN[u] == LOW[u]) {
		vector<int> s;
		
		int v = -1, count = 0;
		do {
			v = stack.back();
			inStack[v] = false;
			count++;
			s.push_back(v);
			stack.pop_back();
		} while (!stack.empty() && u != v);

		sort(s.begin(), s.end());
		string str = "";
		for (int k = 0; k < s.size();k++) {
			stringstream ss;
			int i = s[k];
			string temp;
			ss << i;
			ss >> temp;

			if (k != s.size() - 1) {
				temp += " ";
			}
			str += temp;
		}

		if (count > maxContain || (count == maxContain && str >= maxList)) {
			maxContain = count;
			maxList = str;
		}
	}
}

int main() {
	cin >> N >> M;
	init();

	for (int i = 1; i <= M;i++) {
		int type = 0, start = 0, end = 0;
		cin >> start >> end >> type;
		addEdge(start, end);
		if (type == 2) {
			addEdge(end, start);
		}
	}

	for (int u = 1; u <= N;u++) {
		if (!DFN[u]) {
			tarjan(u);
		}
	}

	cout << maxContain << endl << maxList;

	return 0;
}