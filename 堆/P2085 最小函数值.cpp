#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int MAX = 10005;
vector<int> result;

int main() {
	int N = 0, M = 0;
	cin >> N >> M;

	result.resize(M);
	fill(result.begin(), result.end(), 99999999);

	for (int i = 0; i < N; i++) {
		int A = 0, B = 0, C = 0;
		cin >> A >> B >> C;

		for (int x = 1; x <= M;x++) {
			int number = A * x * x + B * x + C;
			if (number > result.back()) {
				break;
			}
			else {
				auto it = upper_bound(result.begin(), result.end(), number);
				result.insert(it++, number);
				result.resize(M);
			}

		}
	}

	sort(result.begin(), result.end(), less<int>());
	for (int i = 0; i < M; i++) {
		cout << result[i] << " ";
	}

	return 0;
}