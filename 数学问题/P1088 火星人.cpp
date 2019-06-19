#include<iostream>
#include<algorithm>
#include<vector>

int N, M;
std::vector<int> arr;

int main() {
	std::cin >> N >> M;

	for (int i = 0; i < N;i++) {
		int number = 0;
		std::cin >> number;
		arr.push_back(number);
	}

	for (int i = 0; i < M;i++) {
		std::next_permutation(arr.begin(), arr.end());
	}

	for (int number : arr) {
		std::cout << number << " ";
	}

	return 0;
}