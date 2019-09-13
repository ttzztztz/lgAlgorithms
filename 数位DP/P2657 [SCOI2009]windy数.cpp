#include <iostream>
#include <cstring>

using namespace std;

long long dp[15][10];

void init() {
    for (int i = 0; i <= 9; i++) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= 15; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                if (abs(j - k) >= 2) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }
}

long long solve(int x) {
    long long answer = 0;
    short digitArr[15];
    memset(digitArr, 0, sizeof(digitArr));

    int digitLen = 0;
    while (x) {
        digitArr[++digitLen] = x % 10;
        x /= 10;
    }

    for (int i = 1; i <= digitLen - 1; i++) {
        for (int j = 1; j <= 9; j++) {
            answer += dp[i][j];
        }
    }

    int highDigest = digitArr[digitLen];
    for (int i = 1; i < highDigest; i++) {
        answer += dp[digitLen][i];
    }

    for (int i = digitLen - 1; i >= 1; i--) {
        int digitNumber = digitArr[i];
        int highDigitNumber = digitArr[i + 1];

        for (int j = 0; j <= digitNumber - 1; j++) {
            if (abs(j - highDigitNumber) >= 2) {
                answer += dp[i][j];
            }
        }

        if (abs(digitArr[i + 1] - digitArr[i]) < 2) {
            break;
        }
    }

    return answer;
}

int main() {
    init();
    int start = 0, end = 0;
    cin >> start >> end;
    cout << solve(end + 1) - solve(start);

    return 0;
}