#include<iostream>
#include<map>
#include<cstring>
#include<sstream>
using namespace std;

bool checked[105][105][105];
int N, OK[3], INIT[3], answer;

int lastNumber(int x) {
	x--;
	if (x <= 0) {
		x += N;
	}
	return x;
}

int nextNumber(int x) {
	x++;
	if (x > N) {
		x -= N;
	}
	return x;
}

void check(int a, int b, int c) {
	if (!checked[a][b][c]) {
		answer++;
		checked[a][b][c] = true;
	}
}

void solve(int x, int y, int z) {
	int _x = x, _y = y, _z = z;
	for (int a = 0; a < 5;a++) {
		switch (a) {
			case 0: _x = lastNumber(x); break;
			case 1: _x = lastNumber(lastNumber(x)); break;
			case 2: _x = x; break;
			case 3: _x = nextNumber(x); break;
			case 4: _x = nextNumber(nextNumber(x)); break;
		}

		for (int b = 0; b < 5;b++) {
			switch (b) {
				case 0: _y = lastNumber(y); break;
				case 1: _y = lastNumber(lastNumber(y)); break;
				case 2: _y = y; break;
				case 3: _y = nextNumber(y); break;
				case 4: _y = nextNumber(nextNumber(y)); break;
			}

			for (int c = 0; c < 5;c++) {
				switch (c) {
					case 0: _z = lastNumber(z); break;
					case 1: _z = lastNumber(lastNumber(z)); break;
					case 2: _z = z; break;
					case 3: _z = nextNumber(z); break;
					case 4: _z = nextNumber(nextNumber(z)); break;
				}

				check(_x, _y, _z);
			}
		}
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < 3;i++) {
		cin >> OK[i];
	}
	for (int i = 0; i < 3; i++) {
		cin >> INIT[i];
	}

	solve(OK[0], OK[1], OK[2]);
	solve(INIT[0], INIT[1], INIT[2]);

	cout << answer;
	return 0;
}