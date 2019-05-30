#include<iostream>
#include<queue>
using namespace std;

class Farmer {
public:
	int number, cost;
	Farmer() : number(0), cost(0) {};
	Farmer(int n, int c) : number(n), cost(c) {};
	bool operator< (const Farmer& f) const{
		return this->cost > f.cost;
	};
};

int main() {
	int N = 0, M = 0;
	cin >> N >> M;

	priority_queue<Farmer> queue;

	for (int i = 0; i < M;i++) {
		int number = 0, cost = 0;
		cin >> cost >> number;
		queue.push(Farmer(number, cost));
	}

	int allCost = 0;
	while (N > 0 && queue.size()) {
		Farmer f = queue.top();
		queue.pop();

		if (f.number >= N) {
			allCost += f.cost * N;
		}
		else {// f.number < N
			allCost += f.cost * f.number;
		}
		N -= f.number;
	}

	cout << allCost;
	return 0;
}