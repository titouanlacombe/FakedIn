#pragma once

#include <iostream>
#include <string>

template <typename T>
class Node
{
public:
	Node* prev; // Previous node (NULL if none)
	Node* next; // Next node (NULL if none)
	T* data; // Data stored

	Node()
	{
		prev = NULL;
		next = NULL;
		data = NULL;
	}
	Node(T* e)
	{
		prev = NULL;
		next = NULL;
		data = e;
	}
	~Node() {return;}
};

template <typename T>
class Iterator { 
public:
	Node<T>* node; // Current node

	Iterator(Node<T>* n = NULL) {node = n;}
	Iterator operator++(int)
	{
		node = node->next;
		return *this;
	}
	T* operator*() {return node->data;} // Return the data stored in the current node
	bool operator!=(Iterator const &it) const {return node != it.node;} // Return false if two iterator are in the same position
};

template <typename T>
class List
{
public:
	Node<T>* first_n; // First node of the list
	Node<T>* last_n; // Last node of the list
	int length; // Length of the list

	List();
	~List();
	bool empty(); // Return true if list is empty
	void clean(); // Empty the list (reset it) (do not delete the data)
	void addlast(T* e); // Add an element at the end of the list
	void addlast(List<T>& l); // Add an list at the end of the list
	int get_pos(T* e); // Returns the position number of data e in the list
	int get_pos(Node<T>* n); // Returns the position number of node n in the list
	Node<T>* get_node(T* e); // Returns the node of data e in the list
	bool has(T* e); // Returns true if the list has the pointer e in it
	bool has_same(T* e); // Returns true if the list has the same element (==) pointed by e
	void remove(Node<T>* n); // Removes the node n from the list
	void remove(T* e); // Removes the element e from the list
	void remove(List<T>& l); // Removes elements in l from the list
	T* operator[](int n); // Returns the data stored in position n
	int in_common(List<T>& l); // Return the number of similarities between this and l
	void delete_data(); // Deletes the data stored in the list
	void print(std::string title = "List", bool single_line = true); // Print the elements
	// Iterators
	Iterator<T> first() {return Iterator<T>(first_n);}
	Iterator<T> last() {return Iterator<T>(last_n);}
	Iterator<T> end() {return Iterator<T>();}

	Node<T>* min(int start = 0, int end = -1); // Returns the minimum in the list
	Node<T>* max(int start = 0, int end = -1); // Returns the maximum in the list
	void sort(List<int>& li, bool ascending = true); // Sorts the list the same way as li
	void sort(bool ascending = true); // Sorts the list (need operator> and < overloaded to work)
};

template <typename T>
List<T>::List()
{
	first_n = NULL;
	last_n = NULL;
	length = 0;
}

template <typename T>
void List<T>::clean()
{
	auto it = first();
	while (it != last())
	{
		it++;
		delete it.node->prev;
	}
	if (it != end()) delete it.node;
	first_n = NULL;
	last_n = NULL;
	length = 0;
}

template <typename T>
List<T>::~List() {clean();}

template <typename T>
bool List<T>::empty() {return length == 0;}

template <typename T>
void List<T>::addlast(T* e)
{
	auto n = new Node<T>(e);
	length++;
	// if list is not empty
	if (last_n != NULL)
	{
		last_n->next = n;
		n->prev = last_n;
		last_n = n;
	}
	else
	{
		first_n = n;
		last_n = n;
	}
}

template <typename T>
void List<T>::addlast(List<T>& l)
{
	auto it = l.first();
	while (it != l.end())
	{
		addlast(*it);
		it++;
	}
}

template <typename T>
int List<T>::get_pos(T* e)
{
	auto it = first();
	int i = 0;
	while (it != end() && *it != e)
	{
		it++;
		i++;
	}
	if (it != end()) return i;
	else return -1;
}

template <typename T>
int List<T>::get_pos(Node<T>* n)
{
	auto it = first();
	int i = 0;
	while (it != end() && it.node != n)
	{
		it++;
		i++;
	}
	if (it != end()) return i;
	else return -1;
}

template <typename T>
Node<T>* List<T>::get_node(T* e)
{
	auto it = first();
	while (it != end() && *it != e) it++;
	return it.node;
}

template <typename T>
bool List<T>::has_same(T* e)
{
	auto it = first();
	while (it != end() && * *it != *e) it++;
	if (it != end()) return true;
	else return false;
}

template <typename T>
bool List<T>::has(T* e) {return (get_node(e) != NULL);}

