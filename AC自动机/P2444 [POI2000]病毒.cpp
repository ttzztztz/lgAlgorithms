#include <iostream>
#include <cstring>
#include <deque>

using namespace std;

const int MAX = 30005;

class TrieNode {
public:
    int next[2];
    int fail, count;

    TrieNode() : fail(0), count(0) {
        next[0] = next[1] = 0;
    };
} nodes[MAX];

int nodeCount;
bool visited[MAX], inStack[MAX];

void insert(const char *str) {
    int len = strlen(str), now = 0;
    for (int i = 0; i < len; i++) {
        int index = str[i] - '0';
        if (!nodes[now].next[index]) {
            nodes[now].next[index] = ++nodeCount;
        }
        now = nodes[now].next[index];
    }

    nodes[now].count++;
}

void build() {
    deque<int> queue;
    for (int i = 0; i <= 1; i++) {
        int index = nodes[0].next[i];
        if (index) {
            queue.push_back(index);
        }
    }

    while (!queue.empty()) {
        int index = queue.front();
        queue.pop_front();

        for (int i = 0; i <= 1; i++) {
            int nextIndex = nodes[index].next[i];
            if (nextIndex) {
                nodes[nextIndex].fail = nodes[nodes[index].fail].next[i];
                nodes[nextIndex].count += nodes[nodes[nextIndex].fail].count;
                queue.push_back(nextIndex);
            } else {
                nodes[index].next[i] = nodes[nodes[index].fail].next[i];
            }
        }
    }
}

void dfs(int u) {
    if (inStack[u]) {
        cout << "TAK";
        exit(0);
    }
    if(visited[u] || nodes[u].count){
        return;
    }
    visited[u] = inStack[u] = true;
    for (int i = 0; i <= 1; i++) {
        int nextIndex = nodes[u].next[i];
        dfs(nextIndex);
    }
    inStack[u] = false;
}

char buffer[2005];

int main() {
    int N = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> buffer;
        insert(buffer);
    }
    build();
    dfs(0);
    cout << "NIE";
    return 0;
}

