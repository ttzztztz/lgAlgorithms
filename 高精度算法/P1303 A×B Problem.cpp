#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

inline int convert(const char ch) {
	return (int)(ch) - '0';
}

int main() {
	string s1 = "", s2 = "";
	cin >> s1 >> s2;
	int s1_len = s1.length(), s2_len = s2.length();
	vector<int> result(s1_len + s2_len);

	for (int i = 0; i < s1_len;i++) {
		for (int j = 0; j < s2_len;j++) {
			result[i + j] += convert(s1[s1_len - 1 - i]) * convert(s2[s2_len - 1 - j]);
			result[i + j + 1] += result[i + j] / 10;
			result[i + j] %= 10;
		}
	}

	int size = result.size();
	while (size && result[size - 1]==0) {
		size--;
	}
	result.resize(size);
	
	for (int i = size - 1; i >= 0;i--) {
		cout << result[i];
	}
	if (size == 0) {
		cout << "0";
	}

	return 0;
}