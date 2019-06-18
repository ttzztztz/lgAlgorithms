#include<iostream>
using namespace std;

const int MAX = 500005;
int arr[MAX];

int main() {
	int N = 0, k = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		k ^= arr[i];
	}
	if (k) {
		int takeIndex = -1, takeCount = 0;

		for (int i = 0; i < N;i++) {
			if (arr[i] - (arr[i] ^ k) > 0) {
				cout << (arr[i] - (arr[i] ^ k)) << " " << (i + 1) << endl;

				takeIndex = i;
				takeCount = arr[i] - (arr[i] ^ k);
				break;
			}
		}

		for (int i = 0; i < N;i++) {
			if (i == takeIndex) {
				cout << (arr[i] - takeCount) << " ";
			}
			else {
				cout << arr[i] << " ";
			}
		}

	}
	else {
		cout << "lose" << endl;
	}
	return 0;
}