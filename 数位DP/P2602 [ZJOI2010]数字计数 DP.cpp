#include <iostream>
#include <cstring>

using namespace std;

long long dp[15][10][10];
long long answer[10][2];

long long fastPow(long long base, long long pow) {
    long long result = 1, temp = base;
    while (pow) {
        if (pow & 1) {
            result *= temp;
        }

        temp *= temp;
        pow >>= 1;
    }
    return result;
}

void init() {
    for (int j = 0; j <= 9; j++) {
        dp[1][j][j] = 1;
    }

    for (int i = 2; i <= 13; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                for (int d = 0; d <= 9; d++) {
                    dp[i][j][d] += dp[i - 1][k][d];
                }
            }
            dp[i][j][j] += fastPow(10, i - 1);
        }
    }
}

void solve(long long number, int storage) {
    short digitArr[15];
    memset(digitArr, 0, sizeof(digitArr));

    int digitLength = 0;
    while (number) {
        digitArr[++digitLength] = number % 10;
        number /= 10;
    }

    for (int d = 0; d <= 9; d++) {
        for (int i = 1; i <= digitLength - 1; i++) {
            for (int j = 1; j <= 9; j++) {
                answer[d][storage] += dp[i][j][d];
            }
        }

        short highDigest = digitArr[digitLength];
        for (int i = 1; i < highDigest; i++) {
            answer[d][storage] += dp[digitLength][i][d];
        }

        for (int i = digitLength - 1; i >= 1; i--) {
            short digitNumber = digitArr[i];

            for (int j = 0; j <= digitNumber - 1; j++) {
                answer[d][storage] += dp[i][j][d];
            }
        }
    }

    for (int i = digitLength - 1; i >= 1; i--) {
        for (int k = digitLength; k > i; k--) {
            answer[digitArr[k]][storage] += fastPow(10, i - 1) * digitArr[i];
        }
    }
}

int main() {
    init();
    long long start = 0, end = 0;
    cin >> start >> end;

    solve(end + 1, 0);
    solve(start, 1);
    for (int i = 0; i <= 9; i++) {
        long long result = answer[i][0] - answer[i][1];
        cout << result << " ";
    }
    return 0;
}