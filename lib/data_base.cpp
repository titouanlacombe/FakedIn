#include "data_base.h"

#define CMP_FILE_NAME "/Companies.csv"
#define JOB_FILE_NAME "/Jobs.csv"
#define EMP_FILE_NAME "/Employees.csv"
#define SKR_FILE_NAME "/Seekers.csv"

int mygetline(std::string& s, std::string& dest, char limit)
{
	int i = 0;
	auto it = s.begin();
	dest = "";
	while (it != s.end() && *it != limit)
	{
		dest += *it;
		it++;
		i++;
	}
	s.erase(0, i+1);
	return i;
}

void load_workers(List<Worker*>* workers, List<Company*>* companies, List<std::string>& colleagues_ids, std::ifstream &wrk_file, bool employed)
{
	std::string first_name, last_name, email, zip_code, line, skill;
	List<std::string>* skills;
	Company *company;

	// first line
	std::getline(wrk_file, line);
	while (!wrk_file.eof())
	{
		std::getline(wrk_file, line, ','); // id
		std::getline(wrk_file, line, ','); // first name
		first_name = line;
		std::getline(wrk_file, line, ','); // last name
		last_name = line;
		std::getline(wrk_file, line, ','); // email
		email = line;
		std::getline(wrk_file, line, ','); // zip code
		zip_code = line;

		std::getline(wrk_file, line, ','); // skills
		skills = new List<std::string>();
		while (mygetline(line, skill, ';'))
		{
			skills->addlast(skill);
		}

		if (employed) std::getline(wrk_file, line, ','); // colleagues
		else std::getline(wrk_file, line);
		colleagues_ids.addlast(line);
		
		if (employed) {
			std::getline(wrk_file, line); // company
			company = (*companies)[std::stoi(line)];
		}
		workers->addlast(new Worker(first_name, last_name, email));
		workers->last->data->set_zip_code(zip_code);
		workers->last->data->skills = skills;
		if (employed) workers->last->data->set_company(company);
	}
}

void load(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder)
{
	std::ifstream cmp_file, job_file, emp_file, skr_file;
	std::string line;

	cmp_file.open("./" + folder + CMP_FILE_NAME, std::ios::in);
	job_file.open("./" + folder + JOB_FILE_NAME, std::ios::in);
	emp_file.open("./" + folder + EMP_FILE_NAME, std::ios::in);
	skr_file.open("./" + folder + SKR_FILE_NAME, std::ios::in);
	// int i, j;

	// Loading companies
	std::string name, zip_code, email;
	// first line
	std::getline(cmp_file, line);
	while (!cmp_file.eof())
	{
		std::getline(cmp_file, line, ','); // id
		std::getline(cmp_file, line, ','); // name
		name = line;
		std::getline(cmp_file, line, ','); // zip_code
		zip_code = line;
		std::getline(cmp_file, line); // email
		email = line;
		companies->addlast(new Company(name, zip_code, email));
	}
	
	// Loading jobs
	std::string title, skill;
	List<std::string>* skills;
	Company *company;
	// first line
	std::getline(job_file, line);
	while (!job_file.eof())
	{
		std::getline(job_file, line, ','); // id
		std::getline(job_file, line, ','); // title
		title = line;

		std::getline(job_file, line, ','); // skills
		skills = new List<std::string>();
		while (mygetline(line, skill, ';'))
		{
			skills->addlast(skill);
		}
		
		std::getline(job_file, line); // company
		company = (*companies)[std::stoi(line)];
		jobs->addlast(new Job(title, skills, company));
	}
	
	// Loading workers
	List<std::string> colleagues_ids = List<std::string>();
	load_workers(workers, companies, colleagues_ids, emp_file, true);
	load_workers(workers, companies, colleagues_ids, skr_file, false);

	// Linking colleagues
	List<Worker*>* colleagues;
	std::string tmp;
	auto wrk_it = workers->first;
	auto id_it = colleagues_ids.first;
	while (wrk_it != NULL)
	{
		colleagues = new List<Worker*>();
		while (mygetline(id_it->data, tmp, ';'))
		{
			colleagues->addlast((*workers)[std::stoi(tmp)]);
		}
		wrk_it->data->colleagues = colleagues;

		wrk_it = wrk_it->next;
		id_it = id_it->next;
	}
}

void save(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder)
{
	std::ofstream cmp_file, job_file, emp_file, skr_file;
	cmp_file.open("./" + folder + CMP_FILE_NAME, std::ios::out);
	job_file.open("./" + folder + JOB_FILE_NAME, std::ios::out);
	emp_file.open("./" + folder + EMP_FILE_NAME, std::ios::out);
	skr_file.open("./" + folder + SKR_FILE_NAME, std::ios::out);
	int id;

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
			<< wrk_it->data->zip_code << ",";
		}
		else
		{
			skr_file << id << ","
			<< wrk_it->data->first_name << ","
			<< wrk_it->data->last_name << ","
			<< wrk_it->data->email << ","
			<< wrk_it->data->zip_code << ",";
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
		else skr_file << workers->get_pos(coll_it->data) << std::endl;
		
		// company
		if (wrk_it->data->employed()) emp_file << companies->get_pos(wrk_it->data->company) << std::endl;

		wrk_it = wrk_it->next;
		id++;
	}
}
