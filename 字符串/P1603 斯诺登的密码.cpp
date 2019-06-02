#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include<sstream>
using namespace std;

map<string, string> dict;

inline void init() {
	dict["one"] = "1";
	dict["two"] = "2";
	dict["three"] = "3";
	dict["four"] = "4";
	dict["five"] = "5";
	dict["six"] = "6";
	dict["seven"] = "7";
	dict["eight"] = "8";
	dict["nine"] = "9";
	dict["ten"] = "10";
	dict["eleven"] = "11";
	dict["twelve"] = "12";
	dict["thirteen"] = "13";
	dict["fourteen"] = "14";
	dict["fifteen"] = "15";
	dict["sixteen"] = "16";
	dict["seventeen"] = "17";
	dict["eighteen"] = "18";
	dict["nineteen"] = "19";
	dict["twenty"] = "20";

	dict["a"] = "1";
	dict["both"] = "2";
	dict["another"] = "2";
	dict["first"] = "1";
	dict["second"] = "2";
	dict["third"] = "3";
}

inline string calc(string input) {
	stringstream ss1;
	ss1 << input;
	int number = 0;
	ss1 >> number;

	int resultNumber = number * number % 100;

	stringstream ss2;
	ss2 << resultNumber;
	string result;
	ss2 >> result;

	if (result.length() == 1) {
		result = "0" + result;
	}

	return result;
}

vector<string> result;

int main() {
	init();

	for (int i = 0; i < 6;i++) {
		string s;
		cin >> s;
		if (dict.count(s)) {
			result.push_back(calc(dict[s]));
		}
	}


	if (result.size() == 0) {
		cout << 0;
	}
	else {
		sort(result.begin(), result.end(), [](string& $1, string& $2)->bool {
			return $1 + $2 < $2 + $1;
			});

		for (int i = 0; i < result.size(); i++) {
			if (i == 0 && result[0][0] == '0') {
				cout << result[i][1];
			}
			else {
				cout << result[i];
			}
		}
	}
	
	return 0;
}