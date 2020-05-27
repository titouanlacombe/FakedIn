#include "groupe.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1024

groupe* g_open(FILE *db) {
	return NULL;
}

int g_size(groupe* g)
{
	node *tmp;
	int size;

	size = 0;
	tmp = g->personnes;
	while (tmp) {
		if (tmp->data != NULL) {
			size++;
		}
		tmp = l_skip(tmp, 1);
	}
	return size;
}

worker* g_index(groupe* g, int const index) {
	return (worker*)l_skip(g->personnes, index - 1)->data;
}

bool g_friends(groupe* g, int const index_a, int const index_b) {
	worker *a, *b;
	int k;
	a = g_index(g, index_a);
	b = g_index(g, index_b);

	// si a ou b n'existe pas
	if (!a || !b) return false;

	// a aime b
	k = 0;
	while (k < MAX_AMIS && (worker*)l_skip(a->colleagues, k) != b) {
		k++;
	}
	if (k == MAX_AMIS) return false;
	
	// b aime a
	k = 0;
	while (k < MAX_AMIS && (worker*)l_skip(b->colleagues, k) != a) {
		k++;
	}
	if (k == MAX_AMIS) return false;

	return true;
}

worker* g_bestie(groupe* g, int const index) {
	worker *a = g_index(g, index);
	worker *b = (worker*)l_skip(a->colleagues, 0);

	if(!b) return NULL;
	if((worker*)l_skip(b->colleagues, 0) == a) {
		return b;
	}
	return NULL;
}

bool g_oneway(groupe* g, int const index_a, int const index_b) {
	worker *a, *b;
	int k, a_like_b, b_like_a;
	a = g_index(g, index_a);
	b = g_index(g, index_b);

	// a aime b
	k = 0;
	while (k < MAX_AMIS && (worker*)l_skip(a->colleagues, k) != b) {
		k++;
	}
	a_like_b = k != MAX_AMIS;
	
	// b aime a
	k = 0;
	while (k < MAX_AMIS && (worker*)l_skip(b->colleagues, k) != a) {
		k++;
	}
	b_like_a = k != MAX_AMIS;
	
	return (b_like_a && !a_like_b) || (a_like_b && !b_like_a);
}

bool g_linked(groupe* g, int const index_a, int const index_b) {
	node *list, *explored, *tmp;
	worker *p1, *p2, *current;
	int i;

	if (index_a == index_b) return false;

	p1 = g_index(g, index_a);
	p2 = g_index(g, index_b);
	list = l_make_node(p1);
	explored = NULL;

	do {
		current = list->data;
		i = 0;
		while (l_skip(current->colleagues, i)) {
			tmp = list;
			while (tmp && tmp->data != l_skip(current->colleagues, i)) {
				tmp = l_skip(tmp, 1);
			}
			if (!tmp) {
				tmp = explored;
				while (tmp && tmp->data != l_skip(current->colleagues, i)) {
					tmp = l_skip(tmp, 1);
				}
				if (!tmp) {
					l_append(&list, l_make_node(l_skip(current->colleagues, i)));
				}
			}
			i++;
		}
		l_append(&explored, l_make_node(current));
		list = l_skip(list, 1);
	}
	while (list && current != p2);

	return current == p2;
}

int g_distance(groupe* g, int const index_a, int const index_b) {
	node *list, *explored, *tmp, *list_dist, *head_dist;
	worker *p1, *p2, *current;
	int i, *dist, savedist;

	p1 = g_index(g, index_a);
	p2 = g_index(g, index_b);
	list = l_make_node(p1);
	dist = malloc(sizeof(int));
	*dist = 0;
	head_dist = l_make_node(dist);
	list_dist = head_dist;
	explored = NULL;

	do {
		current = list->data;
		if (current != p2) {
			i = 0;
			while (l_skip(current->colleagues, i)) {
				tmp = list;
				while (tmp && tmp->data != l_skip(current->colleagues, i)) {
					tmp = l_skip(tmp, 1);
				}
				if (!tmp) {
					tmp = explored;
					while (tmp && tmp->data != l_skip(current->colleagues, i)) {
						tmp = l_skip(tmp, 1);
					}
					if (!tmp) {
						l_append(&list, l_make_node(l_skip(current->colleagues, i)));
						dist = malloc(sizeof(int));
						*dist = *((int*)list_dist->data) + 1;
						l_append(&list_dist, l_make_node(dist));
					}
				}
				i++;
			}
			l_append(&explored, l_make_node(current));
			list = l_skip(list, 1);
			list_dist = l_skip(list_dist, 1);
		}
	}
	while (list && current != p2);

	if(current == p2) {
		// If found	
		savedist = *((int*)list_dist->data);
		l_free_list(head_dist);
		return savedist;
	}
	else {
		l_free_list(head_dist);
		return -1;
	}
}

void g_remove(groupe* g, int const index) {
	
	return;
}
