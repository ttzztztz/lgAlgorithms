#include<iostream>
using namespace std;

long long lowbit(long long x) {
	return x & (-x);
}

long long calcNum(long long n) {
	long long result = 0;
	while (n) {
		result++;
		n -= lowbit(n);
	}
	return result;
}

int main() {
	long long n = 0, k = 0;
	cin >> n >> k;
	
	long long answer = 0;
	while (calcNum(n) > k) {
		answer += lowbit(n);
		n += lowbit(n);
	}
	cout << answer;
	return 0;
}