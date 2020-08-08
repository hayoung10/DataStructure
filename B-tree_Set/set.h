#pragma once
#ifndef MAIN_SAVITCH_SET_H
#define MAIN_SAVITCH_SET_H
#include <cstdlib>   // Provides size_t
#include <iostream>
#include <iomanip> // Provides setw
using namespace std;

namespace main_savitch_11
{
	template <class Item>
	class set
	{
	public:
		// TYPEDEFS
		typedef Item value_type;
		// CONSTRUCTORS and DESTRUCTOR
		set();
		set(const set& source);
		~set() { clear(); }
		// MODIFICATION MEMBER FUNCTIONS
		void operator =(const set& source);
		void clear();
		bool insert(const Item& entry);
		size_t erase(const Item& target);
		// CONSTANT MEMBER FUNCTIONS
		size_t count(const Item& target) const;
		bool empty() const { return (data_count == 0); }
		// SUGGESTED FUNCTION FOR DEBUGGING
		void print(int indent) const;
		void show_content();
	private:
		// MEMBER CONSTANTS
		static const size_t MINIMUM = 1;
		static const size_t MAXIMUM = 2 * MINIMUM;
		// MEMBER VARIABLES
		size_t data_count;
		Item data[MAXIMUM + 1];
		size_t child_count;
		set *subset[MAXIMUM + 2];
		// HELPER MEMBER FUNCTIONS
		bool is_leaf() const { return (child_count == 0); }
		bool loose_insert(const Item& entry);
		bool loose_erase(const Item& target);
		void remove_biggest(Item& removed_entry);
		void fix_excess(size_t i);
		void fix_shortage(size_t i);
		// NOTE: The implementor may want to have additional helper functions
		void show_content_help(int indent) const; // help show_content
	};

	template<class Item>
	set<Item>::set() {
		data_count = 0;
		child_count = 0;
		for (int x = 0; x < MAXIMUM + 2; x++)
			subset[x] = NULL;
	}

	template<class Item>
	set<Item>::set(const set<Item>& source) {
		for (size_t x = 0; x < MAXIMUM + 1; x++)
			data[x] = source.data[x];
		for (size_t y = 0; y < MAXIMUM + 2; y++)
			subset[y] = source.subset[y];
		data_count = source.data_count;
		child_count = source.child_count;
	}

	template<class Item>
	void set<Item>::operator=(const set<Item>& source) {
		if (this == &source)
			return;
		clear();
		for (size_t x = 0; x < MAXIMUM + 1; x++)
			data[x] = source.data[x];
		for (size_t y = 0; y < MAXIMUM + 2; y++)
			subset[y] = source.subset[y];
		data_count = source.data_count;
		child_count = source.child_count;
	}

	template<class Item>
	void set<Item>::clear() {
		for (size_t x = 0; x < MAXIMUM + 1; x++)
			data[x] = Item();
		for (size_t y = 0; y < MAXIMUM + 2; y++)
			subset[y] = NULL;
		data_count = 0;
		child_count = 0;
	}

	template<class Item>
	bool set<Item>::insert(const Item& entry) {
		if (!loose_insert(entry)) // (1)
			return false; // since entry wasn't added
		if (data_count > MAXIMUM) { // (2) fix the root of the entire tree
			// create a new root with no entries
			// and let the old root be the child of the new root
			set<Item> *child = new set<Item>;
			for (size_t x = 0; x < data_count; x++)
				child->data[x] = data[x];
			for (size_t y = 0; y < child_count; y++)
				child->subset[y] = subset[y];
			child->child_count = child_count;
			child->data_count = data_count;
			data_count = 0;
			child_count = 1;
			subset[0] = child;
			// call fix_excess on the old root
			fix_excess(0);
		}
		return true; // (3)
	}

	template<class Item>
	size_t set<Item>::erase(const Item& target) {
		if (!loose_erase(target)) // (1)
			return false; // since target wasn't removed
		if ((data_count == 0) && (child_count == 1)) { // (2)
			// fix the root of the entire tree
			size_t k;
			set *root = new set<Item>;
			root = subset[0];
			for (k = 0; k < root->data_count; k++)
				data[k] = root->data[k];
			child_count = root->child_count;
			data_count = root->data_count;
			for (k = 0; k < child_count; k++)
				subset[k] = root->subset[k];
			delete root;
			root = NULL;
		}
		return true; // (3)
	}

	template<class Item>
	size_t set<Item>::count(const Item& target) const {
		size_t i;
		for (i = 0; i < data_count&&data[i] < target; i++); // find the first index i such that data[i]>=target
		if (i < data_count && target == data[i]) // target is found at data[i]
			return 1;
		else if (is_leaf()) // the root has no children
			return 0;
		else
			return subset[i]->count(target);
	}

