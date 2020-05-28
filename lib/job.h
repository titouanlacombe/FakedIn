#pragma once

#include "company.h"

typedef struct job
{
	char* name;
	List<char*>* skills;
	Company* c;
} job;

// créé un nouveau job
job* job_create(char* name, List<char*>* skills, Company* c);

// supprime j
void job_delete(job* j);
