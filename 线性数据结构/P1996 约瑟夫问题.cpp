#include<iostream>
using namespace std;

int visited[105];
int finished;
int N = 0, M = 0;

inline void jump(int& offset, int& count) {
	offset++;
	count++;

	if (offset > N) {
		offset = 1;
	}
}

inline void jump(int& offset) {
	offset++;

	if (offset > N) {
		offset = 1;
	}
}

int main() {
	cin >> N >> M;

	int offset = 1, count = 1;
	while (finished < N) {
		if (visited[offset]) {
			jump(offset);
			continue;
		}

		if (count == M) {
			count = 1;
			finished++;
			visited[offset] = 1;
			if (finished == N) {
				cout << offset;
			}
			else {
				cout << offset << " ";
			}
			jump(offset);
			continue;
		}

		jump(offset, count);
	}


	return 0;
}