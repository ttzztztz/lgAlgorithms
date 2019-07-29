#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

class Student {
public:
    int wait, eat;

    Student() : wait(0), eat(0) {};

    Student(int w, int e) : wait(w), eat(e) {};
};

const int MAX = 205;
int T = 0, sum[MAX], dp[MAX][MAX * MAX];
Student student[MAX];

int max(int x, int y) {
    return x < y ? y : x;
}

int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    cin >> T;
    for (int i = 1; i <= T; i++) {
        int A = 0, B = 0;
        cin >> A >> B;

        student[i] = {A, B};
    }

    sort(student + 1, student + 1 + T, [](const Student &$1, const Student &$2) -> bool {
        return $1.eat > $2.eat;
    });

    for (int i = 1; i <= T; i++) {
        sum[i] = sum[i - 1] + student[i].wait;
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= T; i++) {
        const Student &s = student[i];
        for (int j = 0; j <= sum[i]; j++) {
            int k = sum[i] - j;
            if (j >= s.wait) {
                dp[i][j] = min(dp[i][j], max(j + s.eat, dp[i - 1][j - s.wait]));
            }
            dp[i][j] = min(dp[i][j], max(k + s.eat, dp[i - 1][j]));
        }
    }

    int answer = 0x7fffffff;
    for (int i = 0; i <= sum[T]; i++) {
        answer = min(answer, dp[T][i]);
    }
    cout << answer;
    return 0;
}