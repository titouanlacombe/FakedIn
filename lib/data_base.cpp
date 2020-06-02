#include "data_base.h"

#define CMP_FILE_NAME "/Companies.csv"
#define JOB_FILE_NAME "/Jobs.csv"
#define EMP_FILE_NAME "/Employees.csv"
#define SKR_FILE_NAME "/Seekers.csv"

#define CMP_FIRST_LINE (std::string)"id,name,zip code,email"
#define JOB_FIRST_LINE (std::string)"id,title,skills,company"
#define EMP_FIRST_LINE (std::string)"id,first name,last name,email,zip code,skills,co_workers,company"
#define SKR_FIRST_LINE (std::string)"id,first name,last name,email,zip code,skills,co_workers"

void dump_str(std::string s)
{
  for (unsigned int n = 0; n < s.length(); n++)
  {
    char c = s[n];
    std::cout << (int)c << ",";
  }
  std::cout << "\n";
}

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

void create_cmp_file(std::string folder)
{
	std::ofstream cmp_file;
	cmp_file.open("./" + folder + CMP_FILE_NAME);
	cmp_file << CMP_FIRST_LINE << "\n";
	cmp_file.close();
}

void create_job_file(std::string folder)
{
	std::ofstream job_file;
	job_file.open("./" + folder + JOB_FILE_NAME);
	job_file << JOB_FIRST_LINE << "\n";
	job_file.close();
}

void create_emp_file(std::string folder)
{
	std::ofstream emp_file;
	emp_file.open("./" + folder + EMP_FILE_NAME);
	emp_file << EMP_FIRST_LINE << "\n";
	emp_file.close();
}

void create_skr_file(std::string folder)
{
	std::ofstream skr_file;
	skr_file.open("./" + folder + SKR_FILE_NAME);
	skr_file << SKR_FIRST_LINE << "\n";
	skr_file.close();
}

void load_workers(List<Worker*>* workers, List<Company*>* companies, List<std::string>& co_workers_ids, std::ifstream &wrk_file, bool employed)
{
	std::string first_name, last_name, email, zip_code, line, tmp, tmp2;
	List<std::string>* skills;
	Company *company;

	std::getline(wrk_file, line);
	while (!line.empty())
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

		if (employed) mygetline(line, tmp, ','); // co_workers
		else mygetline(line, tmp);
		co_workers_ids.addlast(tmp);
		
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

	companies->empty();
	jobs->empty();
	workers->empty();

	cmp_file.open("./" + folder + CMP_FILE_NAME);
	job_file.open("./" + folder + JOB_FILE_NAME);
	emp_file.open("./" + folder + EMP_FILE_NAME);
	skr_file.open("./" + folder + SKR_FILE_NAME);

	// first line cmp
	std::getline(cmp_file, line);
	if (line != CMP_FIRST_LINE)
	{
		cmp_file.close();
		create_cmp_file(folder);
	}
	else
	{
		// Loading companies
		std::string name, zip_code, email;
		std::getline(cmp_file, line);
		while (!line.empty())
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
	}
	
	// first line jobs
	std::getline(job_file, line);
	if (line != JOB_FIRST_LINE)
	{
		job_file.close();
		create_job_file(folder);
	}
	else
	{
		// Loading jobs
		std::string title;
		Company *company;
		Job* j; 
		std::getline(job_file, line);
		while (!line.empty())
		{
			mygetline(line, tmp, ','); // id
			mygetline(line, tmp, ','); // title
			title = tmp;
			
			j = new Job(title, NULL);
			jobs->addlast(j);

			mygetline(line, tmp, ','); // skills
			while (mygetline(tmp, tmp2, ';'))
			{
				j->add_skill(tmp2);
			}
			
			mygetline(line, tmp); // company
			company = (*companies)[std::stoi(tmp)];
			j->company = company;
			
			std::getline(job_file, line);
		}
	}
	
	// Loading workers
	List<std::string> co_workers_ids = List<std::string>();
	// first line emp
	std::getline(emp_file, line);
	if (line != EMP_FIRST_LINE)
	{
		emp_file.close();
		create_emp_file(folder);
	}
	else
	{
		// Loading emp
		load_workers(workers, companies, co_workers_ids, emp_file, true);
	}

	// first line skr
	std::getline(skr_file, line);
	if (line != SKR_FIRST_LINE)
	{
		skr_file.close();
		create_skr_file(folder);
	}
	else
	{
		// Loading skr
		load_workers(workers, companies, co_workers_ids, skr_file, false);
	}

	// Linking co_workers
	List<Worker*>* co_workers;
	auto wrk_it = workers->first;
	auto id_it = co_workers_ids.first;
	while (wrk_it != NULL)
	{
		co_workers = new List<Worker*>();
		if (!id_it->data.empty())
		{
			while (mygetline(id_it->data, tmp, ';'))
			{
				co_workers->addlast((*workers)[std::stoi(tmp)]);
			}
			wrk_it->data->co_workers = co_workers;
		}

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
	cmp_file << CMP_FIRST_LINE << "\n";
	while (cmp_it != NULL)
	{
		// id,name,zip code,email
		cmp_file << id << ","
		<< cmp_it->data->name << ","
		<< cmp_it->data->zip_code << ","
		<< cmp_it->data->email << "\n";
		cmp_it = cmp_it->next;
		id++;
	}
	
	// Saving jobs
	auto job_it = jobs->first;
	id = 0;
	job_file << JOB_FIRST_LINE << "\n";
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
		if (skl_it != NULL) job_file << skl_it->data;
		job_file << ",";
		
		// Company id
		job_file << companies->get_pos(job_it->data->company) << "\n";

		job_it = job_it->next;
		id++;
	}
	
	// Saving workers
	auto wrk_it = workers->first;
	id = 0;
	emp_file << EMP_FIRST_LINE << "\n";
	skr_file << SKR_FIRST_LINE << "\n";
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
		if (skl_it2 != NULL)
		{
			if (wrk_it->data->employed()) emp_file << skl_it2->data;
			else skr_file << skl_it2->data;
		}
		if (wrk_it->data->employed()) emp_file << ",";
		else skr_file << ",";
		
		// co_workers
		auto coll_it = wrk_it->data->co_workers->first;
		while (coll_it != wrk_it->data->co_workers->last)
		{
			if (wrk_it->data->employed()) emp_file << workers->get_pos(coll_it->data) << ";";
			else skr_file << workers->get_pos(coll_it->data) << ";";

			coll_it = coll_it->next;
		}
		if (coll_it != NULL)
		{
			if (wrk_it->data->employed()) emp_file << workers->get_pos(coll_it->data);
			else skr_file << workers->get_pos(coll_it->data);
		}
		if (wrk_it->data->employed()) emp_file << ",";
		else skr_file << "\n";
		
		// company
		if (wrk_it->data->employed()) emp_file << companies->get_pos(wrk_it->data->company) << "\n";

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
