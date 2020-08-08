#include "node.h"
#include <cassert> // provide assert
node::value_type;

node::node(const value_type& init_data, node* init_link) {
	data_field = init_data;
	link_field = init_link;
}

size_t node::list_length(const node* head_ptr) {
	size_t answer = 0;
	const node *cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
		++answer;
	return answer;
}

node::value_type node::data() const { return data_field; }

void node::list_head_insert(node*& head_ptr, const node::value_type& entry) {
	head_ptr = new node(entry, head_ptr);
}

void node::list_insert(node* previous_ptr, const value_type& entry) {
	node* insert_ptr;
	insert_ptr = new node(entry, previous_ptr->link());
	previous_ptr->set_link(insert_ptr);
}

node* node::list_search(node* head_ptr, const node::value_type& target) {
	node* cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
		if (target == cursor->data())
			return cursor;
	return NULL;
}

const node* node::list_search(const node* head_ptr, const node::value_type& target) {
	const node* cursor;
	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
		if (target == cursor->data())
			return cursor;
	return NULL;
}

node* node::list_locate(node* head_ptr, size_t position) {
	// precondition: position > 0
	node* cursor = head_ptr;
	size_t i;
	assert(0 < position);
	for (i = 1; (cursor != NULL && i < position); ++i)
		cursor = cursor->link();
	return cursor;
}

const node* node::list_locate(const node* head_ptr, size_t position) {
	// precondition: position > 0
	const node* cursor = head_ptr;
	size_t i;
	assert(0 < position);
	for (i = 1; (cursor != NULL && i < position); ++i)
		cursor = cursor->link();
	return cursor;
}

void node::list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr) {
	head_ptr = NULL; tail_ptr = NULL;
	if (source_ptr == NULL) return;
	list_head_insert(head_ptr, source_ptr->data());
	tail_ptr = head_ptr;
	source_ptr = source_ptr->link();
	while (source_ptr != NULL) {
		list_insert(tail_ptr, source_ptr->data());
		tail_ptr = tail_ptr->link();
		source_ptr = source_ptr->link();
	}
}

void node::list_head_remove(node*& head_ptr) {
	node* remove_ptr;
	remove_ptr = head_ptr;
	head_ptr = head_ptr->link();
	delete remove_ptr;
}

void node::list_remove(node* previous_ptr) {
	node* remove_ptr;
	remove_ptr = previous_ptr->link();
	previous_ptr->set_link(remove_ptr->link());
	delete remove_ptr;
}

void node::list_clear(node*& head_ptr) {
	while (head_ptr != NULL)
		list_head_remove(head_ptr);
}