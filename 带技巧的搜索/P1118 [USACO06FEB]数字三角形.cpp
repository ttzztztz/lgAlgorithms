#include<iostream>
#include<vector>
using namespace std;

const int MAX = 20;
int triange[MAX];
bool visited[MAX];
bool flag = false;
int N, sum;
vector<int> result;

bool dfs(int count, int number, int total) {
	if (count == N) {
		if (sum == total) {
			result.push_back(number);
			flag = true;
			return true;
		}
		else {
			return false;
		}
	}

	if (total > sum || flag) {
		// 最优性剪枝
		return false;
	}

	for (int i = 1; i <= N;i++) {
		if (flag) {
			break;
		}
		if (!visited[i]) {
			visited[i] = true;
			if (dfs(count + 1, i, total + i * triange[count])) {
				result.push_back(number);
				return true;
			}
			visited[i] = false;
		}
	}

	return false;
}

int main() {
	cin >> N >> sum;

	triange[0] = triange[N - 1] = 1;
	for (int i = 1; i * 2 < N;i++) {
		triange[i] = triange[N - i - 1] = (N - i) * triange[i - 1] / i;
	}
	
	dfs(0, 0, 0);

	for (int i = result.size() - 1; i >= 0;i--) {
		if (result[i] != 0) {
			cout << result[i] << " ";
		}
	}

	return 0;
}