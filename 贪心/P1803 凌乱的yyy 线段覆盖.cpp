#include<iostream>
#include<algorithm>
using namespace std;

class Competition {
public:
	int start, end;
	Competition(): start(0), end(0){};
	Competition(int s, int e) : start(s), end(e) {};
};

Competition competition[1000005];

int main() {
	int N = 0;
	cin >> N;
	for (int i = 0; i < N;i++) {
		int start = 0, end = 0;
		cin >> start >> end;
		competition[i] = { start,end };
	}

	sort(competition, competition + N, [](const Competition& $1, const Competition& $2)->bool{
		return $1.end < $2.end;
	});


	int result = 0;
	int lastEnd = 0;
	for (int i = 0; i < N;i++) {
		Competition& c = competition[i];
		if (c.start >= lastEnd) {
			result++;
			lastEnd = c.end;
		}
	}
	cout << result;
	return 0;
}