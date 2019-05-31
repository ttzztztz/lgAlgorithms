#include<iostream>
#include<cstring>
#include<deque>
#include<map>
using namespace std;

class Node {
public:
	string str;
	int step;
	Node() : str(""), step(0) {};
	Node(string s, int _step) : str(s), step(_step) {};
};

const int MAX_STEP = 10;
string a, b;
pair<string, string> transform[8];
int regularCount = 0;

int bfs() {
	int answer = 0;
	deque<Node> queue;
	map<string, int> record;
	queue.push_back({a, 0});

	while (!queue.empty()) {
		Node node = queue.front();
		queue.pop_front();

		if (record.count(node.str)) {
			continue;
		}

		if (node.str == b) {
			answer = node.step;
			break;
		}

		record[node.str] = 1;

		for (int j = 0; j < regularCount; j++) {
			auto [t_raw, t_new] = transform[j];
			int start_position = node.str.find(t_raw);

			// 有可能一个串能发现多个匹配
			while (start_position != -1) {
				int end_position = start_position + t_raw.length();

				string transformResult =
					node.str.substr(0, start_position)
					+ t_new + node.str.substr(end_position);

				queue.push_back({ transformResult, node.step + 1 });
				start_position = node.str.find(t_raw, end_position);
			}
		}
	}

	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	string tempa, tempb;

	cin >> a >> b;
	while (cin >> tempa >> tempb) {
		transform[regularCount] = {tempa, tempb};
		regularCount++;
	}

	int result = bfs();

	if (result > 10 || result == 0) {
		cout << "NO ANSWER!";
	}
	else {
		cout << result;
	}

	return 0;
}