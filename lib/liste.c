#include "liste.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

node* l_make_node(void* data)
{
	node *n ;
	n = malloc(sizeof (node));
	n->previous = NULL ;
	n->next = NULL ;
	n->data = data ;
	return(n);
}

void l_free_node(node* n)
{
	if (n->data)
	{
		free(n->data);
	}
	free(n);
	return;
}

void l_free_list(node* n)
{
	while (n->next)
	{
		n = n->next;
		l_free_node(n->previous);
	}
	if (n)
	{
		l_free_node(n);
	}
	return;
}

int l_length(node const* n)
{
	int i ;
	node const *ncopy ;

	i = 0 ;
	if(n)
	{
		i++ ;
		ncopy = n ;
		while(ncopy->next)
		{
			i++ ;
			ncopy = ncopy->next;
		}
		ncopy = n;
		while(ncopy->previous)
		{
			i++ ;
			ncopy = ncopy->previous;
		}
	}
	return i;
}

node* l_head(node* n)
{
	if (n)
	{
		while (n->previous)
		{
			n = n->previous;
		}
		return n;
	}
	else
	{
		return NULL;
	}
}

node* l_tail(node* n)
{
	if (n)
	{
		while (n->next)
		{
			n = n->next;
		}
		return n;
	}
	else
	{
		return NULL;
	}
}

node* l_skip(node* n, int i)
{
	if (i > 0)
	{
		while (n && i > 0)
		{
			i--;
			n = n->next;
		}
	}
	else if (i < 0)
	{
		while (n && i < 0)
		{
			i++;
			n = n->previous;
		}
	}
	
	return n;
}

node* l_append(node** p, node* tail)
{
	node *temp;

	assert(p);

	if (*p)
	{
		temp = *p;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = tail;
		tail->previous = temp;
	}
	else
	{
		*p = tail;
	}

	return tail;
}

node* l_prepend(node** p, node* head)
{
	node *temp;

	assert(p);

	if (*p)
	{
		temp = *p;
		while (temp->previous)
		{
			temp = temp->previous;
		}
		temp->previous = head;
		head->next = temp;
	}
	else
	{
		*p = head;
	}

	return head;
}

node* l_insert(node** p, node* body)
{
	node *temp;

	assert(p);

	if (*p)
	{
		temp = (*p)->next;
		(*p)->next = body;
		body->previous = *p;
		if (temp)
		{
			body->next = temp;
			temp->previous = body;
		}
	}
	else
	{
		*p = body;
	}

	return body;
}

node* l_remove(node* n)
{
	node *temp;

	if (n)
	{
		if (n->previous) n->previous->next = n->next;
		if (n->next) n->next->previous = n->previous;
		
		temp = n->next;
		l_free_node(n);
		return temp;
	}
	else
	{
		return NULL;
	}
}