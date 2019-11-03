#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N = 0, answer = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int number = 0;
        cin >> number;
        if (number < 0) {
            number = -number;
        }

        if (i == 0) {
            answer = number;
        } else {
            answer = __gcd(answer, number);
        }
    }

    cout << answer;
    return 0;
}