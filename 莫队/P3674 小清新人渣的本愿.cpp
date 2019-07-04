#include <iostream>
#include <cmath>
#include <algorithm>
#include <bitset>

using namespace std;

class Query {
public:
    int opt, L, R, K, index;

    Query() : opt(0), L(0), R(0), K(0), index(0) {};

    Query(int o, int l, int r, int k, int i) : opt(o), L(l), R(r), K(k), index(i) {};
};

const int MAXN = 100005;
int number[MAXN], appearCount[MAXN], blockSize, blockNumber, n, m;
bool answer[MAXN];
Query queryList[MAXN];
bitset<MAXN> s1, s2;

inline void init() {
    blockSize = sqrt(n);
    blockNumber = n / blockSize;
    if (n % blockSize) {
        blockNumber++;
    }
}

inline int belong(int index) {
    return (index - 1) / blockSize + 1;
}

inline void add(int x) {
    if (!appearCount[x]) {
        s1[x] = true;
        s2[MAXN - x] = true;
    }
    appearCount[x]++;
}

inline void del(int x) {
    appearCount[x]--;
    if (!appearCount[x]) {
        s1[x] = false;
        s2[MAXN - x] = false;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> number[i];
    }
    init();

    for (int i = 1; i <= m; i++) {
        int opt = 0, l = 0, r = 0, k = 0;
        cin >> opt >> l >> r >> k;
        queryList[i] = {opt, l, r, k, i};
    }

    sort(queryList + 1, queryList + 1 + m, [](const Query &$1, const Query &$2) -> bool {
        if (belong($1.L) == belong($2.L)) {
            return $1.R < $2.R;
        } else {
            return $1.L < $2.L;
        }
    });


    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        auto[opt, L, R, K, index] = queryList[i];
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

        if (opt == 1) {
            answer[index] = (s1 & (s1 << K)).any();
        } else if (opt == 2) {
            answer[index] = (s1 & (s2 >> (MAXN - K))).any();
        } else if (opt == 3) {
            for (int j = 1; j * j <= K; j++) {
                if (K % j == 0 && s1[j] && s1[K / j]) {
                    answer[index] = true;
                    break;
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        if (answer[i]) {
            cout << "hana" << endl;
        } else {
            cout << "bi" << endl;
        }
    }
    return 0;
}