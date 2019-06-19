#include<iostream>
using namespace std;
int N = 0;

int main() {
	cin >> N;

	int i = 1, j = 2, sum = 3;
	while (j < N) {
		if (sum < N) {
			j++;
			sum += j;
		}
		else if (sum > N) {
			sum -= i;
			i++;
		}
		else if (sum == N) {
			cout << i << " " << j << endl;
			sum -= i;
			i++;
			j++;
			sum += j;
		}
	}

	return 0;
}