	template<class Item>
	void set<Item>::print(int indent) const {
		const int INDENT = 4;
		size_t i;
		cout << setw(indent) << "";

		for (i = 0l i < data_count; i++)
			cout << data[i] << " ";
		cout << endl;
		for (i = 0; i < child_count; i++)
			subset[i]->print(indent + INDENT);
	}

	template<class Item>
	void set<Item>::show_content() {
		show_content_help(4);
	}

	template<class Item>
	bool set<Item>::loose_insert(const Item& entry) {
		size_t i; // (1) find the first index i such that data[i]>=entry
		for (i = 0; i < data_count && data[i] < entry; i++);

		if ((i < data_count) && (entry == data[i])) // (2) entry is found at data[i]
			return false;
		if (is_leaf()) { // (3) the root has no children
			for (size_t k = data_count; k > i; k--)
				data[k] = data[k - 1];
			data_count++;
			data[i] = entry; // insert the entry to the root at data[i]
			return true;
		}
		else { // (4) do a recursive call and fix the excess problem
			bool b = subset[i]->loose_insert(entry); // (4.1)
			if (subset[i]->data_count > MAXIMUM) // (4.2)
				fix_excess(i); // (4.3)
			return b; // (4.4)
		}
	}

	template<class Item>
	bool set<Item>::loose_erase(const Item& entry) {
		if (this == NULL)
			return false;
		size_t i; // (1) find first index such that data[index]>=target
		for (i = 0; i < data_count && data[i] < entry; i++);
		
		if ((data[i] != entry) && is_leaf()) // (2a) the root has no child and target not found
			return false;
		if ((data[i] == entry) && is_leaf()) { // (2b) the root has no child and target found
			data_count--;
			for (size_t k = i; k < data_count; k++) // remove the target from the data array
				data[k] = data[k + 1];
			return true;
		}
		else { // (2c,d) the root has children
			if ((data[i] != entry) && !is_leaf()) { // (2c) the root has children and target not found
				subset[i]->loose_erase(entry);
				if (subset[i] != NULL && subset[i]->data_count < MINIMUM)
					fix_shortage(i);
				return true;
			}
			if ((data[i] == entry) && !is_leaf()) { // (2d) the root has children and target found
				subset[i]->remove_biggest(data[i]);
				if (subset[i]->data_count < MINIMUM)
					fix_shortage(i);
				return true;
			}
		}
		return false;
	}

	template<class Item>
	void set<Item>::remove_biggest(Item& removed_entry) {
		if (is_leaf()) { // (1)
			// If the root has no children, copy the last item of data into removed_entry and reduce data_count by 1
			removed_entry = data[data_count - 1];
			data_count--;
		}
		else { // (2)
			// If it has children, remove the biggest item from the rightmost child and call fix_shortage if necessary
			subset[child_count - 1]->remove_biggest(removed_entry);
			if (subset[child_count - 1]->data_count < MINIMUM)
				fix_shortage(child_count - 1);
		}
	}

	template<class Item>
	void set<Item>::fix_excess(size_t i) {
		size_t k;
		for (k = data_count; k > i; k--)
			data[k] = data[k - 1];
		data[i] = subset[i]->data[MINIMUM]; // (2) The entry in the middle is moved upward to the parent
		data_count++;

		// (1) split the node with MAXIMUM+1 entries into two nodes
		//     each of which contains MINIMUM entries.
		set<Item> *left = new set<Item>;
		set<Item> *right = new set<Item>;
		left->data_count = MINIMUM;
		right->data_count = MINIMUM;

		for (k = 0; k < MINIMUM; k++) {
			left->data[k] = subset[i]->data[k];
			right->data[k] = subset[i]->data[k + MINIMUM + 1];
		}
		size_t ch = (subset[i]->child_count) / 2;
		for (k = 0; k < ch; k++) {
			left->subset[k] = subset[i]->subset[k];
			right->subset[k] = subset[i]->subset[k + ch];
		}
		if (ch > 0) {
			left->child_count = MINIMUM + 1;
			right->child_count = MINIMUM + 1;
		}
		subset[child_count] = new set;
		for (k = child_count; k > i; k--)
			subset[k] = subset[k - 1];
		child_count++;
		subset[i] = left;
		subset[i + 1] = right;
	}

