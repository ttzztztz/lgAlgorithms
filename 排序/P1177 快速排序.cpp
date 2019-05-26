#include<iostream>
using namespace std;
int numbers[100000];

void quickSort(int start, int end) {
	if (end - start <= 0) {
		return;
	}
	int i = start, j = end;
	int key = numbers[start];
	while (i < j) {
		while (i < j && key <= numbers[j]) {
			j--;
		}
		if (i < j) {
			numbers[i] = numbers[j];
			i++;
		}
		while (i < j && numbers[i] < key) {
			i++;
		}
		if (i < j) {
			numbers[j] = numbers[i];
			j--;
		}
	}

	if (i == j) {
		numbers[i] = key;
		quickSort(start, i - 1);
		quickSort(i + 1, end);
	}
}

int main() {
	ios::sync_with_stdio(false);
	int N = 0;
	cin >> N;
	for (int i = 0; i < N;i++) {
		cin >> numbers[i];
	}

	quickSort(0, N - 1);

	for (int i = 0; i < N;i++) {
		if (i != N - 1) {
			cout << numbers[i] << " ";
		}
		else {
			cout << numbers[i] << endl;
		}
	}
	return 0;
}