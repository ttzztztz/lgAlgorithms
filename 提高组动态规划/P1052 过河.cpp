#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 1000005;
int dp[MAX], stone[MAX], stone_new[MAX];
bool have_stone[MAX];
int S, T, L;

inline int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    int M = 0;
    cin >> L >> S >> T >> M;

    for (int i = 1; i <= M; i++) {
        cin >> stone[i];
    }

    if (S == T) {
        int count = 0;
        for (int i = 1; i <= M; i++) {
            if (stone[i] % S == 0) {
                count++;
            }
        }
        cout << count;
    } else {
        sort(stone + 1, stone + 1 + M);

        for (int i = 1; i <= M; i++) {
            int delta = stone[i] - stone[i - 1];
            if (delta >= S * T) {
                delta = S * T;
            }
            stone_new[i] = stone_new[i - 1] + delta;
            have_stone[stone_new[i]] = true;
        }

        L = stone_new[M] + S * T;

        memset(dp, 0x7f, sizeof(dp));
        dp[0] = 0;

        for (int i = 1; i <= L; i++) {
            for (int j = S; j <= T; j++) {
                if (i - j >= 0) {
                    if (have_stone[i]) {
                        dp[i] = min(dp[i - j] + 1, dp[i]);
                    } else {
                        dp[i] = min(dp[i - j], dp[i]);
                    }
                }
            }
        }

        int answer = 0x7fffffff;
        for (int i = stone_new[M]; i <= L; i++) {
            answer = min(answer, dp[i]);
        }
        cout << answer;
    }
    return 0;
}