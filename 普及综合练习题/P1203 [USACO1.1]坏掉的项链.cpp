#include<iostream>
#include<cstring>
using namespace std;

int N, answer;
string s;
const char WHITE = 'w';

int max(int x, int y) {
	return x < y ? y : x;
}

int min(int x, int y) {
	return x < y ? x : y;
}

int main() {
	cin >> N >> s;
	s += s;

	for (int i = 1; i < s.length();i++) {
		int l = 0, r = 0;
		char c1 = s[i - 1], c2 = s[i];

		if (c1 == WHITE) {
			c1 = 'r';
			int offsetL = i - 1, _l = 0;
			while (offsetL >= 0 && (s[offsetL] == c1 || s[offsetL] == WHITE)) {
				_l++;
				offsetL--;
			}
			c1 = 'b';
			l = max(l, _l);
			offsetL = i - 1, _l = 0;
			while (offsetL >= 0 && (s[offsetL] == c1 || s[offsetL] == WHITE)) {
				_l++;
				offsetL--;
			}
			l = max(l, _l);
		}
		else {
			int offsetL = i - 1;
			while (offsetL >= 0 && (s[offsetL] == c1 || s[offsetL] == WHITE)) {
				l++;
				offsetL--;
			}
		}

		if (c2 == WHITE) {
			c2 = 'r';

			int offsetR = i, _r = 0;
			while (offsetR < s.length() && (s[offsetR] == c2 || s[offsetR] == WHITE)) {
				_r++;
				offsetR++;
			}

			r = max(r, _r);
			c2 = 'b';
			offsetR = i, _r = 0;
			while (offsetR < s.length() && (s[offsetR] == c2 || s[offsetR] == WHITE)) {
				_r++;
				offsetR++;
			}
			r = max(r, _r);
		}
		else {
			int offsetR = i;
			while (offsetR < s.length() && (s[offsetR] == c2 || s[offsetR] == WHITE)) {
				r++;
				offsetR++;
			}
		}
		
		answer = max(answer, l + r);
		answer = min(answer, N);
	}

	cout << answer;
	return 0;
}