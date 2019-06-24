#include<iostream>
#include<cstring>

const int MAX = 1000005;
char P[MAX], T[MAX];
int next[MAX], lenT, lenP;

void build() {
	next[0] = -1;
	next[1] = 0;

	int j = 0, i = 1;
	while (i < lenP) {
		if (j == -1 || P[i] == P[j]) {
			next[++i] = ++j;
		}
		else {
			j = next[j];
		}
	}
}

void kmp() {
	int i = 0, j = 0;

	while (i < lenT) {
		if (j == -1 || T[i] == P[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}

		if (j == lenP) {
			std::cout << (i - j + 1) << std::endl;
			j = next[j];
		}
	}
}

int main() {
	std::cin >> T >> P;
	lenT = strlen(T);
	lenP = strlen(P);
	build();
	kmp();

	for (int i = 1; i <= lenP;i++) {
		std::cout << next[i] << " ";
	}
	return 0;
}