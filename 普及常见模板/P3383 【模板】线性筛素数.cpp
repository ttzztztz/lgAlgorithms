#include<iostream>
using namespace std;
int prime[10000005];
int check[10000005];
int N = 0, M = 0;

int main() {
	cin >> N >> M;

	int pos = 0;

	check[0] = check[1] = 0;
	for (int i = 2; i <= N;i++) {
		if (!check[i]) {
			prime[pos++] = i;
		}

		for (int j = 0; j < pos && i * prime[j] <= N;j++) {
			check[i * prime[j]] = 1;

			if (i % prime[j] == 0) {
				break;
			}
		}
	}

	for (int i = 0; i < M;i++) {
		int number = 0;
		cin >> number;

		if (!check[number] && number >= 2) {
			cout << "Yes";
		}
		else {
			cout << "No";
		}

		if (i != M - 1) {
			cout << endl;
		}
	}
	return 0;
}