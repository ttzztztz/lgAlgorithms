#include<iostream>
#include<algorithm>
using namespace std;

class Person {
public:
	string name;
	int id, averageScore, rateScore, paperCount, money;
	bool isAdmin, isWestern;
	Person() : name(""), id(0), averageScore(0), rateScore(0), isAdmin(false), isWestern(false), paperCount(0), money(0) {};
	Person(string n, int i, int aS, int rS, bool isA, bool isW, int paper) : name(n), id(i), averageScore(aS), rateScore(rS), isAdmin(isA), isWestern(isW), paperCount(paper), money(0) {};
};

int Yuanshi(Person& p) {
	if (p.averageScore > 80 && p.paperCount) {
		p.money += 8000;
		return 8000;
	}
	return 0;
}

int WuSi(Person& p) {
	if (p.averageScore > 85 && p.rateScore > 80) {
		p.money += 4000;
		return 4000;
	}
	return 0;
}

int YouXiu(Person& p) {
	if (p.averageScore > 90) {
		p.money += 2000;
		return 2000;
	}
	return 0;
}

int Western(Person& p) {
	if (p.averageScore > 85 && p.isWestern) {
		p.money += 1000;
		return 1000;
	}
	return 0;
}

int GongXian(Person& p) {
	if (p.rateScore > 80 && p.isAdmin) {
		p.money += 850;
		return 850;
	}
	return 0;
}

Person person[105];
int all, N;

int main() {
	cin >> N;
	for (int i = 1; i <= N;i++) {
		string name;
		int av = 0, rate = 0;
		char isGanbu = '\0', isWestern = '\0';
		int paperCount = 0;

		cin >> name >> av >> rate >> isGanbu >> isWestern >> paperCount;
		person[i] = Person(name, i, av, rate, isGanbu == 'Y', isWestern == 'Y', paperCount);

		all += Yuanshi(person[i]);
		all += WuSi(person[i]);
		all += YouXiu(person[i]);
		all += Western(person[i]);
		all += GongXian(person[i]);
	}

	sort(person + 1, person + N + 1, [](const Person& $1, const Person& $2)->bool {
		if ($1.money == $2.money) {
			return $1.id < $2.id;
		}
		else {
			return $1.money > $2.money;
		}
	});

	cout << person[1].name << endl;
	cout << person[1].money << endl;
	cout << all;

	return 0;
}