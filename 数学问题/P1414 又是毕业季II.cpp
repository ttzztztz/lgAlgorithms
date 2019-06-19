#include<iostream>
#include<cmath>
using namespace std;

const int MAX = 1000005;
int factorCount[MAX], N;

int max(int x, int y) {
	return x < y ? y : x;
}

int main() {
	int maxNumber = 0;

	cin >> N;
	for (int i = 1; i <= N;i++) {
		int number = 0;
		cin >> number;
		maxNumber = max(maxNumber, number);

		for (int j = 1; j <= sqrt(number);j++) {
			if (!(number % j)) {
				factorCount[j]++;
				if (j * j != number) {
					factorCount[number / j]++;
				}
			}
		}
	}


	for (int i = 1; i <= N;i++) {
		while (factorCount[maxNumber] < i) {
			maxNumber--;
		}
		cout << maxNumber << endl;
	}

	return 0;
}