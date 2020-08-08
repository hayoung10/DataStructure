#include "set.h"
#include <iostream>
#include <string>
using namespace main_savitch_11;
using namespace std;

int main()
{
	set<int> s1;
	string input;

	while (1) {
		cout << "*Menu : insert, erase, count, stop" << endl;
		getline(cin, input);
		int num;
		string check;
		if (input.substr(0, 7) == "insert ") {
			num = atoi(input.substr(7, input.length()).c_str());
			s1.insert(num);
			cout << "[B-Tree]" << endl;
			s1.show_content();
		}
		else if (input.substr(0, 6) == "erase ") {
			num = atoi(input.substr(6, input.length()).c_str());
			s1.erase(num);
			cout << "[B-Tree]" << endl;
			s1.show_content();
		}
		else if (input.substr(0, 6) == "count ") {
			num = atoi(input.substr(6, input.length()).c_str());
			cout << "count result : " << s1.count(num) << endl;
		}
		else if (input == "stop")
			break;
	}
	cout << endl;
	cout << "*보너스 - copy constructor & = operator" << endl << "s1 B-Tree 상태" << endl;
	s1.show_content();
	cout << "set<int> s2(s1);" << endl << "s2 B-Tree 상태" << endl;
	set<int> s2(s1); // copy constructor
	s2.show_content();
	cout << "s3 = s1;" << endl << "s3 B-Tree 상태" << endl;
	set<int> s3;
	s3 = s1; // =operator
	s3.show_content();

	return 0;
}