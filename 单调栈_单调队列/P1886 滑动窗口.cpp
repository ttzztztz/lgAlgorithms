#include <iostream>
#include <deque>

using namespace std;

const int MAX = 1000005;
int N, K;
int arr[MAX];
int answerMax[MAX], answerMin[MAX];
int answerLen = 0;

void addAnswer(int max, int min) {
    answerMax[answerLen] = max;
    answerMin[answerLen] = min;
    answerLen++;
}

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    deque<int> maxQueue;
    deque<int> minQueue;

    for (int i = 1; i <= K; i++) {
        while ((!maxQueue.empty()) && arr[maxQueue.back()] < arr[i]) {
            maxQueue.pop_back();
        }
        maxQueue.push_back(i);


        while ((!minQueue.empty()) && arr[minQueue.back()] > arr[i]) {
            minQueue.pop_back();
        }
        minQueue.push_back(i);
    }

    addAnswer(arr[maxQueue.front()], arr[minQueue.front()]);

    for (int i = K + 1; i <= N; i++) {
        while ((!maxQueue.empty()) && maxQueue.front() <= i - K) {
            maxQueue.pop_front();
        }
        while ((!maxQueue.empty()) && arr[maxQueue.back()] < arr[i]) {
            maxQueue.pop_back();
        }
        maxQueue.push_back(i);

        while ((!minQueue.empty()) && minQueue.front() <= i - K) {
            minQueue.pop_front();
        }
        while ((!minQueue.empty()) && arr[minQueue.back()] > arr[i]) {
            minQueue.pop_back();
        }
        minQueue.push_back(i);

        addAnswer(arr[maxQueue.front()], arr[minQueue.front()]);
    }

    for (int i = 0; i < answerLen; i++) {
        cout << answerMin[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < answerLen; i++) {
        cout << answerMax[i] << " ";
    }
    return 0;
}