#include<iostream>
#include<algorithm>
using namespace std;

pair<int,int> arr[6000];

int main() {
	ios::sync_with_stdio(false);

	int n, m = 0;
	cin >> n >> m;
	for (int i = 0; i < n;i++) {
		int id = 0, score = 0;
		cin >> id >> score;
		arr[i] = { id, score };
	}

	int line = m * 1.5;
	sort(arr, arr + n, [](pair<int, int>& $1, pair<int, int>& $2)->bool {
		if ($1.second != $2.second) {
			return $1.second > $2.second;
		}
		else {
			return $1.first < $2.first;
		}
	});

	auto [id, score] = arr[line - 1];

	cout << score << " ";

	int i = 0;
	while (i < n && arr[i].second >= score) {
		i++;
	}
	cout << i << endl;

	for (int m = 0; m < i;m++) {
		auto& people = arr[m];
		cout << people.first << " " << people.second << " " << endl;
	}

	return 0;
}