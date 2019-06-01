#include<iostream>
using namespace std;

int n, m;
int result;

inline int nextPerson(int x) {
	if (x + 1 > n) {
		return 1;
	}
	else {
		return x + 1;
	}
}

inline int lastPerson(int x) {
	if (x - 1 >= 1) {
		return x - 1;
	}
	else {
		return n;
	}
}

void pushBall(int now, int count) {
	if (count >= m) {
		if (now == 1) {
			result++;
		}
		return;
	}

	pushBall(nextPerson(now), count + 1);
	pushBall(lastPerson(now), count + 1);
}

int main() {
	cin >> n >> m;

	pushBall(1, 0);

	cout << result;
	return 0;
}