#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Query {
public:
    int L, R, index;

    Query() : L(0), R(0), index(0) {};

    Query(int l, int r, int i) : L(l), R(r), index(i) {};
};

const int MAX = 50005;
int N, M, K, blockNumber, blockSize;
long long number[MAX], answer[MAX], sum[MAX];
Query queryList[MAX];

void init() {
    blockSize = sqrt(N);
    blockNumber = N / blockSize;
    if (N % blockSize) {
        blockNumber++;
    }
}

int belong(int index) {
    return (index - 1) / blockSize + 1;
}

int main() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        cin >> number[i];
    }
    int queryCount = 0;
    for (int i = 0; i < M; i++) {
        int l = 0, r = 0;
        cin >> l >> r;
        queryList[queryCount++] = {l, r, i};
    }
    init();

    sort(queryList, queryList + queryCount, [](const Query &$1, const Query &$2) -> bool {
        if (belong($1.L) == belong($2.L)) {
            return $1.R < $2.R;
        } else {
            return $1.L < $2.L;
        }
    });

    int temp = 0, l = 1, r = 0;
    for (int i = 0; i < M; i++) {
        auto[L, R, index] = queryList[i];

        while (l < L) {
            sum[number[l]]--;
            temp -= 2 * sum[number[l]] + 1;
            l++;
        }
        while (l > L) {
            l--;
            sum[number[l]]++;
            temp += 2 * sum[number[l]] - 1;
        }
        while (r < R) {
            r++;
            sum[number[r]]++;
            temp += 2 * sum[number[r]] - 1;
        }
        while (r > R) {
            sum[number[r]]--;
            temp -= 2 * sum[number[r]] + 1;
            r--;
        }
        answer[index] = temp;
    }

    for (int i = 0; i < M; i++) {
        cout << answer[i] << endl;
    }
    return 0;
}