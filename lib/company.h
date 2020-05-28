#pragma once

#include "list.h"

typedef struct company
{
	char* name;
	char* zip_code;
	char* email;
} company;

// créé une nouvelle entreprise
company* cmp_create(char* name, char* zip_code, char* email);

// supprime c
void cmp_delete(company* c);
