#pragma once

#include "company.h"

class Worker
{
public:
	std::string first_name;
	std::string last_name;
	std::string email;
	std::string zip_code;
	List<std::string> skills; 
	List<Worker*> co_workers;
	Company* company;

	Worker();
	Worker(std::string full_name, std::string _email);
	Worker(std::string _first_name, std::string _last_name, std::string _email);
	~Worker();
	void add_skill(std::string skill); // Add a skill
	void add_co_worker(Worker& co_worker); // Add a co_worker
	void set_zip_code(std::string zip_code); // Modify the zip code
	void set_company(Company* company); // Modify the company
	bool employed() const; // Returns true if company != NULL
	void remove_from_coll(); // Remove himself from the co_workers of his co_workers
	friend bool operator==(Worker& l, Worker& r); // Returns true if l&r have the same first and last name
	friend bool operator!=(Worker& l, Worker& r); // Returns (!l==r)
	friend std::ostream& operator<<(std::ostream& os, const Worker& w); // Used to print the worker in the console
};

// Search a worker by his first and last name
Worker* get_worker(std::string first_name, std::string last_name);

Worker* get_worker(std::string full_name);

// Returns true if a worker already exist with the names 'first_name' and 'last_name'
bool wrk_exist(std::string first_name, std::string last_name);

bool wrk_exist(std::string full_name);

// Returns the employees of the company c
List<Worker*>* company_employees(Company& c);

List<Worker*>& get_workers();
