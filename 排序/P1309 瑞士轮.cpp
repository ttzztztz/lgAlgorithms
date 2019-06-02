#include<iostream>
#include<algorithm>
using namespace std;

class Person {
public:
	int id, score, ability;
	Person() : id(0), score(0), ability(0) {};
	Person(int i, int s, int a) : id(i), score(s), ability(a) {};
};

int N, R, Q;
Person person[200005];
Person win[100005], fail[100005];

int main() {
	cin >> N >> R >> Q;
	N *= 2;

	for (int i = 1; i <= N;i++) {
		person[i].id = i;
		cin >> person[i].score;
	}
	for (int i = 1; i <= N;i++) {
		cin >> person[i].ability;
	}

	auto comp = [](const Person& $1, const Person& $2)->bool {
		if ($1.score == $2.score) {
			return $1.id < $2.id;
		}
		else {
			return $1.score > $2.score;
		}
	};
	sort(person + 1, person + 1 + N, comp);

	for (int i = 1; i <= R;i++) {
		int winCount = 0, failCount = 0;

		for (int i = 1; i <= N; i += 2) {
			int firstId = i, secondId = i + 1;
			if (person[firstId].ability > person[secondId].ability) {
				person[firstId].score++;
				win[winCount++] = person[firstId];
				fail[failCount++] = person[secondId];
			}
			else {
				person[secondId].score++;
				win[winCount++] = person[secondId];
				fail[failCount++] = person[firstId];
			}
		}

		int offsetWin = 0, offsetFail = 0;
		while (offsetWin < winCount && offsetFail < failCount) {
			if (comp(win[offsetWin], fail[offsetFail])) {
				person[offsetWin + offsetFail + 1] = win[offsetWin];
				offsetWin++;
			}
			else {
				person[offsetWin + offsetFail + 1] = fail[offsetFail];
				offsetFail++;
			}
		}
		while (offsetWin < winCount) {
			person[offsetWin + offsetFail + 1] = win[offsetWin];
			offsetWin++;
		}
		while (offsetFail < failCount) {
			person[offsetWin + offsetFail + 1] = fail[offsetFail];
			offsetFail++;
		}

	}

	cout << person[Q].id;

	return 0;
}