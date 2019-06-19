#include<iostream>
using namespace std;

int month[] = { 0,31,0,31,30,31,30,31,31,30,31,30,31 };
int staticInfo[15];

void fillFebruary(int year) {
	if ((year % 100 == 0 && year % 400 == 0)
		|| (year % 100 && year % 4 == 0)
		) {
		month[2] = 29;
	}
	else {
		month[2] = 28;
	}
}


int main() {
	int N = 0, dayOfWeek = 0;
	cin >> N;

	for (int y = 1900; y < 1900 + N; y++) {
		fillFebruary(y);
		for (int m = 1; m <= 12;m++) {
			for (int d = 1; d <= month[m];d++) {
				dayOfWeek++;
				if (dayOfWeek >= 8) {
					dayOfWeek -= 7;
				}

				if (d == 13) {
					staticInfo[dayOfWeek] ++;
				}
			}
		}
	}

	for (int i = 6; i <= 7;i++) {
		cout << staticInfo[i] << " ";
	}
	for (int i = 1; i <= 5; i++) {
		cout << staticInfo[i] << " ";
	}
	return 0;
}