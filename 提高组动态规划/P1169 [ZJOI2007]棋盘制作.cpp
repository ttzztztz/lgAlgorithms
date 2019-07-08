#include <iostream>

using namespace std;
const int MAX = 2005;

int N, M, matrix[MAX][MAX], dp_left[MAX][MAX], dp_right[MAX][MAX], dp_top[MAX][MAX];

int max(int x, int y) {
    return x < y ? y : x;
}

int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> matrix[i][j];
            dp_left[i][j] = j;
            dp_right[i][j] = j;
            dp_top[i][j] = 1;
        }
    }
    int answer1 = 0, answer2 = 0;
    int a = 0, b = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 2; j <= M; j++) {
            if (matrix[i][j - 1] != matrix[i][j]) {
                dp_left[i][j] = dp_left[i][j - 1];
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = M - 1; j >= 1; j--) {
            if (matrix[i][j + 1] != matrix[i][j]) {
                dp_right[i][j] = dp_right[i][j + 1];
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (i >= 2 && matrix[i][j] != matrix[i - 1][j]) {
                dp_left[i][j] = max(dp_left[i][j], dp_left[i - 1][j]);
                dp_right[i][j] = min(dp_right[i][j], dp_right[i - 1][j]);
                dp_top[i][j] = dp_top[i - 1][j] + 1;
            }

            a = dp_right[i][j] - dp_left[i][j] + 1;
            b = dp_top[i][j];

            if (a < b) {
                answer1 = max(answer1, a * a);
            } else {
                answer1 = max(answer1, b * b);
            }
            answer2 = max(answer2, a * b);
        }
    }

    cout << answer1 << endl << answer2 << endl;
    return 0;
}

