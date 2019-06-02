#include<iostream>
#include<algorithm>
using namespace std;

class Person {
public:
	int id, weight;
	Person() : id(0), weight(0) {};
	Person(int i, int w) : id(i), weight(w) {};
};

int N, K;
int E[12];
Person person[20005];

int main() {
	cin >> N >> K;
	for (int i = 1; i <= 10;i++) {
		cin >> E[i];
	}
	for (int i = 1; i <= N;i++) {
		int weight = 0;
		cin >> weight;
		person[i] = {i, weight};
	}

	sort(person + 1, person + 1 + N, [](const Person& $1, const Person& $2)->bool {
		if ($1.weight == $2.weight) {
			return $1.id < $2.id;
		}
		else {
			return $1.weight > $2.weight;
		}
	});

	for (int i = 1; i <= N;i++) {
		int type = (i - 1) % 10 + 1;
		person[i].weight += E[type];
	}

	sort(person + 1, person + 1 + N, [](const Person& $1, const Person& $2)->bool {
		if ($1.weight == $2.weight) {
			return $1.id < $2.id;
		}
		else {
			return $1.weight > $2.weight;
		}
	});

	for (int i = 1; i <= K;i++) {
		cout << person[i].id << " ";
	}
	return 0;
}