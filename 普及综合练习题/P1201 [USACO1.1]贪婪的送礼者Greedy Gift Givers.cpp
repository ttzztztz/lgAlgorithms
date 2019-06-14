#include<iostream>
#include<map>
#include<cstring>
using namespace std;

class People {
public:
	string name;
	int send, receive, result;
	People() : name(""), send(0), receive(0), result(0) {};
	People(string s, int _s, int r) :
		name(s), send(_s), receive(r), result(0) {};
};

const int MAX = 15;
People people[MAX];
int N;
map<string, People*> reflection;

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		string name;
		cin >> name;
		people[i].name = name;
		reflection[name] = people + i;
	}

	string name;
	while (cin >> name) {
		People* p = reflection[name];
		int totalSendNumber = 0, totalSend = 0;
		cin >> totalSendNumber >> totalSend;
		if (totalSend != 0) {
			int perMoney = totalSendNumber / totalSend;
			p->receive += totalSendNumber - (perMoney * totalSend);
			p->send += totalSendNumber;
			for (int i = 0; i < totalSend; i++) {
				string sendName;
				cin >> sendName;
				reflection[sendName]->receive += perMoney;
			}
		}
	}

	for (int i = 0; i < N;i++) {
		People p = people[i];
		cout << p.name << " " << (p.receive - p.send) << endl;
	}
	return 0;
}