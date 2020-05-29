#pragma once

#include "mylog.h"

template <typename T>
class Node
{
public:
	Node *prev;
	Node *next;
	T data;

	Node(T e);
	~Node();
};

template <typename T>
Node<T>::Node(T e)
{
	prev = NULL;
	next = NULL;
	data = e;
}

template <typename T>
Node<T>::~Node()
{
	return;
}

template <typename T>
class List
{
public:
	Node<T> *first;
	Node<T> *last;
	int length;

	List();
	~List();
	// void addfirst(T e);
	void addlast(T e);
	int get_pos(T e);
	Node<T>* get_node(T e);
	void remove(T e);
	void remove(Node<T>* tmp);
	List<T>& operator-=(List<T>& l);
	T& operator[](int n);
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
	auto tmp = first;
	while (tmp != last)
	{
		tmp = tmp->next;
		delete tmp->prev;
	}
	if (tmp != NULL) delete tmp;
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
	auto tmp = first;
	int i = 0;
	while (tmp != NULL && tmp->data != e)
	{
		tmp = tmp->next;
		i++;
	}
	if (tmp != NULL) return i;
	else return -1;
}

template <typename T>
Node<T>* List<T>::get_node(T e)
{
	auto tmp = first;
	while (tmp != NULL && tmp->data != e)
	{
		tmp = tmp->next;
	}
	return tmp;
}

template <typename T>
void List<T>::remove(T e)
{
	auto n = get_node(e);
	remove(n);
}

template <typename T>
void List<T>::remove(Node<T>* tmp)
{
	if (tmp == first && tmp == last)
	{
		first = NULL;
		last = NULL;
	}
	else if (tmp == first)
	{
		first = tmp->next;
		first->prev = NULL;
	}
	else if (tmp == last)
	{
		last = tmp->prev;
		last->next = NULL;
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	length--;
	delete tmp;
}

template <typename T>
List<T>& List<T>::operator-=(List<T>& l)
{
	auto tmp = l.first;
	while (tmp != NULL)
	{
		remove(tmp->data);
		tmp = tmp->next;
	}
}

template <typename T>
T& List<T>::operator[](int n)
{
	int i = 0;
	auto tmp = first;
	while (tmp != NULL && i < n)
	{
		i++;
		tmp = tmp->next;
	}
	return tmp->data;
}
