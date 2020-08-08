#include <iostream>
#include <cstdlib> // provide NULL and size_t
#include "Bag.h"
using namespace std;

Bag::Bag() {
	head_ptr = NULL;
	many_nodes = 0;
}

Bag::Bag(const Bag& source) {
	node *tail_ptr;
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

Bag::~Bag() {
	list_clear(head_ptr);
	many_nodes = 0; // not necessary
}

void Bag::operator=(const Bag& source) {
	node* tail_ptr;
	if (this == &source) // self-assignment
		return;
	list_clear(head_ptr);
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

void Bag::operator+=(const Bag& addend) {
	node* copy_tail_ptr;
	node* copy_head_ptr;
	if (addend.many_nodes > 0)
	{
		list_copy(addend.head_ptr, copy_head_ptr, copy_tail_ptr);
		copy_tail_ptr->set_link(head_ptr);
		head_ptr = copy_head_ptr;
		many_nodes += addend.many_nodes;
	}
}

bool Bag::erase_one(const value_type& target) {
	node* target_ptr;
	target_ptr = list_search(head_ptr, target);
	if (target_ptr == NULL)
		return false;
	target_ptr->set_data(head_ptr->data());
	list_head_remove(head_ptr);
	--many_nodes;
	return true;
}

size_t Bag::count(const value_type& target) {
	size_t answer = 0;
	const node* cursor;
	cursor = list_search(head_ptr, target);
	while (cursor != NULL)
	{
		++answer;
		cursor = cursor->link();
		cursor = list_search(cursor, target);
	}
	return answer;
}

void Bag::insert(const value_type& entry) {
	list_head_insert(head_ptr, entry);
	++many_nodes;
}

void Bag::show_content() { // ���� bag ���� ���
	node* cursor;
	cursor = head_ptr;
	while (cursor != NULL)
	{
		if (cursor == head_ptr)
			cout << cursor->data();
		else
			cout << " -> " << cursor->data();
		cursor = cursor->link();
	}
}

void Bag::operator-=(const Bag& source) {
	node* cursor;
	cursor = source.head_ptr;
	while (cursor != NULL)
	{
		if (count(cursor->data()) > 0) // ��ġ�� �����Ͱ� ������ ���
			erase_one(cursor->data()); // ��ġ�� ������ ����
		cursor = cursor->link();
	}
}

Bag Bag::operator+(const Bag& source) {
	Bag answer;
	answer += *this;
	answer += source;
	return answer;
}

Bag Bag::operator-(const Bag& source) {
	Bag answer;
	answer = *this;
	answer -= source;
	return answer;
}

bool Bag::operator==(const Bag& source) {
	Bag answer = source; // ������ ����
	node* cursor = head_ptr; // ���� ����
	if (many_nodes != answer.many_nodes) // ��� ���� �ٸ���
		return false;
	while (cursor != NULL)
	{
		if (list_search(answer.head_ptr, cursor->data()) == NULL) // ������ ���� ������
			return false;
		else // ������ ���� ������
			answer.erase_one(cursor->data());
		cursor = cursor->link();
	}
	answer.list_clear(answer.head_ptr);
	return true;
}

void Bag::removeRepetitions() { // �ݺ��� �׸� ����
	node* cursor;
	node* remove; // ������ ���
	cursor = head_ptr;
	while (cursor != NULL)
	{
		if (count(cursor->data()) > 1) { // �ݺ��� ������ ���� ������
			remove = cursor;
			cursor = cursor->link();
			erase_one(remove->data()); // �ݺ��� �׸� ����
			--many_nodes;
		}
		else
			cursor = cursor->link();
	}
}

void Bag::reverse() { // ���� ��� ������ �Ųٷ� �ٲٱ�
	node* previous; // head_ptr �� ���
	node* next; // head_ptr ���� ���
	previous = NULL;
	while (head_ptr)
	{ // ��ũ�� �Ųٷ� �ٲٱ�
		next = head_ptr->link();
		head_ptr->set_link(previous);
		previous = head_ptr;
		head_ptr = next;
	}
	head_ptr = previous;
}

void Bag::sort() { // ���� ����� ������������ ���� - Bubble sort ���
	value_type previous;
	node* cursor;
	node* next;
	for (int i = 0; i < list_length(head_ptr); i++)
	{
		previous = NULL;
		cursor = head_ptr;
		next = head_ptr->link();
		while (cursor->link() != NULL)
		{
			if (cursor->data() > next->data())
			{ // �� �� ���� ���� ũ�� ���� ��ġ �ٲٱ�
				previous = cursor->data();
				cursor->set_data(next->data());
				next->set_data(previous);
			}
			cursor = cursor->link();
			next = next->link();
		}
	}
}