template <typename T>
void List<T>::remove(Node<T>* n)
{
	if (n == first_n && n == last_n)
	{
		first_n = NULL;
		last_n = NULL;
	}
	else if (n == first_n)
	{
		first_n = n->next;
		first_n->prev = NULL;
	}
	else if (n == last_n)
	{
		last_n = n->prev;
		last_n->next = NULL;
	}
	else
	{
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
	length--;
	delete n;
}

template <typename T>
void List<T>::remove(T* e)
{
	Node<T>* n = get_node(e);
	if (n != NULL) remove(n);
}

template <typename T>
void List<T>::remove(List<T>& l)
{
	auto it = l.first();
	while (it != l.end())
	{
		remove(*it);
		it++;
	}
}

template <typename T>
T* List<T>::operator[](int n)
{
	int i = 0;
	auto it = first();
	while (it != end() && i < n)
	{
		i++;
		it++;
	}
	if (it.node) return it.node->data;
	else return NULL;
}

template <typename T>
int List<T>::in_common(List<T>& l)
{
	auto it = l.first();
	int n = 0;

	while (it != l.end())
	{
		if (has_same(*it)) n++;
		it++;
	}
	return n;
}

template <typename T>
void List<T>::delete_data()
{
	auto it = first();
	while (it != end())
	{
		delete *it;
		it++;
	}
}

template <typename T>
void List<T>::print(std::string title, bool single_line)
{
	auto it = first();
	if (single_line)
	{
		std::cout << title << ": ";
		while (it != last())
		{
			std::cout << *(*it) << ", ";
			it++;
		}
		if (it != end()) std::cout << *(*it);
		std::cout << std::endl;
	}
	else
	{
		std::cout << title << ":" << std::endl;
		while (it != end())
		{
			std::cout << " - " << *(*it) << std::endl;
			it++;
		}
	}
}

template <typename T>
Node<T>* List<T>::min(int start, int end)
{
	if (end == -1) end = length;
	
	int i;
	Node<T>* m;
	auto it = first();
	for (i = 0; i < start; i++) it++;
	m = it.node;
	while (i < end)
	{
		if (*it < m->data) m = it.node; 
		i++;
		it++;
	}
	return m;
}

template <typename T>
Node<T>* List<T>::max(int start, int end)
{
	if (end == -1) end = length;
	
	int i;
	Node<T>* m;
	auto it = first();
	for (i = 0; i < start; i++) it++;
	m = it.node;
	while (i < end)
	{
		if (*it > m->data) m = it.node;
		i++;
		it++;
	}
	return m;
}

template <typename T>
void swap_data(Node<T>* a, Node<T>* b)
{
	T *tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

template <typename T>
void List<T>::sort(List<int>& li, bool ascending)
{
	auto curent_pos = first();
	auto curent_pos_int = li.first();
	Node<int> *extrema_node;
	while (curent_pos != end())
	{
		// Find extrema
		auto extrema_it = Iterator<int>(curent_pos_int.node);
		extrema_node = extrema_it.node;
		if (ascending)
		{
			while (extrema_it != li.end())
			{
				if (* *extrema_it < *extrema_node->data) extrema_node = extrema_it.node;
				extrema_it++;
			}
		}
		else
		{
			while (extrema_it != li.end())
			{
				if (* *extrema_it > *extrema_node->data) extrema_node = extrema_it.node;
				extrema_it++;
			}
		}

		// Find extrema on main list
		int minmax_pos = li.get_pos(extrema_node);
		int count = 0;
		auto tmp_it = first();
		while (tmp_it != end() && count < minmax_pos)
		{
			tmp_it++;
			count++;
		}
		
		// swap and update
		swap_data(curent_pos_int.node, extrema_node);
		swap_data(curent_pos.node, tmp_it.node);

		curent_pos++;
		curent_pos_int++;
	}
}

template <typename T>
void List<T>::sort(bool ascending)
{
	auto curent_pos = first();
	Node<int> *extrema_node;
	while (curent_pos != end())
	{
		// Find extrema
		auto extrema_it = Iterator<int>(curent_pos.node);
		extrema_node = extrema_it.node;
		if (ascending)
		{
			while (extrema_it != end())
			{
				if (* *extrema_it < *extrema_node->data) extrema_node = extrema_it.node;
				extrema_it++;
			}
		}
		else
		{
			while (extrema_it != end())
			{
				if (* *extrema_it > *extrema_node->data) extrema_node = extrema_it.node;
				extrema_it++;
			}
		}

		// swap and update
		swap_data(curent_pos.node, extrema_node);
		curent_pos++;
	}
}
