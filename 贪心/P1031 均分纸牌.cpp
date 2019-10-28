#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> arr;
    int avg = 0;
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        arr.push_back(temp);
        avg += temp;
    }
    avg /= N;
    for (int i = 0; i < N; i++) {
        arr[i] -= avg;
    }

    int answer = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] == 0) {
            continue;
        } else {
            arr[i + 1] += arr[i];
            answer++;
        }
    }
    cout << answer;
    return 0;
}