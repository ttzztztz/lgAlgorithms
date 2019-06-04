#include<iostream>
using namespace std;

const int MAX = 1000005;
int heap[MAX];
int heapLen = 0;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

void adjustHeap(int root) {
	for (int i = root; i > 0;i = (i - 1)/ 2) {
		int parent = (i - 1) / 2;
		if (heap[parent] > heap[i]) {
			swap(heap[parent], heap[i]);
		}
		else {
			break;
		}
	}
}

void delHeap(int node) {
	int minIndex = -1, leftChild = 2 * node + 1, rightChild = 2 * node + 2, minValue = 0x7fffffff;

	if (leftChild < heapLen && heap[leftChild] < heap[node]) {
		minIndex = leftChild;
		minValue = heap[leftChild];
	}

	if (rightChild < heapLen && heap[rightChild] < heap[node] && heap[rightChild] < heap[leftChild]) {
		minIndex = rightChild;
		minValue = heap[rightChild];
	}

	if (minIndex != -1) {
		swap(heap[node], heap[minIndex]);
		delHeap(minIndex);
	}
}

int main() {
	int N = 0;
	cin >> N;
	for (int i = 0; i < N;i++) {
		int opt = 0;
		cin >> opt;
		if (opt == 1) {
			int x = 0;
			cin >> x;
			heap[heapLen] = x;
			adjustHeap(heapLen);
			heapLen++;
		}
		else if (opt == 2) {
			cout << heap[0] << endl;
		}
		else if (opt == 3) {
			heapLen--;
			swap(heap[0], heap[heapLen]);
			delHeap(0);
		}
	}

	return 0;
}