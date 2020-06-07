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

void load_workers(List<Worker*>& workers, List<Company*>& companies, List<std::string>& co_workers_ids, std::ifstream &wrk_file, bool employed)
{
	std::string first_name, last_name, email, zip_code, line, it, it2;
	Worker *w;

	std::getline(wrk_file, line);
	while (!line.empty())
	{
		mygetline(line, it, ','); // id
		mygetline(line, it, ','); // first name
		first_name = it;
		mygetline(line, it, ','); // last name
		last_name = it;
		mygetline(line, it, ','); // email
		email = it;
		mygetline(line, it, ','); // zip code
		zip_code = it;
		
		w = new Worker(first_name, last_name, email);
		workers.addlast(w);
		workers.last_n->data->set_zip_code(zip_code);

		mygetline(line, it, ','); // skills
		while (mygetline(it, it2, ';')) workers.last_n->data->add_skill(it2);

		if (employed) mygetline(line, it, ','); // co_workers
		else mygetline(line, it);
		co_workers_ids.addlast(it);
		
		if (employed)
		{
			mygetline(line, it); // company
			workers.last_n->data->set_company(companies[std::stoi(it)]);
		}

		std::getline(wrk_file, line);
	}
}

void load(List<Company*>& companies, List<Job*>& jobs, List<Worker*>& workers, std::string folder)
{
	std::ifstream cmp_file, job_file, emp_file, skr_file;
	std::string line, it, it2;
	Company *c;
	Job *j;

	companies.empty();
	jobs.empty();
	workers.empty();

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
			mygetline(line, it, ','); // id
			mygetline(line, it, ','); // name
			name = it;
			mygetline(line, it, ','); // zip_code
			zip_code = it;
			mygetline(line, it); // email
			email = it;
			c = new Company(name, zip_code, email);
			companies.addlast(c);

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
		std::getline(job_file, line);
		while (!line.empty())
		{
			mygetline(line, it, ','); // id
			mygetline(line, it, ','); // title
			title = it;
			
			j = new Job(title, NULL);
			jobs.addlast(j);

			mygetline(line, it, ','); // skills
			while (mygetline(it, it2, ';')) j->add_skill(it2);
			
			mygetline(line, it); // company
			company = companies[std::stoi(it)];
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
	std::string tmp_str;
	auto wrk_it = workers.first();
	auto id_it = co_workers_ids.first();
	while (wrk_it != workers.end())
	{
		if (!(*id_it).empty())
		{
			tmp_str = *id_it;
			while (mygetline(tmp_str, it, ';')) (*wrk_it)->co_workers.addlast(workers[std::stoi(it)]);
		}

		wrk_it++;
		id_it++;
	}

	cmp_file.close();
	job_file.close();
	emp_file.close();
	skr_file.close();
}

void save(List<Company*>& companies, List<Job*>& jobs, List<Worker*>& workers, std::string folder)
{
	std::ofstream cmp_file, job_file, emp_file, skr_file;
	int id;

	cmp_file.open("./" + folder + CMP_FILE_NAME);
	job_file.open("./" + folder + JOB_FILE_NAME);
	emp_file.open("./" + folder + EMP_FILE_NAME);
	skr_file.open("./" + folder + SKR_FILE_NAME);

	// Saving companies
	auto cmp_it = companies.first();
	id = 0;
	cmp_file << CMP_FIRST_LINE << "\n";
	while (cmp_it != companies.end())
	{
		// id,name,zip code,email
		cmp_file << id << ","
		<< (*cmp_it)->name << ","
		<< (*cmp_it)->zip_code << ","
		<< (*cmp_it)->email << "\n";
		cmp_it++;
		id++;
	}
	
	// Saving jobs
	auto job_it = jobs.first();
	id = 0;
	job_file << JOB_FIRST_LINE << "\n";
	while (job_it != jobs.end())
	{
		// id,title
		job_file << id << "," <<
		(*job_it)->title << ",";

		// Skills
		auto skl_it = (*job_it)->skills.first();
		while (skl_it != (*job_it)->skills.last())
		{
			job_file << *skl_it << ";";
			skl_it++;
		}
		if (skl_it != (*job_it)->skills.end()) job_file << *skl_it;
		job_file << ",";
		
		// Company id
		job_file << companies.get_pos((*job_it)->company) << "\n";

		job_it++;
		id++;
	}
	
	// Saving workers
	auto wrk_it = workers.first();
	id = 0;
	emp_file << EMP_FIRST_LINE << "\n";
	skr_file << SKR_FIRST_LINE << "\n";
	while (wrk_it != workers.end())
	{
		// id,first name,last name,email,zip code
		if ((*wrk_it)->employed())
		{
			emp_file << id << ","
			<< (*wrk_it)->first_name << ","
			<< (*wrk_it)->last_name << ","
			<< (*wrk_it)->email << ","
			<< (*wrk_it)->zip_code << ",";
		}
		else
		{
			skr_file << id << ","
			<< (*wrk_it)->first_name << ","
			<< (*wrk_it)->last_name << ","
			<< (*wrk_it)->email << ","
			<< (*wrk_it)->zip_code << ",";
		}
		
		// Skills
		auto skl_it2 = (*wrk_it)->skills.first();
		while (skl_it2 != (*wrk_it)->skills.last())
		{
			if ((*wrk_it)->employed()) emp_file << *skl_it2 << ";";
			else skr_file << *skl_it2 << ";";
			skl_it2++;
		}
		if (skl_it2 != (*wrk_it)->skills.end())
		{
			if ((*wrk_it)->employed()) emp_file << *skl_it2;
			else skr_file << *skl_it2;
		}
		if ((*wrk_it)->employed()) emp_file << ",";
		else skr_file << ",";
		
		// co_workers
		auto coll_it = (*wrk_it)->co_workers.first();
		while (coll_it != (*wrk_it)->co_workers.last())
		{
			if ((*wrk_it)->employed()) emp_file << workers.get_pos(*coll_it) << ";";
			else skr_file << workers.get_pos(*coll_it) << ";";

			coll_it++;
		}
		if (coll_it != (*wrk_it)->co_workers.end())
		{
			if ((*wrk_it)->employed()) emp_file << workers.get_pos(*coll_it);
			else skr_file << workers.get_pos(*coll_it);
		}
		if ((*wrk_it)->employed()) emp_file << ",";
		else skr_file << "\n";
		
		// company
		if ((*wrk_it)->employed()) emp_file << companies.get_pos((*wrk_it)->company) << "\n";

		wrk_it++;
		id++;
	}
	
	companies.empty();
	jobs.empty();
	workers.empty();

	cmp_file.close();
	job_file.close();
	emp_file.close();
	skr_file.close();
}
