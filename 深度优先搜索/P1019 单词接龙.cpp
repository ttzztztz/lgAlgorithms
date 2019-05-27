#include<iostream>
#include<algorithm>
using namespace std;

int N, connect[20][20];
char last;
string str[25];
int visited[25];

inline bool valid(int ptr1, int len1) {
	return ptr1 >= 0 && ptr1 < len1;
}

inline int calcConnect(int s1, int s2) {
	string& str2 = str[s2];
	return str2.length() - connect[s1][s2];
}

inline int min(int a, int b) {
	return a < b ? a : b;
}

void prepare() {
	for (int i = 0; i < N; i++) {
		for (int m = 0; m < N; m++) {
			string& str1 = str[i], & str2 = str[m];
			int len1 = str1.length(), len2 = str2.length();
			int minLen = min(len1, len2);

			for (int q = 1; q <= minLen; q++) {
				bool OK = true;

				for (int p = q - 1, s = 0; p >= 0; p--, s++) {
					int offset1 = len1 - p - 1, offset2 = s;
					if (str1[offset1] != str2[offset2]) {
						OK = false;
						break;
					}
				}

				if (OK) {
					connect[i][m] = q;
					break;
				}
			}
		}
	}
}

int answer = 0, tempAnswer = 0;

void dfs(int u) {
	bool findPath = false;
	for (int v = 0; v < N; v++) {
		if (connect[u][v] == str[u].length() || connect[u][v] == str[v].length()) {
			continue;
		}
		if (!connect[u][v]) {
			continue;
		}

		if (visited[v] < 2) {
			findPath = true;
			tempAnswer += calcConnect(u, v);
			visited[v]++;
			dfs(v);
			visited[v]--;
			tempAnswer -= calcConnect(u, v);
		}
	}

	if (!findPath) {
		answer = max(answer, tempAnswer);
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> str[i];
	}
	cin >> last;

	prepare();

	for (int i = 0; i < N; i++) {
		if (str[i][0] == last) {
			visited[i]++;
			tempAnswer = str[i].length();
			dfs(i);
			visited[i]--;
		}
	}

	cout << answer;

	return 0;
}