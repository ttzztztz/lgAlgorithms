#include<iostream>
#include<algorithm>
using namespace std;

int n, m;
const int MAX = 1000006;
int prime[MAX], check[MAX];

inline void prepare() {
	int pos = 0;
	for (int i = 2; i <= m;i++) {
		if (!check[i]) {
			prime[pos++] = i;
		}

		for (int j = 0; j < pos && i * prime[j] <= m;j++) {
			check[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				break;
			}
		}
	}
}

int main() {
	cin >> n >> m;
	prepare();

	for (int i = 0; i < n;i++) {
		int start = 0, end = 0;
		cin >> start >> end;
		if (start < 1 || end > m) {
			cout << "Crossing the line" << endl;
		}
		else {
			int count = 0;
			if (start < 2) {
				start = 2;
			}
			for (int i = start; i <= end;i++) {
				if (!check[i]) {
					count++;
				}
			}
			cout << count << endl;
		}
	}
	return 0;
}