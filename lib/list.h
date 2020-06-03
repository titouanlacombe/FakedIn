#pragma once

#include "mylog.h"

template <typename T>
class Node
{
public:
	Node *prev;
	Node *next;
	T data;

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
	Node<T> *node;

	Iterator(Node<T>* n = NULL) {node = n;}
	Iterator operator++(int)
	{
		node = node->next;
		return *this;
	}
	T operator*() {return node->data;}
	bool operator!=(Iterator const &it) const {return node != it.node;}
};

template <typename T>
class List
{
public:
	Node<T> *first;
	Node<T> *last;
	int length;

	List();
	~List();
	void empty();
	// void addfirst(T e);
	void addlast(T e);
	int get_pos(T e);
	int get_pos(Node<T>& n);
	Node<T>* get_node(T e);
	bool has(T e);
	void remove(Node<T>* it);
	void remove(T e);
	void remove(List<T>& l);
	T& operator[](int n);
	//retourne le nombre d'éléments en commun entre deux listes
	int in_common(List<T>& l);
	void delete_data();
	void print(bool ptr = false);
	void printl();
	Iterator<T> begin() {return Iterator<T>(first);}
	Iterator<T> end() {return Iterator<T>();}
	Node<T>* min(int start = 0, int end = -1);
	void sort(List<int>& li);
	void sort();
};

template <typename T>
List<T>::List()
{
	first = NULL;
	last = NULL;
	length = 0;
}

template <typename T>
List<T>::~List()
{
	auto it = first;
	while (it != last)
	{
		it = it->next;
		delete it->prev;
	}
	if (it != NULL) delete it;
}

template <typename T>
void List<T>::empty()
{
	auto it = first;
	while (it != last)
	{
		it = it->next;
		delete it->prev;
	}
	if (it != NULL) delete it;
	first = NULL;
	last = NULL;
	length = 0;
}

template <typename T>
void List<T>::addlast(T e)
{
	auto n = new Node<T>(e);
	length++;
	// if list is not empty
	if (last != NULL)
	{
		last->next = n;
		n->prev = last;
		last = n;
	}
	else
	{
		first = n;
		last = n;
	}
}

template <typename T>
int List<T>::get_pos(T e)
{
	auto it = begin();
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
	auto it = begin();
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
	auto it = begin();
	while (it != end() && *it != e) it++;
	return it.node;
}

template <typename T>
bool List<T>::has(T e) {return (get_node(e) != NULL);}

template <typename T>
void List<T>::remove(Node<T>* it)
{
	if (it == first && it == last)
	{
		first = NULL;
		last = NULL;
	}
	else if (it == first)
	{
		first = it->next;
		first->prev = NULL;
	}
	else if (it == last)
	{
		last = it->prev;
		last->next = NULL;
	}
	else
	{
		it->prev->next = it->next;
		it->next->prev = it->prev;
	}
	length--;
	delete it;
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
	auto it = l.begin();
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
	auto it = first;
	while (it != NULL && i < n)
	{
		i++;
		it = it->next;
	}
	return it->data;
}

template <typename T>
int List<T>::in_common(List<T>& l)
{
	auto it = l.begin();
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
	auto it = begin();
	while (it != end())
	{
		delete *it;
		it++;
	}
}

template <typename T>
void List<T>::print(bool ptr)
{
	auto it = begin();
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
	auto it = first;
	while (it != last) {
		std::cout << it->data << ", ";
		it = it->next;
	}
	if (it != NULL)
	{
		std::cout << it->data;
	}
	std::cout << std::endl;
}

template <typename T>
Node<T>* List<T>::min(int start, int end)
{
	if (end == -1) end = length;
	int i;
	Node<T>* m;
	auto it = begin();
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
void swap_node(Node<T>& a, Node<T>& b)
{
	T tmp = a.data;
	a.data = b.data;
	b.data = tmp;
}

template <typename T>
void List<T>::sort(List<int>& li)
{
	int start = 0, i, j;
	auto it_T = begin();
	auto it_i = li.begin();
	Node<T> *max_T;
	Node<int> *max_i;
	while (it_i != li.end())
	{
		max_i = li.min(start);
		i = li.get_pos(*max_i);
		j = 0;
		max_T = first;
		while (max_T != NULL && j < i)
		{
			max_T = max_T->next;
			j++;
		}
		
		swap_node(*(it_T.node), *max_T);
		swap_node(*(it_i.node), *max_i);
		it_T++;
		it_i++;
		start++;
	}
}

template <typename T>
void List<T>::sort()
{
	int start = 0;
	auto it = begin();
	Node<T> *m;
	while (it != end())
	{
		m = min(start);
		swap_node(*(it.node), *m);
		it++;
		start++;
	}
}

void load_list();
