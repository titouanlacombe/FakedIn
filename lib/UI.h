#pragma once

#include "mylog.h"
#include "language.h"
#include "search.h"

// Home menu
void home();

// Company menus
void pre_company();
void create_company();
void login_company();
void company_menu(Company& c);
void search_worker(Company& c);
void create_job(Company& c);
void delete_job(Company& c);
void delete_company(Company& c);

// Workers menus
void pre_worker();
void create_worker();
void login_worker();
void worker_menu(Worker& w);
void search_coll(Worker& w);
void search_job(Worker& w);
void modify_worker(Worker& w);
void delete_worker(Worker& w);
