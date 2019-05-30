#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 30005;
int arr[MAX];

int main() {
	int w = 0, n = 0;
	cin >> w >> n;

	for (int i = 0; i < n;i++) {
		cin >> arr[i];
	}
	sort(arr, arr + n);

	int startOffset = 0, endOffset = n - 1, result = 0;
	while (startOffset <= endOffset) {
		if (arr[startOffset] + arr[endOffset] <= w) {
			startOffset++;
			endOffset--;
			result++;
		}
		else if (arr[endOffset] <= w) {
			endOffset--;
			result++;
		}
	}
	cout << result;

	return 0;
}