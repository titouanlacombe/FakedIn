#pragma once

#include "mylog.h"

template <typename T>
class Node
{
public:
	Node *prev; // Previous node (NULL if none)
	Node *next; // Next node (NULL if none)
	T data; // Data stored

	Node(T e)
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
	Node<T> *node; // Current node

	Iterator(Node<T>* n = NULL) {node = n;}
	Iterator operator++(int) // Iterate over the list
	{
		node = node->next;
		return *this;
	}
	T operator*() {return node->data;} // Return the data stored in the current node
	bool operator!=(Iterator const &it) const {return node != it.node;} // Return false if two iterator are in the same position
};

template <typename T>
class List
{
public:
	Node<T> *first_n; // First node of the list
	Node<T> *last_n; // Last node of the list
	int length; // Length of the list

	List();
	~List();
	void empty(); // Empty the list (reset it) (do not delete the data)
	// void addfirst(T e); // Add an element at the begining of the list
	void addlast(T e); // Add an element at the end of the list
	void addlast(List<T>& l); // Add an list at the end of the list
	int get_pos(T e); // Returns the position number of data e in the list
	int get_pos(Node<T>& n); // Returns the position number of node n in the list
	Node<T>* get_node(T e); // Returns the node of data e in the list
	bool has(T e); // Returns true if the list has the element e in it
	void remove(Node<T>* n); // Removes the node n from the list
	void remove(T e); // Removes the element e from the list
	void remove(List<T>& l); // Removes elements in l from the list
	T& operator[](int n); // Returns the data stored in position n
	int in_common(List<T>& l); // Return the number of similarities between this and l
	void delete_data(); // Deletes the data stored in the list
	void print(bool ptr = false); // Print one element each line
	void printl(); // Print all elements in one line
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
List<T>::~List()
{
	auto it = first();
	while (it != last())
	{
		it++;
		delete it.node->prev;
	}
	if (it != end()) delete it.node;
}

template <typename T>
void List<T>::empty()
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
void List<T>::addlast(T e)
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
int List<T>::get_pos(T e)
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
int List<T>::get_pos(Node<T>& n)
{
	auto it = first();
	int i = 0;
	while (it != end() && it.node != &n)
	{
		it++;
		i++;
	}
	if (it != end()) return i;
	else return -1;
}

template <typename T>
Node<T>* List<T>::get_node(T e)
{
	auto it = first();
	while (it != end() && *it != e) it++;
	return it.node;
}

template <typename T>
bool List<T>::has(T e) {return (get_node(e) != NULL);}

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
void List<T>::remove(T e)
{
	auto n = get_node(e);
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
T& List<T>::operator[](int n)
{
	int i = 0;
	auto it = first();
	while (it != end() && i < n)
	{
		i++;
		it++;
	}
	return it.node->data;
}

template <typename T>
int List<T>::in_common(List<T>& l)
{
	auto it = l.first();
	int n = 0;

	while (it != l.end())
	{
		if (has(*it)) n++;
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
void List<T>::print(bool ptr)
{
	auto it = first();
	while (it != end())
	{
		if (ptr) std::cout << " - " << *(*it) << std::endl;
		else std::cout << " - " << *it << std::endl;
		it++;
	}
}

template <typename T>
void List<T>::printl()
{
	auto it = first();
	while (it != last())
	{
		std::cout << *it << ", ";
		it++;
	}
	if (it != end()) std::cout << *it;
	std::cout << std::endl;
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
void swap_node(Node<T>& a, Node<T>& b)
{
	T tmp = a.data;
	a.data = b.data;
	b.data = tmp;
}

template <typename T>
void List<T>::sort(List<int>& li, bool ascending)
{
	int start = 0, pos, k;
	auto it_T = first();
	auto it_i = li.first();
	Node<int> *m_i;
	while (it_i != li.end())
	{
		if (ascending) m_i = li.min(start);
		else m_i = li.max(start);
		pos = li.get_pos(*m_i);
		auto m_T = first();
		k = 0;
		while (m_T != end() && k < pos)
		{
			m_T++;
			k++;
		}
		
		swap_node(*(it_T.node), *(m_T.node));
		swap_node(*(it_i.node), *m_i);
		it_T++;
		it_i++;
		start++;
	}
}

template <typename T>
void List<T>::sort(bool ascending)
{
	int start = 0;
	auto it = first();
	Node<T> *m;
	while (it != end())
	{
		if (ascending) m = min(start);
		else m = max(start);
		swap_node(*(it.node), *m);
		it++;
		start++;
	}
}
