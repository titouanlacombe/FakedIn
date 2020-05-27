#pragma once

#include "liste.h"
#include "mylog.h"

typedef struct job
{
  char* name;
	node* skills;
  void* employee;
} job;

typedef struct company
{
  char* name;
  char* email;
  char* zip_code;
  node* jobs;
} company;

// créé une nouvelle entreprise
company* cmp_create(char* name, char* email, char* zip_code);

// supprime c
void cmp_delete(company* c);

// ajoute un poste a pourvoir a c
void cmp_add_job(company* c, char* name, node* skills);

// suprime le poste a pourvoir avec le nom 'name' de c
void cmp_del_job(company* c, char* name);