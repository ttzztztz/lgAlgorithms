#include<iostream>
#include<cstring>
using namespace std;

const int MAX = 100005;
int nextVertex[MAX], DFN[MAX], COLOR[MAX], CIRCLE[MAX], INDFN[MAX];
int N;

inline int max(int x, int y) {
	return x < y ? y : x;
}

int main() {
	cin >> N;
	for (int i = 1; i <= N;i++) {
		cin >> nextVertex[i];
	}

	for (int i = 1; i <= N;i++) {
		for (int j = i, timestamp = 0;;j = nextVertex[j], timestamp++) {
			if (!COLOR[j]) {
				COLOR[j] = i;
				DFN[j] = timestamp;
			}
			else if (COLOR[j] == i) {
				CIRCLE[i] = timestamp - DFN[j];
				INDFN[i] = DFN[j];
				cout << timestamp << endl;
				break;
			}
			else if (COLOR[j] != i) {
				CIRCLE[i] = CIRCLE[COLOR[j]];
				INDFN[i] = timestamp + max(0, INDFN[COLOR[j]] - DFN[j]);
				cout << CIRCLE[i] + INDFN[i] << endl;
				break;
			}
		}
	}

	return 0;
}