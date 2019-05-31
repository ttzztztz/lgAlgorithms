#include<iostream>
#include<cstring>
using namespace std;

enum Color {
	undefined, Red, Black
};

class Edge {
public:
	int start, end, next;
	Edge() : start(0), end(0), next(-1) {};
	Edge(int s, int e, int n) : start(s), end(e), next(n) {};
};

const int MAX_VERTEX = 10005, MAX_EDGE = 200005;
int N, M;
int head[MAX_VERTEX], numbers[3];
Color vertexColor[MAX_VERTEX];
Edge edges[MAX_EDGE];

Color reverseColor(Color color) {
	return color == Red ? Black : Red;
}

inline int min(int x, int y) {
	return x < y ? x : y;
}

bool dfs(int vertex, Color color) {
	if (vertexColor[vertex] == color) {
		return true;
	}
	else if (vertexColor[vertex] == reverseColor(color)) {
		return false;
	}

	vertexColor[vertex] = color;
	numbers[color]++;

	for (int i = head[vertex]; i != -1;i=edges[i].next) {
		Edge& e = edges[i];
		if (vertexColor[e.end] != Color::undefined) {
			if (vertexColor[e.end] == vertexColor[vertex]) {
				return false;
			}
			else {
				continue;
			}
		}
		if (vertexColor[e.end] == Color::undefined && !dfs(e.end, reverseColor(color))) {
			return false;
		}
	}

	return true;
}

int main() {
	memset(head, 0xff, sizeof(head));
	cin >> N >> M;

	int count = 0;
	for (int i = 0; i < M;i++) {
		int start, end;
		cin >> start >> end;
		edges[count] = Edge(start, end, head[start]);
		head[start] = count;
		count++;

		edges[count] = Edge(end, start, head[end]);
		head[end] = count;
		count++;
	}


	bool OK = true;
	int answer = 0;
		
	for (int i = 1; i <= N;i++) {
		numbers[1] = numbers[2] = 0;

		if (vertexColor[i] != Color::undefined) {
			continue;
		}
		bool result = dfs(i, Color::Red);
		if (!result) {
			OK = false;
			break;
		}

		// 难点，有可能图不是联通的，所以要每次加一个最小值
		answer += min(numbers[1], numbers[2]);
	}

	if (OK) {
		cout << answer;
	}
	else {
		cout << "Impossible";
	}

	return 0;
}