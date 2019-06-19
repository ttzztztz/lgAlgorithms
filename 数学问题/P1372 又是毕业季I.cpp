#include<iostream>
using namespace std;

// gcd(a, b)，当且仅当a = kb (k为整数)时，最大公因数是a，其余情况均同时小于a、b
// x 2x 3x ... kx <= n
// x=[n/k]

int main() {
	long long n = 0, k = 0;
	cin >> n >> k;
	cout << n / k;
	return 0;
}