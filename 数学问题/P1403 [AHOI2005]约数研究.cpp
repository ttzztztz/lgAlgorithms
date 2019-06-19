#include<iostream>
using namespace std;

// [1, n] 含有2因子的数有 n/2 个，含有3因子的数有 n/3 个……
// 含有i因子的数有n/i个
int main() {
	int n = 0, answer = 0;
	cin >> n;
	for (int i = 1; i <= n;i++) {
		answer += n / i;
	}
	cout << answer;
	
	return 0;
}