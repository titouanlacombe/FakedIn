#include "groupe.h"

#include "liste.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1024

groupe* g_open(FILE *db) {
	groupe *g;
	personne *p;
	node *maillon_p, *head_p, *maillon_amis, *head_amis;
	char line[MAX_LINE_LENGTH];
	char tmp[MAX_LINE_LENGTH];
	int k, i, j;
	int *amis;

	g = malloc(sizeof(groupe));
	maillon_amis = 0;
	fgets(line, MAX_LINE_LENGTH, db);  // Premiere ligne labels
	while (fgets(line, MAX_LINE_LENGTH, db)) {
		p = malloc(sizeof(personne));
		for (i = 0; i < MAX_AMIS; i++) {
			p->amis[i] = NULL;
		}
		

		i = 0;
		// index setup
		k = 0;
		while (line[i] != ',') {
			tmp[k] = line[i];
			k++;
			i++;
		}
		tmp[k] = '\0';
		i++;
		p->index = atoi(tmp);
		
		// nom setup
		k = 0;
		while (line[i] != ',') {
			p->nom[k] = line[i];
			k++;
			i++;
		}
		p->nom[k] = '\0';
		i++;
		
		// prenom setup
		k = 0;
		while (line[i] != ',') {
			p->prenom[k] = line[i];
			k++;
			i++;
		}
		p->prenom[k] = '\0';
		i++;
		
		// courriel setup
		k = 0;
		while (line[i] != ',') {
			p->courriel[k] = line[i];
			k++;
			i++;
		}
		p->courriel[k] = '\0';
		i++;
		
		// telephone setup
		k = 0;
		while (line[i] != ',') {
			p->telephone[k] = line[i];
			k++;
			i++;
		}
		p->telephone[k] = '\0';
		i++;
		
		// adresse setup
		k = 0;
		while (line[i] != ',') {
			p->adresse[k] = line[i];
			k++;
			i++;
		}
		p->adresse[k] = '\0';
		i++;
		

		// save amis for later
		j = 0;
		amis = malloc(6*sizeof(int));
		while (line[i] != '\0') {
			k = 0;
			while (line[i] != ';' && line[i] != '\0') {
				tmp[k] = line[i];
				k++;
				i++;
			}
			tmp[k] = '\0';
			if (line[i] != '\0') {
				i++;
			}
			amis[j] = atoi(tmp);
			j++;
		}
		amis[j] = -1;
		l_append(&maillon_amis, l_make_node(amis));

		// Constructing group
		l_append(&g->personnes, l_make_node(p));
	}

	// amis setup
	head_p = l_head(g->personnes);
	maillon_p = head_p;
	head_amis = l_head(maillon_amis);
	maillon_amis = head_amis;
	while (maillon_p) {
		k = 0;
		while ((j = ((int*)maillon_amis->data)[k]) != -1) {
			((personne*)maillon_p->data)->amis[k] = (personne*)l_skip(head_p, j-1)->data;
			k++;
		}
		maillon_p = l_skip(maillon_p, 1);
		maillon_amis = l_skip(maillon_amis, 1);
	}
	l_free_list(head_amis);

	return g;
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

personne* g_index(groupe* g, int const index) {
	return (personne*)l_skip(g->personnes, index - 1)->data;
}

bool g_friends(groupe* g, int const index_a, int const index_b) {
	personne *a, *b;
	int k;
	a = g_index(g, index_a);
	b = g_index(g, index_b);

	// si a ou b n'existe pas
	if (!a || !b) return false;

	// a aime b
	k = 0;
	while (k < MAX_AMIS && a->amis[k] != b) {
		k++;
	}
	if (k == MAX_AMIS) return false;
	
	// b aime a
	k = 0;
	while (k < MAX_AMIS && b->amis[k] != a) {
		k++;
	}
	if (k == MAX_AMIS) return false;

	return true;
}

int g_bestie(groupe* g, int const index) {
	personne *a = g_index(g, index);
	personne *b = a->amis[0];

	if(!b) return -1;
	if(b->amis[0] == a) {
		return b->index;
	}
	else {
		return -1;
	}
}

bool g_oneway(groupe* g, int const index_a, int const index_b) {
	personne *a, *b;
	int k, a_like_b, b_like_a;
	a = g_index(g, index_a);
	b = g_index(g, index_b);

	// a aime b
	k = 0;
	while (k < MAX_AMIS && a->amis[k] != b) {
		k++;
	}
	a_like_b = k != MAX_AMIS;
	
	// b aime a
	k = 0;
	while (k < MAX_AMIS && b->amis[k] != a) {
		k++;
	}
	b_like_a = k != MAX_AMIS;
	
	return (b_like_a && !a_like_b) || (a_like_b && !b_like_a);
}

bool g_linked(groupe* g, int const index_a, int const index_b) {
	node *list, *explored, *tmp;
	personne *p1, *p2, *current;
	int i;

	if (index_a == index_b) return false;

	p1 = g_index(g, index_a);
	p2 = g_index(g, index_b);
	list = l_make_node(p1);
	explored = NULL;

	do {
		current = list->data;
		i = 0;
		while (current->amis[i]) {
			// if (current->amis[i] not in explored && current->amis[i] not in list)
			tmp = list;
			while (tmp && tmp->data != current->amis[i]) {
				tmp = l_skip(tmp, 1);
			}
			if (!tmp) {
				// current->amis[i] not in list
				tmp = explored;
				while (tmp && tmp->data != current->amis[i]) {
					tmp = l_skip(tmp, 1);
				}
				if (!tmp) {
					// current->amis[i] not in explored
					l_append(&list, l_make_node(current->amis[i]));
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
	personne *p1, *p2, *current;
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
			while (current->amis[i]) {
				// if (current->amis[i] not in explored && current->amis[i] not in list)
				tmp = list;
				while (tmp && tmp->data != current->amis[i]) {
					tmp = l_skip(tmp, 1);
				}
				if (!tmp) {
					// current->amis[i] not in list
					tmp = explored;
					while (tmp && tmp->data != current->amis[i]) {
						tmp = l_skip(tmp, 1);
					}
					if (!tmp) {
						// current->amis[i] not in explored
						l_append(&list, l_make_node(current->amis[i]));
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
	personne *p, *p_tmp;
	node *tmp;
	int i, j;

	p = g_index(g, index);

	// Remove from friends
	tmp = g->personnes;
	while (tmp) {
		i = 0;
		p_tmp = tmp->data;
		while (p_tmp->amis[i]) {
			if (p_tmp->amis[i] == p) {
				// Delete
				for (j = i; j < MAX_AMIS-1; j++) {
					p_tmp->amis[j] = p_tmp->amis[j+1];
				}
				p_tmp->amis[j] = NULL;
				i--;
			}
			i++;
		}
		tmp = l_skip(tmp, 1);
	}

	// Remove from list
	// free(p);
	tmp = l_skip(g->personnes, index - 1);
	tmp->data = NULL;
	return;
}
