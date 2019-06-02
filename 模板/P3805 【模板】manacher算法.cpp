#include<iostream>
#include<cstring>
using namespace std;

char oldStr[11000005], str[22000010];
int oldStrLen = 0, strLen = 0;
int dp[22000010];

inline int min(int x, int y) {
	return x < y ? x : y;
}

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline void init() {
	oldStrLen = strlen(oldStr);
	strLen = 2;
	str[0] = '$';
	str[1] = '#';
	for (int i = 0; i < oldStrLen;i++) {
		str[strLen++] = oldStr[i];
		str[strLen++] = '#';
	}
}

inline int manacher() {
	int center = 0, right = 0, result = 0;

	for (int i = 1; i <= strLen;i++) {
		int radius = 1;

		if (right >= i) {
			radius = min(dp[2 * center - i], right - i);
		}

		while (str[i + radius] == str[i - radius]) {
			radius++;
		}

		if (i + radius > right) {
			center = i;
			right = i + radius;
		}

		dp[i] = radius;
		result = max(dp[i] - 1, result);
	}
	return result;
}

int main() {
	cin >> oldStr;
	init();
	cout << manacher();

	return 0;
}