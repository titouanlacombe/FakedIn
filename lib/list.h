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
	Node<T>* get_node(T e);
	bool has(T e);
	void remove(Node<T>* it);
	void remove(T e);
	void remove(List<T>& l);
	T& operator[](int n);
	//retourne le nombre d'éléments en commun entre deux listes
	int in_common(List<T>& l);
	void delete_data();
	void print();
	void printl();
	Iterator<T> begin() {return Iterator<T>(first);}
	Iterator<T> end() {return Iterator<T>();}
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
void List<T>::print()
{
	auto it = begin();
	while (it != end())
	{
		std::cout << *it << std::endl;
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
	if (it != NULL) std::cout << it->data;
	std::cout << std::endl;
}

void load_list();
