#include<iostream>
#include<algorithm>
using namespace std;

int arr[120];

int main() {
	ios::sync_with_stdio(false);

	int N = 0;
	cin >> N;
	for (int i = 0; i < N;i++) {
		cin >> arr[i];
	}

	sort(arr, arr + N);
	int* end = unique(arr, arr + N);
	int total = end - arr;
	cout << total << endl;

	for (int i = 0; i < total;i++) {
		if (i == total - 1) {
			cout << arr[i];
		}
		else {
			cout << arr[i] << " ";
		}
	}

	return 0;
}