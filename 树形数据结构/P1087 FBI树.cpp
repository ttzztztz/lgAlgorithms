#include<iostream>
using namespace std;

char list[1050];
int N;

enum Type {
	F, B, I
};

Type defineType(int start, int end) {
	bool have0 = false, have1 = false;
	while (start <= end) {
		if (have0 && have1) {
			break;
		}

		if (list[start] == 1 + '0') {
			have1 = true;
		}
		else if (list[start] == 0 + '0') {
			have0 = true;
		}

		start++;
	}

	if (have0 && have1) {
		return F;
	}
	else if (have0 && !have1) {
		return B;
	}
	else {
		return I;
	}
}

void makeTree(int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		makeTree(start, mid);
		makeTree(mid + 1, end);
	}

	Type result = defineType(start, end);
	if (result == Type::F) {
		cout << "F";
	}
	else if (result == Type::B) {
		cout << "B";
	}
	else {
		cout << "I";
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < (1 << N);i++) {
		cin>>list[i];
	}
	
	makeTree(0, (1 << N) - 1);

	return 0;
}