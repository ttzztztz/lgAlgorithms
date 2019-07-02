#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class Edge {
public:
    int from, to, next;

    Edge() : from(0), to(0), next(-1) {};

    Edge(int f, int t, int n) : from(f), to(t), next(n) {};
};

class Point {
public:
    int x, y;

    Point() : x(0), y(0) {};

    Point(int a, int b) : x(a), y(b) {};

    friend ostream &operator<<(ostream &stream, Point &p) {
        stream << p.x << " " << p.y << " ";
        return stream;
    }
};

Edge edge[10005];
int head[105], yParent[105];
bool yVisited[105];
Point meet[105], visit[105];

double dist(Point &a, Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool solve(int x) {
    for (int i = head[x]; i != -1; i = edge[i].next) {
        const int y = edge[i].to;
        if (!yVisited[y]) {
            yVisited[y] = true;
            if (!yParent[y] || solve(yParent[y])) {
                yParent[y] = x;
                return true;
            }
        }
    }
    return false;
}

void addEdge(int u, int v) {
    static int edgeCount;

    edge[edgeCount] = Edge(u, v, head[u]);
    head[u] = edgeCount;
    edgeCount++;
}

int main() {
    memset(head, 0xff, sizeof(head));
    int N = 0, M = 0;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int x = 0, y = 0;
        cin >> x >> y;
        meet[i] = {x, y};
    }

    for (int i = 1; i <= M; i++) {
        int x = 0, y = 0;
        cin >> x >> y;
        visit[i] = {x, y};
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 1; j < N; j++) {
            double distMan = dist(meet[j], meet[j + 1]);
            double distDog = dist(meet[j], visit[i]) + dist(meet[j + 1], visit[i]);

            if (distMan * 2.0 >= distDog) {
                addEdge(i, j);
            }
        }
    }

    int answer = 0;
    for (int x = 1; x <= M; x++) {
        memset(yVisited, 0, sizeof(yVisited));
        if (solve(x)) {
            answer++;
        }
    }
    cout << answer + N << endl;

    for (int i = 1; i <= N; i++) {
        cout << meet[i];

        if (yParent[i]) {
            cout << visit[yParent[i]];
        }

    }
    return 0;
}