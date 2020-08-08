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
	void show_content(); // 현재 bag 상태 출력
	void operator-=(const Bag& source);
	Bag operator+(const Bag& source);
	Bag operator-(const Bag& source);
	bool operator==(const Bag& source);
	void removeRepetitions(); // 반복된 항목 제거
	void reverse(); //  가방 목록 순서를 거꾸로 바꾸기
	void sort(); // 가방 목록을 오름차순으로 정렬
private:
	node* head_ptr;
	size_t many_nodes;
};