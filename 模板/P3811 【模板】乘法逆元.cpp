#include<iostream>
using namespace std;

long long P = 0;
const int MAX = 3000005;
long long answer[MAX];

int main() {
	int N = 0;
	cin >> N >> P;

	answer[1] = 1;
	printf("1\n");
	for (int i = 2; i <= N;i++) {
		answer[i] = (P - P / i) * answer[P % i] % P;
		printf("%lld\n", answer[i]);
	}

	return 0;
}