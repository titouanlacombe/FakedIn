#pragma once

#include "search.h"

#define ASCII_ART															       \
"*********************************************   \n" \
"|     ______      __            ______      |   \n" \
"|    / ____/___ _/ /_____  ____/ /  _/___   |   \n" \
"|   / /_  / __ `/ //_/ _ \\/ __  // // __ \\  | \n" \
"|  / __/ / /_/ / ,< /  __/ /_/ // // / / /  |   \n" \
"| /_/    \\__,_/_/|_|\\___/\\__,_/___/_/ /_/   |\n" \
"|                                           |   \n" \
"| Made by: Lacombe, Billet, Veran           |   \n" \
"| Polytech Marseille - Informatique 3A      |   \n" \
"*********************************************   \n" 

void home();
void init_lists(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers);

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
