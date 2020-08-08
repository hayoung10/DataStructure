#include <iostream>
#include <cstring>
#include "deque.h"
using namespace std;

int main()
{
	// Settings
	deque<int> d1, d2;
	d1.show_content();
	d1.push_front(1);
	d1.push_front(6);
	d1.push_back(3);
	d1.push_back(7);
	d1.push_front(9);
	d1.show_content();

	d1.pop_front();
	d1.show_content();
	d1.pop_back();
	d1.show_content();

	d2 = d1; // = operator
	d2.show_content();

	d2.push_back(3);
	deque<int> d3(d2); // copy constructor
	d3.show_content();

	cout << "front : " << d1.front() << endl; // front
	cout << "back : " << d1.back() << endl; // back

	bool answer = d2.empty(); // empty
	if (answer == true)
		cout << "The bag is empty" << endl;
	else
		cout << "The bag is not empty" << endl;
	cout << endl;

	char infix[] = "3*X+(Y-12)-Z";
	cout << "infix : " << infix << endl;
	cout << "postfix : " << infixToPostfix(infix) << endl;
	cout << endl;

	char postfix[] = "5 3 2 * + 4 - 5.12 +";
	cout << "postfix : " << postfix << endl;
	cout << "evaluate(postfix) : " << evaluate(postfix) << endl;
	cout << endl;

	char infix2[] = "4*(5+7+0)-8/4*0.5";
	cout << "infix : " << infix2 << endl;
	char* postfix2 = infixToPostfix(infix2);
	cout << "postfix : " << postfix2 << endl;
	cout << "evaluate : " << evaluate(postfix2) << endl;


	return 0;
} 