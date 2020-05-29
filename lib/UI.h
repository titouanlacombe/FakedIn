#pragma once

#include "search.h"

void home();

void pre_company();
void create_cmp();
void company(Company* c);

void pre_wrk(bool emp);
void create_wrk(bool emp);
void employee(Worker* w);
void seeker(Worker* w);

void delete_cmp(Company* c);
void create_job(Company* c);
void delete_job(Company* c);
void search_seeker(Company* c);

void modify_wrk(Worker* w);
void delete_wrk(Worker* w);
void search_job(Worker* w);
void search_wrk(Worker* w);
