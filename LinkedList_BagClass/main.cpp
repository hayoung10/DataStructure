#include <iostream>
#include "node.h" // provide node class
#include "Bag.h" // provide bag class
using namespace std;

int main()
{
	// Settings
	Bag  bag2, bag3, bag4;
	bag2.insert(3);
	bag2.insert(5);
	bag2.insert(21);
	bag2.insert(14);
	bag4.insert(7);
	bag4.insert(7);
	bag4.insert(9);
	bag4.insert(5);
	bag4.insert(5);
	bag4.insert(5);

	// constructors
	cout << "[constructors]" << endl;
	Bag bag1;
	cout << "Bag bag1;   =>   bag1 : ";
	bag1.show_content();

	// insert function
	bag1.insert(5);
	bag1.insert(9);
	cout << endl << endl << "[insert]" << endl << "Before   =>   bag1 : ";
	bag1.show_content();
	bag1.insert(2);
	bag1.insert(13);
	bag1.insert(1);
	bag1.insert(9);
	cout << endl << "After(insert 2,13,1,9)   =>   bag1 : ";
	bag1.show_content();

	// erase_one function
	cout << endl << endl << "[erase_one]" << endl << "Before   =>   bag1 : ";
	bag1.show_content();
	bag1.erase_one(2);
	cout << endl << "After(erase 2)   =>   bag1 : ";
	bag1.show_content();

	// count function
	cout << endl << endl << "[count]" << endl;
	bag1.show_content();
	cout << endl << "Count 9 : " << bag1.count(9) << endl;

	// + operator
	cout << endl << "[+ operator]" << endl << "Before   =>   bag1 : ";
	bag1.show_content();
	cout << " / bag2 : ";
	bag2.show_content();
	bag3 = bag1 + bag2;
	cout << endl << "After(bag3=bag1+bag2)   =>   bag3 : ";
	bag3.show_content();

	// += operator
	cout << endl << endl << "[+= operator]" << endl << "Before   =>   bag1 : ";
	bag1.show_content();
	cout << " / bag2 : ";
	bag2.show_content();
	bag1 += bag2;
	cout << endl << "After(bag1+=bag2)   =>   bag1 : ";
	bag1.show_content();

	// - operator
	Bag bag5;
	cout << endl << endl << "[- operator]" << endl << "Before   =>   bag1 : ";
	bag1.show_content();
	cout << " / bag4 : ";
	bag4.show_content();
	bag5 = bag1 - bag4;
	cout << endl << "After(bag5=bag1-bag4)   =>   bag5 : ";
	bag5.show_content();

	// -= operator
	cout << endl << endl << "[-= operator]" << endl << "Before   =>   bag1 : ";
	bag1.show_content();
	cout << endl << "              bag2 : ";
	bag2.show_content();
	cout << " / bag4 : ";
	bag4.show_content();
	bag1 -= bag4;
	cout << endl << "After(bag1-=bag4)   =>   bag1 : ";
	bag1.show_content();
	bag1 -= bag2;
	cout << endl << "After(bag1-=bag2)   =>   bag1 : ";
	bag1.show_content();

	// = operator
	cout << endl << endl << "[= operator]" << endl << "Before   =>   bag2 : ";
	bag2.show_content();
	cout << " / bag5 : ";
	bag5.show_content();
	bag5 = bag2;
	cout << endl << "After(bag5=bag2)   =>   bag5 : ";
	bag5.show_content();

	// copy constructor
	cout << endl << endl << "[copy constructor]" << endl << "Before   =>   bag1 : ";
	bag1.show_content();
	Bag bag6(bag1);
	cout << endl << "After( Bag bag6(bag1); )   =>   bag6 : ";
	bag6.show_content();

	// == operator
	cout << endl << endl << "[== operator]" << endl << "Before   =>   bag1 : ";
	bag1.show_content();
	cout << endl << "              bag2 : ";
	bag2.show_content();
	cout << " / bag6 : ";
	bag6.show_content();
	cout << endl << "After( (bag1 == bag2)? )   =>   ";
	if ((bag1 == bag2) == true)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;
	cout << "After( (bag1 == bag6)? )   =>   ";
	if ((bag1 == bag6) == true)
		cout << "Yes" << endl;
	else
		cout << "No" << endl;

	// removeRepetitions
	cout << endl << "[removeReptitions]" << endl << "Before   =>   bag4 : ";
	bag4.show_content();
	bag4.removeRepetitions();
	cout << endl << "After   =>   bag4 : ";
	bag4.show_content();

	// reverse
	cout << endl << endl << "[reverse]" << endl << "Before   =>   bag2 : ";
	bag2.show_content();
	bag2.reverse();
	cout << endl << "After   =>   bag2 : ";
	bag2.show_content();

	// sort
	cout << endl << endl << "[sort]" << endl << "Before   =>   bag3 : ";
	bag3.show_content();
	bag3.sort();
	cout << endl << "After   =>   Bag3 : ";
	bag3.show_content();

	cout << endl;

	return 0;
}