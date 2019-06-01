#include<iostream>
#include<map>
using namespace std;

const int SAME_SIMILARITY = 5;

map<pair<char, char>, int> editSimilarity;
map<char, int> addSimilarity;
int len1, len2;
char str1[105], str2[105];
int dp[105][105];

enum EditMethod {
	edit, add
};

inline int max(int x, int y) {
	return x < y ? y : x;
}

inline void init() {
	addSimilarity['A'] = -3;
	addSimilarity['C'] = -4;
	addSimilarity['G'] = -2;
	addSimilarity['T'] = -1;

	editSimilarity[{'A', 'C'}] = -1;
	editSimilarity[{'C', 'A'}] = -1;

	editSimilarity[{'A', 'G'}] = -2;
	editSimilarity[{'G', 'A'}] = -2;

	editSimilarity[{'A', 'T'}] = -1;
	editSimilarity[{'T', 'A'}] = -1;

	editSimilarity[{'C', 'T'}] = -2;
	editSimilarity[{'T', 'C'}] = -2;

	editSimilarity[{'C', 'G'}] = -3;
	editSimilarity[{'G', 'C'}] = -3;

	editSimilarity[{'T', 'G'}] = -2;
	editSimilarity[{'G', 'T'}] = -2;
}

int DP(int offset1, int offset2) {
	if (offset1 < 0 || offset2 < 0) {
		return 0;
	}

	if (dp[offset1][offset2]) {
		return dp[offset1][offset2];
	}

	char ch1 = str1[offset1], ch2 = str2[offset2];

	// 容易忽视 一个字符串遍历完毕 另一个字符串没有遍历完毕 少算的相似度问题
	if (offset1 >= len1 && offset2 < len2) {
		return dp[offset1][offset2] = DP(offset1, offset2 + 1) + addSimilarity[ch2];
	}
	else if (offset2 >= len2 && offset1 < len1) {
		return dp[offset1][offset2] = DP(offset1 + 1, offset2) + addSimilarity[ch1];
	}
	else if (offset1 >= len1 && offset2 >= len2) {
		return 0;
	}

	if (ch1 == ch2) {
		return dp[offset1][offset2] = SAME_SIMILARITY + DP(offset1 + 1, offset2 + 1);
	}
	else {
		int case1 = DP(offset1 + 1, offset2 + 1) + editSimilarity[{ch1, ch2}];
		int case2 = DP(offset1, offset2 + 1) + addSimilarity[ch2];
		int case3 = DP(offset1 + 1, offset2) + addSimilarity[ch1];

		return dp[offset1][offset2] = max(max(case1, case2), case3);
	}
}

int main() {
	init();

	cin >> len1 >> str1;
	cin >> len2 >> str2;

	cout << DP(0, 0);

	return 0;
}