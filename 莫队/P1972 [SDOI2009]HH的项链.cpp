#pragma GCC optimize(3, "Ofast", "inline")

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

class Query {
public:
    int L, R, index;

    Query() : L(0), R(0), index(0) {};

    Query(int l, int r, int i) : L(l), R(r), index(i) {};
};

const int MAXN = 1000005, MAX = 500005;
Query queryList[MAX];
int number[MAX], N = 0, M = 0, blockSize, blockNumber, answer[MAX], appearCount[MAXN], block[MAX];

inline int read() {
    int x = 0, f = 1;
    char s = getchar();
    for (; s > '9' || s < '0'; s = getchar()) if (s == '-') f = -1;
    for (; s >= '0' && s <= '9'; s = getchar()) x = x * 10 + s - '0';
    return x * f;
}

inline void output(int x) {
    if (x >= 10) output(x / 10);
    putchar(x % 10 + '0');
}

inline void init() {
    blockSize = N >= 100000 ? 1800 : sqrt(N);
    blockNumber = N / blockSize;
    if (N % blockSize) {
        blockNumber++;
    }
    for (int i = 1; i <= M; i++) {
        block[i] = (queryList[i].L - 1) / blockSize + 1;
    }
}

int l = 1, r = 0, result = 0;

inline void add(int x) {
    if (!appearCount[x]) {
        result++;
    }
    appearCount[x]++;
}

inline void del(int x) {
    if (appearCount[x] == 1) {
        result--;
    }
    appearCount[x]--;
}

int main() {
    N = read();
    for (int i = 1; i <= N; i++) {
        number[i] = read();
    }
    M = read();
    for (int i = 1; i <= M; i++) {
        int l = 0, r = 0;
        l = read();
        r = read();
        queryList[i] = {l, r, i};
    }

    init();
    sort(queryList + 1, queryList + 1 + M, [](const Query &$1, const Query &$2) -> bool {
        if (block[$1.index] == block[$2.index]) {
            if (block[$1.index] & 1) {
                return $1.R < $2.R;
            } else {
                return $1.R > $2.R;
            }
        } else {
            return $1.L < $2.L;
        }
    });
    for (int i = 1; i <= M; i++) {
        auto[L, R, index] = queryList[i];
        while (l < L) {
            del(number[l]);
            l++;
        }
        while (l > L) {
            l--;
            add(number[l]);
        }
        while (r < R) {
            r++;
            add(number[r]);
        }
        while (r > R) {
            del(number[r]);
            r--;
        }
        answer[index] = result;
    }
    for (int i = 1; i <= M; i++) {
        output(answer[i]);
        puts("");
    }
    return 0;
}