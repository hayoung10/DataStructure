#pragma once
#include <cstdlib>

class node {
public:
	typedef double value_type;
	node() { data_field = value_type(); link_field = NULL; }
	node(const value_type& init_data, node* init_link);
	void set_data(const value_type& new_data) { data_field = new_data; }
	void set_link(node* new_link) { link_field = new_link; }
	value_type data() const;
	const node* link() const { return link_field; }
	node* link() { return link_field; }
	size_t list_length(const node* head_ptr);
	void list_head_insert(node*& head_ptr, const node::value_type& entry);
	void list_insert(node* previous_ptr, const value_type& entry);
	node* list_search(node* head_ptr, const node::value_type& target);
	const node* list_search(const node* head_ptr, const value_type& target);
	node* list_locate(node* head_ptr, size_t position);
	const node* list_locate(const node* head_ptr, size_t position);
	void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr);
	void list_head_remove(node*& head_ptr);
	void list_remove(node* previous_ptr);
	void list_clear(node*& head_ptr);
private:
	value_type data_field;
	node *link_field;
};