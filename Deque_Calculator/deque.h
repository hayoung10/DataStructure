#pragma once
#include <cassert>
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

template <class Item>
class dnode {
public:
	typedef Item value_type;
	dnode() { data_field = value_type(); link_fore = NULL; link_back = NULL; }
	dnode(const value_type& init_data, dnode* init_fore, dnode* init_back) {
		data_field = init_data;
		link_fore = init_fore;
		link_back = init_back;
	}
	void set_data(const value_type& new_data) { data_field = new_data; }
	void set_link_fore(dnode* new_link) { link_fore = new_link; }
	void set_link_back(dnode* new_link) { link_back = new_link; }
	value_type data() const { return data_field; }
	const dnode* fore() const { return link_fore; }
	const dnode* back() const { return link_back; }
	dnode* fore() { return link_fore; }
	dnode* back() { return link_back; }
	size_t list_length(const dnode* head_ptr) {
		size_t answer = 0;
		const dnode *cursor;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->fore())
			++answer;
		return answer;
	}
	void list_head_insert(dnode*& head_ptr, const value_type& entry) {
		if (list_length(head_ptr) == 0)
			head_ptr = new dnode(entry, head_ptr, NULL);
		else {
			head_ptr = new dnode(entry, head_ptr, NULL);
			dnode* cursor = head_ptr->fore();
			cursor->set_link_back(head_ptr);
		}
	}
	void list_insert(dnode* previous_ptr, const value_type& entry) {
		dnode* insert_ptr;
		if (previous_ptr->fore() == NULL)
			insert_ptr = new dnode(entry, previous_ptr->fore(), previous_ptr);
		else {
			dnode* cursor = previous_ptr;
			cursor = cursor->fore();
			insert_ptr = new dnode(entry, cursor, previous_ptr);
			cursor->set_link_back(insert_ptr);
		}
		previous_ptr->set_link_fore(insert_ptr);
	}
	dnode* list_search(dnode* head_ptr, const value_type& target) {
		dnode* cursor;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->fore())
			if (target == cursor->data())
				return cursor;
		return NULL;
	}
	const dnode* list_search(const dnode* head_ptr, const value_type& target) {
		const dnode* cursor;
		for (cursor = head_ptr; cursor != NULL; cursor = cursor->fore())
			if (target == cursor->data())
				return cursor;
		return NULL;
	}
	dnode* list_locate(dnode* head_ptr, size_t position) {
		dnode* cursor = head_ptr;
		size_t i;
		assert(0 < position);
		for (i = 1; (cursor != NULL && i < position); ++i)
			cursor = cursor->fore();
		return cursor;
	}
	const dnode* list_locate(const dnode* head_ptr, size_t position) {
		const dnode* cursor = head_ptr;
		size_t i;
		assert(0 < position);
		for (i = 1; (cursor != NULL && i < position); ++i)
			cursor = cursor->fore();
		return cursor
	}
	void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr) {
		head_ptr = NULL; tail_ptr = NULL;
		if (source_ptr == NULL) return;
		list_head_insert(head_ptr, source_ptr->data());
		tail_ptr = head_ptr;
		source_ptr = source_ptr->fore();
		while (source_ptr != NULL) {
			list_insert(tail_ptr, source_ptr->data());
			tail_ptr = tail_ptr->fore();
			source_ptr = source_ptr->fore();
		}
	}
	void list_head_remove(dnode*& head_ptr) {
		dnode* remove_ptr = head_ptr;
		head_ptr = head_ptr->fore();
		if (head_ptr != NULL) {
			head_ptr->set_link_back(NULL);
		}
		delete remove_ptr;
	}
	void list_remove(dnode* previous_ptr) {
		dnode* remove_ptr;
		remove_ptr = previous_ptr->fore();
		if (remove_ptr->fore() == NULL)
			previous_ptr->set_link_fore(NULL);
		else {
			dnode* cursor = remove_ptr;
			cursor = cursor->fore();
			previous_ptr->set_link_fore(cursor);
			cursor->set_link_back(previous_ptr);
		}
		delete remove_ptr;
	}
	void list_clear(dnode*& head_ptr) {
		while (head_ptr != NULL)
			list_head_remove(head_ptr);
	}
private:
	value_type data_field;
	dnode *link_fore;
	dnode *link_back;
};

