#include<iostream>
#include<cstring>
using namespace std;

class Edge {
public:
	int start, end, next;
	Edge() :start(0), end(0), next(-1) {};
	Edge(int s, int e, int n) : start(s), end(e), next(n) {};
};

const string OK = "^_^";
const string FAIL = "T_T";
const int MAX = 500;

int T;
int isSchoolStudent[MAX], isGoHome[MAX];

int yUsed[MAX], yParent[MAX];
int head[MAX * 4];
Edge edge[MAX * 4];

void init() {
	memset(head, 0xff, sizeof(head));
	memset(edge, 0xff, sizeof(edge));
	memset(isSchoolStudent, 0, sizeof(isSchoolStudent));
	memset(isGoHome, 0, sizeof(isGoHome));
	memset(yUsed, 0, sizeof(yUsed));
	memset(yParent, 0, sizeof(yParent));
}

void addEdge(int s, int e) {
	static int edgeCount;

	edge[edgeCount] = Edge(s, e, head[s]);
	head[s] = edgeCount;
	edgeCount++;
}

int find(int x) {
	for (int i = head[x]; i != -1; i = edge[i].next) {
		const Edge& e = edge[i];

		if (isSchoolStudent[e.end] && !yUsed[e.end]) {
			yUsed[e.end] = 1;
			if (!yParent[e.end] || find(yParent[e.end])) {
				yParent[e.end] = x;
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	cin >> T;
	for (int _ = 0; _ < T; _++) {
		int n = 0, totalNumber = 0;
		cin >> n;
		init();

		for (int j = 1; j <= n;j++) {
			cin >> isSchoolStudent[j];
		}
		for (int j = 1; j <= n;j++) {
			cin >> isGoHome[j];

			if (!(isSchoolStudent[j] && isGoHome[j])) {
				totalNumber++;
			}

			if (isSchoolStudent[j] && !isGoHome[j]) {
				addEdge(j, j);
			}
		}

		for (int i = 1; i <= n;i++) {
			for (int j = 1; j <= n; j++) {
				int edgeInfo = 0;
				cin >> edgeInfo;

				if (i != j && edgeInfo && !(isSchoolStudent[i] && isGoHome[i])
					&& isSchoolStudent[j]
					) {
					addEdge(i, j);
				}
			}
		}
		
		int number = 0;
		for (int x = 1; x <= n;x++) {
			memset(yUsed, 0, sizeof(yUsed));
			if (!(isSchoolStudent[x] && isGoHome[x]) && find(x)) {
				number++;
			}
		}

		if (number >= totalNumber) {
			cout << OK << endl;
		}
		else {
			cout << FAIL << endl;
		}
	}
	return 0;
}