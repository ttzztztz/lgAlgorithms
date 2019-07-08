#include <iostream>

using namespace std;
const int MAX = 1005;

int N, T, matrix[MAX][MAX], dp_left[MAX][MAX], dp_right[MAX][MAX], dp_top[MAX][MAX];

int max(int x, int y) {
    return x < y ? y : x;
}

int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    cin >> N >> T;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            matrix[i][j] = 1;
        }
    }

    for (int i = 1; i <= T; i++) {
        int x = 0, y = 0;
        cin >> x >> y;
        matrix[x][y] = 0;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (matrix[i][j]) {
                dp_left[i][j] = j;
                dp_right[i][j] = j;
                dp_top[i][j] = 1;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 2; j <= N; j++) {
            if (matrix[i][j] && matrix[i][j - 1]) {
                dp_left[i][j] = dp_left[i][j - 1];
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = N - 1; j >= 1; j--) {
            if (matrix[i][j] && matrix[i][j + 1]) {
                dp_right[i][j] = dp_right[i][j + 1];
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i >= 2 && matrix[i][j] && matrix[i - 1][j]) {
                dp_left[i][j] = max(dp_left[i][j], dp_left[i - 1][j]);
                dp_right[i][j] = min(dp_right[i][j], dp_right[i - 1][j]);
                dp_top[i][j] = dp_top[i - 1][j] + 1;
            }
            int a = dp_right[i][j] - dp_left[i][j] + 1;
            int b = dp_top[i][j];
            answer = max(answer, min(a, b));
        }
    }
    cout << answer;
    return 0;
}

