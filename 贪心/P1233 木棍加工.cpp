#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Stuff {
public:
	int l, w;
	Stuff() :l(0), w(0) {};
	Stuff(int _l, int _w) : l(_l), w(_w) {};
};

const int MAX = 5005;
Stuff stuff[MAX];
int N;

inline int max(int x, int y) {
	return x < y ? y : x;
}

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		int l = 0, w = 0;
		cin >> l >> w;
		stuff[i] = { l,w };
	}

	sort(stuff, stuff + N, [](const Stuff& $1, const Stuff& $2)->bool{
		return $1.l > $2.l;
	});

	vector<int> stack;
	stack.push_back(stuff[0].w);

	for (int i= 1; i < N;i++) {
		if (stuff[i].w > stack.back()) {
			stack.push_back(stuff[i].w);
		}
		else {
			auto it = lower_bound(stack.begin(), stack.end(), stuff[i].w);
			*it = stuff[i].w;
		}
	}

	cout << stack.size();

	return 0;
}