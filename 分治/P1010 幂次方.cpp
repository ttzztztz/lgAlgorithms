#include<iostream>
using namespace std;

int pow2[] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768 };
int len = sizeof(pow2) / sizeof(int);

void split(int x) {
	if (x == 2) {
		cout << "2";
		return;
	}
	else if (x == 1) {
		cout << "2(0)";
		return;
	}
	else if (x == 3) {
		cout << "2+2(0)";
		return;
	}
	else if (x == 0) {
		return;
	}

	int key = 0;

	for (int i = len; i >= 0;i--) {
		key = pow2[i];
		if (key > x) {
			continue;
		}

		if (x & key) {
			if (i >= 2) {
				cout << "2(";
			}
			split(i);
			if (i >=2) {
				cout << ")";
			}
			break;
		}
	}

	if (x - key) {
		cout << "+";
		split(x - key);
	}
}

int main() {
	int N = 0;
	cin >> N;
	split(N);

	return 0;
}