#include<iostream>
using namespace std;

const int MAX = 40005;
int prime[MAX], check[MAX], phi[MAX];

void euler() {
	phi[1] = 1;
	int maxCount = 1;
	for (int i = 2; i <= MAX;i++) {
		if (!check[i]) {
			prime[maxCount++] = i;
			phi[i] = i - 1;
		}

		for (int j = 1; j <= maxCount && i * prime[j] <= MAX;j++) {
			check[i * prime[j]] = 1;

			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
}

int main() {
	euler();
	int number = 0;
	cin >> number;

	if (number == 1) {
		cout << 0;
		return 0;
	}

	int result = 0;
	for (int i = 1; i < number;i++) {
		result += phi[i] * 2;
	}
	result += 1; // k=1
	cout << result;
	return 0;
}