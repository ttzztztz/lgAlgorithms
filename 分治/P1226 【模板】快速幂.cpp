#include<iostream>
#include<cstdio>
using namespace std;

int main() {
	long long b = 0, p = 0, k = 0;
	cin >> b >> p >> k;
	long long rawP = p;

	if (p == 0) {
		printf("%lld^%lld mod %lld=%lld", b, rawP, k, 1 % k);
		return 0;
	}

	long long result = 1;
	long long pow = b % k;
	while (p) {
		if (p & 1) {
			result = (result * pow) % k;
		}
		pow = (pow * pow) % k;
		p >>= 1;
	}


	printf("%lld^%lld mod %lld=%lld", b, rawP, k, result);

	return 0;
}