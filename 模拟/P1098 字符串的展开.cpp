#include <iostream>

using namespace std;

int p1 = 0, p2 = 0, p3 = 0;

int simpleCheck(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return 1;
    } else if (ch >= '0' && ch <= '9') {
        return 2;
    } else {
        return 0;
    }
}

bool check(char before, char after) {
    int result1 = simpleCheck(before);
    int result2 = simpleCheck(after);

    return result1 && result2 && result1 == result2 && before < after;
}

bool isLowerCase(char ch) {
    return ch >= 'a' && ch <= 'z';
}

char toUpperCase(char ch) {
    return (ch - 'a') + 'A';
}

void output(char ch) {
    for (int i = 1; i <= p2; i++) {
        if (p1 == 1) {
            cout << ch;
        } else if (p1 == 2) {
            if (isLowerCase(ch)) {
                cout << toUpperCase(ch);
            } else {
                cout << ch;
            }
        } else if (p1 == 3) {
            cout << '*';
        }
    }
}

int main() {
    cin >> p1 >> p2 >> p3;
    char ch = '\0', before = '\0';
    while ((cin >> ch)) {
        if (ch != '-' || before == '\0') {
            cout << ch;
        } else if (ch == '-') {
            char next = '\0';
            cin >> next;
            if (check(before, next)) {
                if (p3 == 1) {
                    for (int i = before + 1; i < next; i++) {
                        output(i);
                    }
                } else if (p3 == 2) {
                    for (int i = next - 1; i > before; i--) {
                        output(i);
                    }
                }

                cout << next;
            } else {
                cout << ch << next;
            }
            ch = next;
        }
        before = ch;
    }
    return 0;
}