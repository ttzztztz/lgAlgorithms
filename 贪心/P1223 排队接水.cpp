#include<iostream>
#include<algorithm>
using namespace std;

class Item {
public:
	int id, time;
	Item() : id(0), time(0) {};
	Item(int i, int t) : id(i), time(t) {};
};

const int MAX = 1005;
Item arr[MAX];

int main() {
	int N = 0;
	double totalTime = 0.0;
	cin >> N;

	for (int i = 1; i <= N;i++) {
		int time = 0;
		cin >> time;
		arr[i - 1] = Item(i, time);
	}

	sort(arr, arr + N, [](const Item& $1, const Item& $2)->bool {
		return $1.time < $2.time;
	});

	for (int i = 0; i < N;i++) {
		Item& item = arr[i];
		totalTime += item.time * (N - i - 1);
		cout << item.id;
		if (i != N - 1) {
			cout << " ";
		}
	}

	cout << endl;
	printf("%.2f", totalTime / N);
	return 0;
}