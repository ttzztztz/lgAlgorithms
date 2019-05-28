#include<cstdio>
using namespace std;

int arr[200005];
int N;

inline int getCrossSubArraySum(int start, int end) {
	int middle = (start + end) / 2;

	int maxLeftSum = arr[middle], maxRightSum = arr[middle + 1];
	int leftSum = 0, rightSum = 0;

	for (int i = middle; i >= start;i--) {
		int number = arr[i];
		leftSum += number;
		if (leftSum > maxLeftSum) {
			maxLeftSum = leftSum;
		}
	}

	for (int i = middle + 1; i <= end;i++) {
		int number = arr[i];
		rightSum += number;
		if (rightSum > maxRightSum) {
			maxRightSum = rightSum;
		}
		
	}

	return maxLeftSum + maxRightSum;
}

int getMaxSubArraySum(int start, int end) {
	if (start == end) {
		return arr[start];
	}
	
	int middle = (start + end) / 2;

	int result1 = getMaxSubArraySum(start, middle);
	int result2 = getMaxSubArraySum(middle + 1, end);
	int result3 = getCrossSubArraySum(start, end);

	if (result1 > result2 && result1 > result3) {
		return result1;
	}
	else if (result2 > result1 && result2 > result3) {
		return result2;
	}
	else {
		return result3;
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N;i++) {
		scanf("%d", &arr[i]);
	}

	int result = getMaxSubArraySum(0, N - 1);
	printf("%d", result);
	return 0;
}