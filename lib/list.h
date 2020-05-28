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
	void remove(T e);
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
void List<T>::remove(T e)
{
	auto tmp = first;
	while (tmp != NULL && tmp->data != e)
	{
		tmp = tmp->next;
	}
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
