#include<iostream>
#include<set>
using namespace std;

class Appointment {
public:
	int start, end;
	Appointment() : start(0), end(0) {};
	Appointment(int s, int e) : start(s), end(e) {};
	bool operator< (const Appointment& $1) const{
		return this->end < $1.start;
	}
};

set<Appointment> appointSet;
int N;

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		char opt = '\0';
		cin >> opt;
		if (opt == 'A') {
			int start = 0, end = 0;
			cin >> start >> end;
			int cancelledCount = 0;

			Appointment app = {start, end};
			auto it = appointSet.find(app);
			while (it != appointSet.end()) {
				cancelledCount++;
				appointSet.erase(it);
				it = appointSet.find(app);
			}
			appointSet.insert(app);

			cout << cancelledCount << endl;
		}
		else if (opt == 'B') {
			cout << appointSet.size() << endl;
		}
	}

	return 0;
}