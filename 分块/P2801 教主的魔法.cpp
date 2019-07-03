#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 1000010;
int blockSize, blockNumber, N;
int number[MAX], lazyTag[MAX], orderedNumber[MAX];

int belong(int index) {
    return (index - 1) / blockSize + 1;
}

int LIndex(int belong) {
    return (belong - 1) * blockSize + 1;
}

int RIndex(int belong) {
    if (belong == blockNumber) {
        return N;
    } else {
        return belong * blockSize;
    }
}

void init() {
    blockSize = sqrt(N);
    blockNumber = N / blockSize;
    if (N % blockSize) {
        blockNumber++;
    }
    memcpy(orderedNumber, number, sizeof(int) * N);
    for (int i = 1; i <= blockNumber; i++) {
        sort(orderedNumber + LIndex(i), orderedNumber + RIndex(i) + 1);
    }
}

int main() {
    int Q = 0;
    cin >> N >> Q;

    for (int i = 1; i <= N; i++) {
        cin >> number[i];
    }
    init();
    for (int _ = 0; _ < Q; _++) {
        char opt = '\0';
        int x = 0, y = 0, k = 0;
        cin >> opt >> x >> y >> k;
        if (opt == 'A') {
            int answer = 0;
            if (belong(x) == belong(y)) {
                for (int i = x; i <= y; i++) {
                    if (lazyTag[belong(x)] + number[i] >= k) {
                        answer++;
                    }
                }
            } else {
                for (int i = x; i <= RIndex(belong(x)); i++) {
                    if (lazyTag[belong(x)] + number[i] >= k) {
                        answer++;
                    }
                }
                for (int i = LIndex(belong(y)); i <= y; i++) {
                    if (lazyTag[belong(y)] + number[i] >= k) {
                        answer++;
                    }
                }
                for (int i = belong(x) + 1; i <= belong(y) - 1; i++) {
                    int left = LIndex(i), right = RIndex(i), result = 0;
                    while (left <= right) {
                        int mid = (left + right) / 2;
                        if (orderedNumber[mid] + lazyTag[i] >= k) {
                            result = RIndex(i) - mid + 1;
                            right = mid - 1;
                        } else {
                            left = mid + 1;
                        }
                    }
                    answer += result;
                }
            }
            cout << answer << endl;
        } else if (opt == 'M') {
            if (belong(x) == belong(y)) {
                for (int i = x; i <= y; i++) {
                    number[i] += k;
                }
                for (int i = LIndex(belong(x)); i <= RIndex(belong(y)); i++) {
                    orderedNumber[i] = number[i];
                }
                sort(orderedNumber + LIndex(belong(x)), orderedNumber + RIndex(belong(y)) + 1);
            } else {
                for (int i = x; i <= RIndex(belong(x)); i++) {
                    number[i] += k;
                }
                for (int i = LIndex(belong(x)); i <= RIndex(belong(x)); i++) {
                    orderedNumber[i] = number[i];
                }
                sort(orderedNumber + LIndex(belong(x)), orderedNumber + RIndex(belong(x)) + 1);
                for (int i = belong(x) + 1; i <= belong(y) - 1; i++) {
                    lazyTag[i] += k;
                }
                for (int i = LIndex(belong(y)); i <= y; i++) {
                    number[i] += k;
                }
                for (int i = LIndex(belong(y)); i <= RIndex(belong(y)); i++) {
                    orderedNumber[i] = number[i];
                }
                sort(orderedNumber + LIndex(belong(y)), orderedNumber + RIndex(belong(y)) + 1);
            }
        }
    }
    return 0;
}