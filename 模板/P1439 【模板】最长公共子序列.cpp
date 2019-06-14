#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int MAX = 100005;
int arr1[MAX], arr2[MAX], map[MAX];
int N;
vector<int> stack;

const auto comp = [&](const int $1, const int $2)->bool {
	return map[$1] < map[$2];
};

int main() {
	cin >> N;
	for (int i = 0; i < N;i++) {
		cin >> arr1[i];
		map[arr1[i]] = i;
	}
	for (int i = 0; i < N;i++) {
		cin >> arr2[i];
	}


	stack.push_back(arr2[0]);
	for (int i = 1; i < N;i++) {
		if (map[arr2[i]] > map[stack.back()]) {
			stack.push_back(arr2[i]);
		}
		else {
			auto it = lower_bound(stack.begin(), stack.end(), arr2[i], comp);
			*it = arr2[i];
		}
	}
	cout << stack.size();
	return 0;
}