#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 5005;
int N, answer[2];
pair<int, int> timetable[MAX];

int min(int x, int y) {
	return x < y ? x : y;
}

int max(int x, int y) {
	return x < y ? y : x;
}

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		int s = 0, e = 0;
		cin >> s >> e;
		timetable[i] = { s, e };
	}

	sort(timetable, timetable + N, 
		[](const pair<int, int>& $1, const pair<int, int>& $2)->bool {
			return $1.first < $2.first;
		}
	);
	
	int startTime = timetable[0].first, endTime = timetable[0].second;

	for (int i = 1; i < N; i++) {
		const pair<int, int>& curr = timetable[i];
		if (curr.first <= endTime) {
			endTime = max(endTime, curr.second);
		}
		else {
			answer[0] = max(answer[0], endTime - startTime);
			answer[1] = max(answer[1], curr.first - endTime);

			startTime = curr.first;
			endTime = curr.second;
		}
	}

	answer[0] = max(answer[0], endTime - startTime);

	cout << answer[0] << " " << answer[1];
	return 0;
}