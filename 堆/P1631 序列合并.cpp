#include<iostream>
#include<queue>
using namespace std;

class Item {
public:
	int x, y, sum;
	Item() : x(0), y(0), sum(0) {};
	Item(int _x, int _y, int _sum) : x(_x), y(_y), sum(_sum) {};
	bool operator< (const Item& $2) const {
		return this->sum > $2.sum;
	}
};

int A[100005], B[100005];
priority_queue<Item> heap;

int main() {
	int N = 0;
	cin >> N;

	for (int i = 0; i < N;i++) {
		cin >> A[i];
	}

	for (int i = 0; i < N; i++) {
		cin >> B[i];
	}

	for (int i = 0; i < N;i++) {
		heap.push({ i, 0, A[i] + B[0] });
	}

	for (int i = 0; i < N; i++) {
		Item item = heap.top();
		heap.pop();

		if (item.y + 1 < N) {
			heap.push({ item.x , item.y + 1, A[item.x] + B[item.y + 1] });
		}

		cout << item.sum << " ";
	}

	return 0;
}