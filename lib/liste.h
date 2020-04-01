#pragma once

typedef struct node
{
    void *data;
    struct node *next;
    struct node *previous;
} node;

// Crée une nouvelle node avec node->data affecté de data et node->next affecté de NULL. Retourne cette nouvelle node.
node* l_make_node(void* data);

// Libère la mémoire allouée pour une node. Si n->data est non-NULL, libère la mémoire allouée pour n->data.
void l_free_node(node* n);

// Libère la mémoire allouée pour la node n et toute les nodes suivantes.
void l_free_list(node* n);

// Retourne la longueur de la liste.
// 1. l_length(NULL) => 0
// 2. {a->NULL}, l_length(a) => 1
// 3. {a->b->c->d->NULL}, l_length(a) => 4
// 4. {a->b->c->d->NULL}, l_length(c) => 4
int l_length(node const* n);

// Retourne la première node de la liste si n est non-NULL, sinon retourne NULL.
// 1. l_head(NULL) => NULL
// 2. {a->NULL}, l_head(a) => a
// 3. {a->b->c->d->NULL}, l_head(a) => a
// 4. {a->b->c->d->NULL}, l_head(c) => a
node* l_head(node* n);

// Retourne la dernière node si n est non-NULL, sinon retourne NULL.
// 1. l_last(NULL) => NULL
// 2. {a->NULL}, l_last(a) => a
// 3. {a->b->c->d->NULL}, l_last(a) => d
// 4. {a->b->c->d->NULL}, l_last(c) => d
node* l_tail(node* n);

// Retourne n avancé (ou reculé) de i nodes s'il y a i autres nodes, sinon retourne NULL.
// 1. l_skip(NULL, /* n'importe quoi */) => NULL
// 2. {a->NULL}, l_skip(a, 0) => a
// 3. {a->NULL}, l_skip(a, 1) => NULL
// 4. {a->NULL}, l_skip(a, -1) => NULL
// 5. {a->NULL}, l_skip(a, 2) => NULL
// 6. {a->b->c->d->NULL}, l_skip(a, 1) => b
// 7. {a->b->c->d->NULL}, l_skip(a, 3) => d
// 8. {a->b->c->d->NULL}, l_skip(a, /* i >= 4 */) => NULL
// 9. {a->b->c->d->NULL}, l_skip(c, 1) => d
// 10. {a->b->c->d->NULL}, l_skip(d, /* i <= -4 */) => NULL
node* l_skip(node* n, int i);

// Ajoute une node à la fin de la liste. Si la liste est vide, cette node constitue la liste. Retourne cette node.
// 1. p->{NULL}, l_append(p, a) => a {a->NULL}
// 2. {a->NULL}, l_append(a, b) => b {a->b->NULL}
// 3. {a->b->NULL}, l_append(a, c) => c {a->b->c->NULL}
node* l_append(node** p, node* tail);

// Ajoute une node au début de la liste. Si la liste est vide, cette node constitue la liste. Retourne cette node.
// 1. p->{NULL} l_prepend(p, a) => a {a->NULL}
// 2. {a->NULL}, l_prepend(&a, b) => b {b->a->NULL}
// 3. {a->b->NULL}, l_prepend(&a, c) => c {c->a->b->NULL}
node* l_prepend(node** p, node* head);

// Ajoute une node après *p si *p est non-NULL. Si *p est NULL, cette node constitue la liste. Retourne cette node.
// 1. p->{NULL} l_insert(p, a) => a {a->NULL}
// 2. {a->NULL}, l_insert(&a, b) => b {a->b->NULL}
// 3. {a->b->NULL}, l_insert(&a, c) => c {a->c->b->NULL}
node* l_insert(node** p, node* body);

// Retire une node de la liste et libère sa mémoire allouée. Retourne la node suivant n.
// 1. l_remove(NULL) => NULL
// 2. {a->NULL}, l_remove(a) => NULL {NULL}
// 3. {a->b->NULL}, l_remove(a) => b {b->NULL}
// 4. {a->b->c->NULL}, l_remove(a) => b {b->c->NULL}
// 5. {a->b->c->NULL}, l_remove(b) => c {a->c->NULL}
// 6. {a->b->c->NULL}, l_remove(c) => NULL {a->b->NULL}
// 7. {a->b->c->NULL}, l_remove(l_remove(a)) => c {c->NULL}
node* l_remove(node* n);
