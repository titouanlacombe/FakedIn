#pragma once

#include "company.h"

class Job
{
public:
	std::string title; // Title of the job
	List<std::string> skills; // Skills required for the job
	Company* company; // Company who offers the job

	Job();
	Job(std::string _title, Company* _company);
	~Job();
	void add_skill(std::string skill); // Add skill to skills
	friend bool operator==(Job& l, Job& r); // Returns true if l&r have the same title and company
	friend bool operator!=(Job& l, Job& r); // Returns (!l==r)
	friend std::ostream& operator<<(std::ostream& os, const Job& j); // Used to print the job in the console
};

// Search a job in jobs from a title and a company
Job* get_job(Company& c, std::string title);

// Search if a job with the title 'title' and the company 'c' already exist in jobs
bool job_exist(Company& c, std::string title);

// Returns the jobs of the company c
List<Job>* company_jobs(Company& c);

List<Job>& get_jobs();
