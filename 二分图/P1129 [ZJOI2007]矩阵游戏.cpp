#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 500;
int yParent[MAX], edge[MAX][MAX];
bool yVisit[MAX];

int answer = 0, N = 0;

bool solve(int u) {
    for (int v = 1; v <= N; v++) {
        if (edge[u][v] && !yVisit[v]) {
            yVisit[v] = true;
            if (!yParent[v] || solve(yParent[v])) {
                yParent[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    int T = 0;
    cin >> T;
    for (int _ = 0; _ < T; _++) {
        cin >> N;
        memset(edge, 0, sizeof(edge));
        memset(yParent, 0, sizeof(yParent));
        answer = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cin >> edge[i][j];
            }
        }

        for (int i = 1; i <= N; i++) {
            memset(yVisit, 0, sizeof(yVisit));
            if (solve(i)) {
                answer++;
            }
        }

        if (answer == N) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}