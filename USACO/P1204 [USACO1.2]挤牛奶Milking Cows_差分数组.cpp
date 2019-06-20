#include<iostream>
#include<algorithm>
using namespace std;

const int MAX = 5005;
int N;
pair<int, int> timetable[MAX];
int startTime = 99999999, endTime, answer[2];
int differenceArray[1000005];

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

		differenceArray[s] += 1;
		differenceArray[e] += -1;

		startTime = min(s, startTime);
		endTime = max(e, endTime);
	}

	int now = 0, tempStart = startTime;
	for (int i = startTime; i <= endTime + 1;i++) {
		differenceArray[i] += differenceArray[i - 1];
		if ((differenceArray[i] == 0 || i == endTime) && now == 1) {
			answer[1] = max(answer[1], i - tempStart);
			now = 0;
			tempStart = i;
		}
		else if ((differenceArray[i] >= 1 || i == endTime) && now == 0) {
			answer[0] = max(answer[0], i - tempStart);
			now = 1;
			tempStart = i;
		}
	}


	cout << answer[1] << " " << answer[0];

	return 0;
}