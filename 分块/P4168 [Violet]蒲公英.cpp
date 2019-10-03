#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

//#define DEBUG 1

using namespace std;

const int MAX = 40005, SQRT_MAX = 205;
int N = 0, M = 0, blockSize = 0, blockCount = 0, dataCount = 0;
int appearSum[SQRT_MAX][MAX], blockAnswer[SQRT_MAX][SQRT_MAX];
int tempCount[MAX];
int dataList[MAX];
vector<int> numberList;

int belong(int x) {
    return (x - 1) / blockSize + 1;
}

int leftBound(int block) {
    return (block - 1) * blockSize + 1;
}

int rightBound(int block) {
    return block * blockSize;
}

void dataInput() {
    ios::sync_with_stdio(false);
    cin >> N >> M;
    blockSize = sqrt(N);
    blockCount = N / blockSize;
    if (N % blockSize) {
        blockCount++;
    }
#ifdef DEBUG
    cout << "DEBUG: BLOCK SIZE = " << blockSize << endl;
#endif

    for (int i = 1; i <= N; i++) {
        int tempNumber = 0;
        cin >> tempNumber;

        dataList[i] = tempNumber;
        numberList.push_back(tempNumber);
    }
    std::sort(numberList.begin(), numberList.end());
    auto endIterator = std::unique(numberList.begin(), numberList.end());
    dataCount = endIterator - numberList.begin() + 1;
    for (int &data: dataList) {
        data = std::lower_bound(numberList.begin(), endIterator, data) - numberList.begin();
    }
}

void prepare() {
    for (int i = 1; i <= N; i++) {
        appearSum[belong(i)][dataList[i]]++;
    }
    for (int i = 1; i <= belong(N); i++) {
        for (int j = 0; j <= dataCount; j++) {
            appearSum[i][j] += appearSum[i - 1][j];
        }

        std::memset(tempCount, 0, sizeof(tempCount));
        int currentAnswer = 0;

        for (int j = leftBound(i); j <= N; j++) {
            tempCount[dataList[j]]++;
            if (tempCount[dataList[j]] > tempCount[currentAnswer] || (tempCount[dataList[j]] == tempCount[currentAnswer]
                                                                      && dataList[j] < currentAnswer)) {
                currentAnswer = dataList[j];
            }

            blockAnswer[i][belong(j)] = currentAnswer;
        }
    }
}

int search(int l, int r) {
#ifdef DEBUG
    cout << "DEBUG:SEARCH: " << l << "," << r << endl;
#endif
    int answer = 0;
    const int blockL = belong(l), blockR = belong(r);

#ifdef DEBUG
    cout << "DEBUG:block interval:" << blockL << "," << blockR << endl;
#endif

    if (blockR - blockL <= 1) {
        memset(tempCount, 0, sizeof(tempCount));
        for (int i = l; i <= r; i++) {
            tempCount[dataList[i]]++;
            if (tempCount[dataList[i]] > tempCount[answer]
                || (tempCount[dataList[i]] == tempCount[answer] && dataList[i] < answer)) {
                answer = dataList[i];
            }
        }
    } else {
        answer = blockAnswer[blockL + 1][blockR - 1];
        const int leftBlockEnd = rightBound(belong(l)), rightBlockStart = leftBound(belong(r));

#ifdef DEBUG
        cout << "DEBUG:out of block:" << leftBlockEnd << "," << rightBlockStart << endl;
#endif

        std::memset(tempCount, 0, sizeof(tempCount));

        for (int i = l; i <= leftBlockEnd; i++) {
            tempCount[dataList[i]]++;
            if (tempCount[dataList[i]] + appearSum[blockR - 1][dataList[i]] - appearSum[blockL][dataList[i]] >
                tempCount[answer] + appearSum[blockR - 1][answer] - appearSum[blockL][answer] ||
                (tempCount[dataList[i]] + appearSum[blockR - 1][dataList[i]] - appearSum[blockL][dataList[i]] ==
                 tempCount[answer] + appearSum[blockR - 1][answer] - appearSum[blockL][answer] &&
                 dataList[i] < answer)) {
                answer = dataList[i];
            }
        }
        for (int i = rightBlockStart; i <= r; i++) {
            tempCount[dataList[i]]++;
#ifdef DEBUG
            cout << "DEBUG: TEMP COUNT:"
                 << tempCount[dataList[i]] << "," << appearSum[blockR - 1][dataList[i]] << ","
                 << appearSum[blockL][dataList[i]]
                 << endl;
            cout << "DEBUG: TEMP COUNT:"
                 << tempCount[answer] << "," << appearSum[blockR - 1][answer] << "," << appearSum[blockL][answer]
                 << endl;
#endif
            if (tempCount[dataList[i]] + appearSum[blockR - 1][dataList[i]] - appearSum[blockL][dataList[i]] >
                tempCount[answer] + appearSum[blockR - 1][answer] - appearSum[blockL][answer] ||
                (tempCount[dataList[i]] + appearSum[blockR - 1][dataList[i]] - appearSum[blockL][dataList[i]] ==
                 tempCount[answer] + appearSum[blockR - 1][answer] - appearSum[blockL][answer] &&
                 dataList[i] < answer)) {
                answer = dataList[i];
            }
        }

        int q = 0;
    }
    return numberList[answer];
}

void dataOutput() {
    int x = 0;
    for (int i = 1; i <= M; i++) {
        int l0 = 0, r0 = 0;
        cin >> l0 >> r0;

        int l = (l0 + x - 1) % N + 1;
        int r = (r0 + x - 1) % N + 1;

        if (l < r) {
            x = search(l, r);
        } else {
            x = search(r, l);
        }
        cout << x << endl;
    }
}

int main() {

    dataInput();
    prepare();
    dataOutput();

    return 0;
}