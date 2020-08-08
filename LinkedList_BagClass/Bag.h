#pragma once
#include <cstdlib> // provide NULL and size_t
#include "node.h"  // provide node class

class Bag : node {
public:
	typedef node::value_type value_type;
	Bag();
	Bag(const Bag& source);
	~Bag();
	void operator=(const Bag& source);
	void operator+=(const Bag& addend);
	bool erase_one(const value_type& target);
	size_t count(const value_type& target);
	void insert(const value_type& entry);
	void show_content(); // ���� bag ���� ���
	void operator-=(const Bag& source);
	Bag operator+(const Bag& source);
	Bag operator-(const Bag& source);
	bool operator==(const Bag& source);
	void removeRepetitions(); // �ݺ��� �׸� ����
	void reverse(); //  ���� ��� ������ �Ųٷ� �ٲٱ�
	void sort(); // ���� ����� ������������ ����
private:
	node* head_ptr;
	size_t many_nodes;
};