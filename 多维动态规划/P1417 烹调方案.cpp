#include<iostream>
#include<algorithm>
using namespace std;

class Food {
public:
	long long a, b, c;
	Food() :a(0), b(0), c(0) {};
	Food(int x, int y, int z) : a(x), b(y), c(z) {};
};

Food foods[55];
long long dp[100005];
int T = 0, N = 0;

inline long long max(long long x, long long y) {
	return x < y ? y : x;
}

int main() {
	cin >> T >> N;
	for (int i = 1; i <= N;i++) {
		int a = 0;
		cin >> a;
		foods[i].a = a;
	}

	for (int i = 1; i <= N; i++) {
		int b = 0;
		cin >> b;
		foods[i].b = b;
	}

	for (int i = 1; i <= N; i++) {
		int c = 0;
		cin >> c;
		foods[i].c = c;
	}
	
	sort(foods + 1, foods + 1 + N, [](const Food& $1, const Food& $2)->bool {
		return $1.b * $2.c > $1.c * $2.b;
	});

	for (int i = 1; i <= N;i++) {
		const Food& f = foods[i];
		for (int j = T; j >= 0;j--) {
			if (f.c <= j) {
				dp[j] = max(dp[j], dp[j - f.c] + (f.a - j * f.b));
			}
		}
	}

	long long result = 0;
	for (int i = 0; i <= T;i++) {
		result = max(result, dp[i]);
	}
	cout << result;
	return 0;
}