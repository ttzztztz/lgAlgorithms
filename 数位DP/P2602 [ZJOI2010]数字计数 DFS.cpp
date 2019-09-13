#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 15;
long long dp[MAX][2][MAX][2];
short digestArr[MAX];
int digestLength = 0;

long long dfs(int length, int isSmall, int sum, int isZero, int d) {
    if (length == 0) {
        return sum;
    }
    if (dp[length][isSmall][sum][isZero] != -1) {
        return dp[length][isSmall][sum][isZero];
    }

    long long answer = 0;
    for (int i = 0; i <= 9; i++) {
        if (!isSmall && i > digestArr[length]) {
            break;
        }

        answer += dfs(length - 1,
                      isSmall || (digestArr[length] > i),
                      sum + ((i == d) && (i || !isZero)),
                      isZero && (i == 0),
                      d);
    }

    return dp[length][isSmall][sum][isZero] = answer;
}

long long solve(long long number, int d) {
    memset(dp, 0xff, sizeof(dp));
    memset(digestArr, 0, sizeof(digestArr));
    digestLength = 0;

    while (number) {
        digestArr[++digestLength] = number % 10;
        number /= 10;
    }

    return dfs(digestLength, 0, 0, 1, d);
}

int main() {
    long long start = 0, end = 0;
    cin >> start >> end;
    for (int i = 0; i <= 9; i++) {
        cout << (solve(end, i) - solve(start - 1, i)) << " ";
    }
    return 0;
}