	template<class Item>
	void set<Item>::fix_shortage(size_t i) {
		size_t k;
		if (i != 0 && subset[i - 1]->data_count > MINIMUM) { // Case 1
			for (k = subset[i]->data_count; k > 0; k--)
				subset[i]->data[k] = subset[i]->data[k - 1];
			subset[i]->data[0] = data[i - 1]; // (1) Transfer data[i-1] to the front of subset[i]->data
			subset[i]->data_count++;
			// (2) Transfer the final item of subset[i-1]->data up to replace data[i-1]
			//     and reduce subset[i-1]->data_count by 1
			data[i - 1] = subset[i - 1]->data[subset[i - 1]->data_count - 1];
			subset[i - 1]->data_count--;

			// (3) If subset[i-1] has children, transfer the final child of subset[i-1] over to the front of the subset[i]
			if (!(subset[i - 1]->is_leaf())) {
				for (k = subset[i]->child_count; k > 0; k--)
					subset[i]->subset[k] = subset[i]->subset[k - 1];
				subset[i]->subset[0] = subset[i - 1]->subset[subset[i - 1]->child_count - 1];
				subset[i]->child_count++;
				subset[i - 1]->child_count--;
			}
		}
		else if (i != data_count && subset[i + 1]->data_count > MINIMUM) { // Case 2
			subset[i]->data_count++;
			subset[i]->data[subset[i]->data_count - 1] = data[i];
			data[i] = subset[i + 1]->data[0]; // (1) Transfer data[i] to the end of subset[i]->data
			// (2) Transfer the first item of subset[i+1]->data up to replace data[i]
			//     and reduce subset[i+1]->data_count by 1
			for (k = 0; k < subset[i + 1]->data_count; k++)
				subset[i + 1]->data[k] = subset[i + 1]->data[k + 1];
			subset[i + 1]->data_count--;

			// (3) If subset[i] has children, transfer the first child of subset[i+1] over to the end of the subset[i]
			if (!(subset[i + 1]->is_leaf())) {
				subset[i]->subset[subset[i]->child_count] = subset[i + 1]->subset[0];
				subset[i]->child_count++;
				for (k = 0; k < subset[i + 1]->child_count; k++)
					subset[i + 1]->subset[k] = subset[i + 1]->subset[k + 1];
				subset[i + 1]->child_count--;
			}
		}
		else if (i != 0 && subset[i - 1]->data_count == MINIMUM) { // Case 3
			subset[i - 1]->data[subset[i - 1]->data_count] = data[i - 1]; // (1) Move data[i-1] to the end of subset[i]->data
			subset[i - 1]->data_count++;
			for (k = i; k < data_count; k++)
				data[k - 1] = data[k];
			data_count--;
			// (2) Transfer all the items and children of subset[i] to the end of subset[i-1]
			for (k = 0; k < subset[i]->data_count; k++) {
				subset[i - 1]->data[subset[i - 1]->data_count] = subset[i]->data[k];
				subset[i - 1]->data_count++;
			}
			for (k = 0; k < subset[i]->child_count; k++) {
				subset[i - 1]->subset[subset[i - 1]->child_count] = subset[i]->subset[k];
				subset[i - 1]->child_count++;
			}
			// (3) Delete the node subset[i] and shift subset[i+1], subset[i+2], and so on leftward and reduce child_count by 1
			delete subset[i];
			subset[i] = NULL;
			child_count--;
			for (k = i; k < child_count; k++)
				subset[k] = subset[k + 1];
		}
		else if (i != data_count && subset[i + 1]->data_count == MINIMUM) { // Case 4
			subset[i]->data[subset[i]->data_count] = data[i]; // (1) Move data[i] to the end of subset[i]->Data
			subset[i]->data_count++;
			for (k = i; k < data_count; k++)
				data[k] = data[k + 1];
			data_count--;
			// (2) Transfer all the items and children of subset[i+1] to the end of subset[i]
			for (k = 0; k < subset[i + 1]->data_count; k++) {
				subset[i]->data[subset[i]->data_count] = subset[i + 1]->data[k];
				subset[i]->data_count++;
			}
			for (k = 0; k < subset[i + 1]->child_count; k++) {
				subset[i]->subset[subset[i]->child_count] = subset[i + 1]->subset[k];
				subset[i]->child_count++;
			}
			// (3) Delete the node subset[i+1] and shift subset[i+2], subset[i+3], and so on leftward and reduce child_count by 1
			delete subset[i + 1];
			subset[i + 1] = NULL;
			child_count--;
			for (k = i; k < child_count; k++)
				subset[k + 1] = subset[k + 2];
		}
	}

	template<class Item>
	void set<Item>::show_content_help(int indent) const {
		const int INDENT = 4;
		size_t i, j;

		for (i = data_count; i > 0; i--) {
			j = child_count - (data_count - i);
			if (!is_leaf() && j > i) {
				subset[j - 1]->show_content_help(indent + INDENT);
				j--;
			}
			cout << setw(indent) << data[i - 1] << endl;
			if (!is_leaf() && j == 1)
				subset[j - 1]->show_content_help(indent + INDENT);
		}
	}
}
//#include "set.template" // Include the implementation.
#endif