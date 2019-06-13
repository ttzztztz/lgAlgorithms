#include<iostream>
#include<algorithm>
using namespace std;

class Apple {
public:
	int height, force;
	Apple() : height(0), force(0) {};
	Apple(int h, int f) : height(h), force(f) {};
};

const int MAX = 5005;
int n, s, a, b;
Apple apples[MAX];

int main() {
	cin >> n >> s >> a >> b;
	for (int i = 0; i < n;i++) {
		int h = 0, f = 0;
		cin >> h >> f;
		apples[i] = { h, f };
	}
	
	sort(apples, apples + n, [](const Apple& $1, const Apple& $2)->bool {
		if ($1.force == $2.force) {
			return $1.height < $2.height;
		}
		else {
			return $1.force < $2.force;
		}
	});

	int i = 0, answer = 0;
	while (s && i < n) {
		const Apple& apple = apples[i];
		if (s >= apple.force && apple.height <= a + b) {
			s -= apple.force;
			answer++;
		}
		i++;
	}

	cout << answer;

	return 0;
}