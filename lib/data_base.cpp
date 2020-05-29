#include "data_base.h"

#define CMP_FILE_NAME "/Companies.csv"
#define JOB_FILE_NAME "/Jobs.csv"
#define EMP_FILE_NAME "/Employees.csv"
#define SKR_FILE_NAME "/Seekers.csv"

void load(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder)
{
	std::ofstream cmp_file, job_file, emp_file, skr_file;
	// int id;

	cmp_file.open("./" + folder + CMP_FILE_NAME, std::ios::in);
	job_file.open("./" + folder + JOB_FILE_NAME, std::ios::in);
	emp_file.open("./" + folder + EMP_FILE_NAME, std::ios::in);
	skr_file.open("./" + folder + SKR_FILE_NAME, std::ios::in);

	// Loading companies
	// std::string line, name, zip_code, email;
	// cmp_file >> line;
	// std::cout << line;
	// int id;
	// while (std::ios::getline(cmp_file, line))
	// {
	// 	std::cout << line << std::endl;
		
	// 	// companies->addlast(new Company(name, zip_code, email));
	// 	// cmp_id.addlast(id);
	// }

	// Loading jobs
	// Loading employees
}

void save(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder)
{
	std::ofstream cmp_file, job_file, emp_file, skr_file;
	int id;

	cmp_file.open("./" + folder + CMP_FILE_NAME, std::ios::out);
	job_file.open("./" + folder + JOB_FILE_NAME, std::ios::out);
	emp_file.open("./" + folder + EMP_FILE_NAME, std::ios::out);
	skr_file.open("./" + folder + SKR_FILE_NAME, std::ios::out);

	// Saving companies
	auto cmp_it = companies->first;
	id = 0;
	cmp_file << "id,name,zip code,email\n";
	while (cmp_it != NULL)
	{
		// id,name,zip code,email
		cmp_file << id << ","
		<< cmp_it->data->name << ","
		<< cmp_it->data->zip_code << ","
		<< cmp_it->data->email << std::endl;
		cmp_it = cmp_it->next;
		id++;
	}
	
	// Saving jobs
	auto job_it = jobs->first;
	id = 0;
	job_file << "id,title,skills,company\n";
	while (job_it != NULL)
	{
		// id,title
		job_file << id << "," <<
		job_it->data->title << ",";

		// Skills
		auto skl_it = job_it->data->skills->first;
		while (skl_it != job_it->data->skills->last)
		{
			job_file << skl_it->data << ";";
			skl_it = skl_it->next;
		}
		job_file << skl_it->data << ",";
		
		// Company id
		job_file << companies->get_pos(job_it->data->company) << std::endl;

		job_it = job_it->next;
		id++;
	}
	
	// Saving workers
	auto wrk_it = workers->first;
	id = 0;
	emp_file << "id,first name,last name,email,zip code,skills,colleagues,company\n";
	skr_file << "id,first name,last name,email,zip code,skills,colleagues\n";
	while (wrk_it != NULL)
	{
		// id,first name,last name,email,zip code
		if (wrk_it->data->employed())
		{
			emp_file << id << ","
			<< wrk_it->data->first_name << ","
			<< wrk_it->data->last_name << ","
			<< wrk_it->data->email << ","
			<< wrk_it->data->zip_code << std::endl;
		}
		else
		{
			skr_file << id << ","
			<< wrk_it->data->first_name << ","
			<< wrk_it->data->last_name << ","
			<< wrk_it->data->email << ","
			<< wrk_it->data->zip_code << std::endl;
		}
		
		// Skills
		auto skl_it2 = wrk_it->data->skills->first;
		while (skl_it2 != wrk_it->data->skills->last)
		{
			if (wrk_it->data->employed()) emp_file << skl_it2->data << ";";
			else skr_file << skl_it2->data << ";";

			skl_it2 = skl_it2->next;
		}
		if (wrk_it->data->employed()) emp_file << skl_it2->data << ",";
		else skr_file << skl_it2->data << ",";
		
		// colleagues
		auto coll_it = wrk_it->data->colleagues->first;
		while (coll_it != wrk_it->data->colleagues->last)
		{
			if (wrk_it->data->employed()) emp_file << workers->get_pos(coll_it->data) << ";";
			else skr_file << workers->get_pos(coll_it->data) << ";";

			coll_it = coll_it->next;
		}
		if (wrk_it->data->employed()) emp_file << workers->get_pos(coll_it->data) << ",";
		else skr_file << workers->get_pos(coll_it->data) << ",";
		
		// company
		if (wrk_it->data->employed()) emp_file << companies->get_pos(wrk_it->data->company) << std::endl;
		else skr_file << std::endl;

		wrk_it = wrk_it->next;
		id++;
	}
}
