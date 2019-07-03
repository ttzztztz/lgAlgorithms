#include<iostream>
#include<cmath>

using namespace std;

const int MAX = 5005, MAXN = 150005;
int number[MAXN], storage[MAX][MAX];
int N = 0, M = 0, sqrtN = 0;

void prepare() {
    sqrtN = sqrt((double) N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= sqrtN; j++) {
            storage[j][i % j] += number[i];
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> number[i];
    }
    prepare();

    for (int _ = 1; _ <= M; _++) {
        char opt = '\0';
        int x = 0, y = 0;
        cin >> opt >> x >> y;
        if (opt == 'A') {
            int answer = 0;
            if (x <= sqrtN) {
                answer = storage[x][y];
            } else {
                for (int i = y; i <= N; i += x) {
                    answer += number[i];
                }
            }
            cout << answer << endl;
        } else if (opt == 'C') {
            for (int j = 1; j <= sqrtN; j++) {
                storage[j][x % j] += y - number[x];
            }
            number[x] = y;
        }

    }
    return 0;
}