#include "data_base.h"

#define CMP_FILE_NAME "/Companies.csv"
#define JOB_FILE_NAME "/Jobs.csv"
#define EMP_FILE_NAME "/Employees.csv"
#define SKR_FILE_NAME "/Seekers.csv"

int mygetline(std::string& s, std::string& dest, char limit = '\n')
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
	std::string first_name, last_name, email, zip_code, line, tmp, tmp2;
	List<std::string>* skills;
	Company *company;

	// first line
	std::getline(wrk_file, line);
	std::getline(wrk_file, line);
	while (line != "")
	{
		mygetline(line, tmp, ','); // id
		mygetline(line, tmp, ','); // first name
		first_name = tmp;
		mygetline(line, tmp, ','); // last name
		last_name = tmp;
		mygetline(line, tmp, ','); // email
		email = tmp;
		mygetline(line, tmp, ','); // zip code
		zip_code = tmp;

		mygetline(line, tmp, ','); // skills
		skills = new List<std::string>();
		while (mygetline(tmp, tmp2, ';'))
		{
			skills->addlast(tmp2);
		}

		if (employed) mygetline(line, tmp, ','); // colleagues
		else mygetline(line, tmp);
		colleagues_ids.addlast(tmp);
		
		if (employed) {
			mygetline(line, tmp); // company
			company = (*companies)[std::stoi(tmp)];
		}
		workers->addlast(new Worker(first_name, last_name, email));
		workers->last->data->set_zip_code(zip_code);
		workers->last->data->skills = skills;
		if (employed) workers->last->data->set_company(company);

		std::getline(wrk_file, line);
	}
}

void load(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder)
{
	std::ifstream cmp_file, job_file, emp_file, skr_file;
	std::string line, tmp, tmp2;

	cmp_file.open("./" + folder + CMP_FILE_NAME);
	job_file.open("./" + folder + JOB_FILE_NAME);
	emp_file.open("./" + folder + EMP_FILE_NAME);
	skr_file.open("./" + folder + SKR_FILE_NAME);

	// Loading companies
	std::string name, zip_code, email;
	// first line
	std::getline(cmp_file, line);
	std::getline(cmp_file, line);
	while (line != "")
	{
		mygetline(line, tmp, ','); // id
		mygetline(line, tmp, ','); // name
		name = tmp;
		mygetline(line, tmp, ','); // zip_code
		zip_code = tmp;
		mygetline(line, tmp); // email
		email = tmp;
		companies->addlast(new Company(name, zip_code, email));

		std::getline(cmp_file, line);
	}
	
	// Loading jobs
	std::string title;
	List<std::string>* skills;
	Company *company;
	// first line
	std::getline(job_file, line);
	std::getline(job_file, line);
	while (line != "")
	{
		mygetline(line, tmp, ','); // id
		mygetline(line, tmp, ','); // title
		title = tmp;

		mygetline(line, tmp, ','); // skills
		skills = new List<std::string>();
		while (mygetline(tmp, tmp2, ';'))
		{
			skills->addlast(tmp2);
		}
		
		mygetline(line, tmp); // company
		company = (*companies)[std::stoi(tmp)];
		jobs->addlast(new Job(title, skills, company));
		
		std::getline(job_file, line);
	}
	
	// Loading workers
	List<std::string> colleagues_ids = List<std::string>();
	load_workers(workers, companies, colleagues_ids, emp_file, true);
	load_workers(workers, companies, colleagues_ids, skr_file, false);

	// Linking colleagues
	List<Worker*>* colleagues;
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

	cmp_file.close();
	job_file.close();
	emp_file.close();
	skr_file.close();
}

void save(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder)
{
	std::ofstream cmp_file, job_file, emp_file, skr_file;
	int id;

	cmp_file.open("./" + folder + CMP_FILE_NAME);
	job_file.open("./" + folder + JOB_FILE_NAME);
	emp_file.open("./" + folder + EMP_FILE_NAME);
	skr_file.open("./" + folder + SKR_FILE_NAME);

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

	cmp_file.close();
	job_file.close();
	emp_file.close();
	skr_file.close();
}

void load_db()
{
	return;
}