template <class Item2>
class deque : dnode<Item2> {
public:
	typedef Item2 size_type;
	deque() {
		front_ptr = NULL;
		rear_ptr = NULL;
		count = 0;
	}
	deque(const deque<Item2>& source) {
		count = source.count;
		list_copy(source.front_ptr, front_ptr, rear_ptr);
	}
	~deque() { // destructor
		list_clear(front_ptr);
	}
	void show_content() { // 현재 deque 상태 출력
		dnode<Item2> *cursor = front_ptr;
		dnode<Item2> *cursor2 = rear_ptr;
		cout << "head부터 출력 : ";
		while (cursor != NULL) {
			cout << cursor->data() << " ";
			cursor = cursor->fore();
		}
		cout << endl << "tail부터 출력 : ";
		while (cursor2 != NULL) {
			cout << cursor2->data() << " ";
			cursor2 = cursor2->back();
		}
		cout << endl << "count : " << count << endl << endl;
	}
	void operator=(const deque<Item2>& source) {
		if (this == &source)
			return;
		list_clear(front_ptr);
		list_copy(source.front_ptr, front_ptr, rear_ptr);
		count = source.count;
	}
	void push_front(const Item2& entry) {
		if (empty()) {
			list_head_insert(front_ptr, entry);
			rear_ptr = front_ptr;
		}
		else
			list_head_insert(front_ptr, entry);
		++count;
	}
	void push_back(const Item2& entry) {
		if (empty()) {
			list_head_insert(front_ptr, entry);
			rear_ptr = front_ptr;
		}
		else {
			list_insert(rear_ptr, entry);
			rear_ptr = rear_ptr->fore();
		}
		++count;
	}
	void pop_front() {
		assert(!empty());
		dnode<Item2> *remove_ptr = front_ptr;
		if (count > 1) {
			front_ptr = front_ptr->fore();
			front_ptr->set_link_back(NULL);
		}
		else {
			front_ptr = NULL;
			rear_ptr = NULL;
		}
		list_head_remove(remove_ptr);
		--count;
	}
	void pop_back() {
		assert(!empty());
		if (count > 1) {
			rear_ptr = rear_ptr->back();
			list_remove(rear_ptr);
			rear_ptr->set_link_fore(NULL);
		}
		else {
			dnode<Item2> *remove_ptr = rear_ptr;
			front_ptr = NULL;
			rear_ptr = NULL;
			list_head_remove(remove_ptr);
		}
		--count;
	}
	Item2 front() const {
		assert(!empty());
		return front_ptr->data();
	}
	Item2 back() const {
		assert(!empty());
		return rear_ptr->data();
	}
	bool empty() const { return (count == 0); }
	size_type size() const { return count; }
private:
	dnode<Item2> *front_ptr;
	dnode<Item2> *rear_ptr;
	size_type count;
};

double evaluate(char expr[]) {
	deque<double> dq;
	double operand1, operand2;
	char *input = strtok(expr, " ");

	while (input != NULL) {
		if (isdigit(*input)) {
			double number = atof(input);
			dq.push_back(number);
		}
		else if (strchr("+-*/", *input) != NULL) {
			operand2 = dq.back();
			dq.pop_back();
			operand1 = dq.back();
			dq.pop_back();
			switch (*input) {
			case '+':dq.push_back(operand1 + operand2); break;
			case '-':dq.push_back(operand1 - operand2); break;
			case '*':dq.push_back(operand1 * operand2); break;
			case '/':dq.push_back(operand1 / operand2); break;
			}
		}
		input = strtok(NULL, " ");
	}
	double answer = dq.front();
	return answer;
}

char* infixToPostfix(char expr[]) {
	const char RIGHT_PARENTHESIS = ')';
	deque<char> dq2;
	int num = 0; // index 0부터 시작
	string postfix = "";
	int priority = 0, priority2 = 0; // 우선순위를 비교하기 위해
	bool blank = false; // true이면 공백 넣기
	
	while (expr[num] != '\0') {
		if (strchr("+-*/", expr[num]) != NULL) {
			blank = false;
			switch (expr[num]) {
			case '+':priority = 1; break;
			case '-':priority = 1; break;
			case '*':priority = 2; break;
			case '/':priority = 2; break;
			}
			if (dq2.empty() == false && strchr("+-*/", dq2.back()) != NULL) {
				switch (dq2.back()) {
				case '+':priority2 = 1; break;
				case '-':priority2 = 1; break;
				case '*':priority2 = 2; break;
				case '/':priority2 = 2; break;
				}
			}
			else
				priority2 = 0;
			if (priority2 >= priority) {
				postfix += dq2.back();
				blank = true;
				dq2.pop_back();
			}
			dq2.push_back(expr[num]);
		}
		else if (expr[num] == '(') {
			blank = false;
			dq2.push_back(expr[num]);
		}
		else if (expr[num] == ')') {
			blank = false;
			while (dq2.back() != '(') {
				postfix += dq2.back();
				dq2.pop_back();
				blank = true;
			}
			dq2.pop_back();
		}
		else {
			if (expr[num] >= '0' && expr[num] <= '9')
				postfix += expr[num];
			if (expr[num] >= 'a' && expr[num] <= 'z')
				postfix += expr[num];
			if (expr[num] >= 'A' && expr[num] <= 'Z')
				postfix += expr[num];
			blank = true;
			if (expr[num] == '.') {
				postfix += expr[num];
				blank = false;
			}
			if (expr[num+1] >= '0' && expr[num+1] <= '9')
				blank = false;
			else if (expr[num+1] >= 'a' && expr[num+1] <= 'z')
				blank = false;
			else if (expr[num+1] >= 'A' && expr[num+1] <= 'Z')
				blank = false;
			else if (expr[num + 1] == '.')
				blank = false;
		}
		if (blank == true)
			postfix += " ";
		num++;
	}
	while (!dq2.empty()) {
		postfix += dq2.back();
		postfix += " ";
		dq2.pop_back();
	}

	// string을 char*형으로 변환
	char *answer = strcpy(new char[postfix.length() + 1], postfix.c_str());

	return answer;
}