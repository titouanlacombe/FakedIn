#include "data_base.h"

#include "mylog.h"

#define CMP_FILE_NAME "/Companies.csv"
#define JOB_FILE_NAME "/Jobs.csv"
#define WRK_FILE_NAME "/Workers.csv"

#define CMP_FIRST_LINE "Name,Zip code,email"
#define JOB_FIRST_LINE "Title,Skills,Company"
#define WRK_FIRST_LINE "First name,Last name,email,Zip code,Skills,Co-workers,Company"

void load(std::string folder)
{
	if (!path_exist(folder)) system(("mkdir -p " + folder).c_str());

	std::ifstream cmp_file, job_file, wrk_file;
	cmp_file.open("./" + folder + CMP_FILE_NAME);
	job_file.open("./" + folder + JOB_FILE_NAME);
	wrk_file.open("./" + folder + WRK_FILE_NAME);

	//------------------------COMPANIES--------------------------
	std::string line, it, it2;
	std::getline(cmp_file, line);
	if (line != CMP_FIRST_LINE)
	{
		cmp_file.close();

		std::ofstream new_file;
		new_file.open("./" + folder + CMP_FILE_NAME);
		new_file << CMP_FIRST_LINE << "\n";
		new_file.close();
	}
	else
	{
		std::getline(cmp_file, line);
		while (!line.empty())
		{
			mygetline(line, it, ','); // name
			std::string name = it;
			mygetline(line, it, ','); // zip_code
			std::string zip_code = it;
			mygetline(line, it); // email
			std::string email = it;

			new Company(name, zip_code, email);

			std::getline(cmp_file, line);
		}
	}
	
	//------------------------JOBS--------------------------
	std::getline(job_file, line);
	if (line != JOB_FIRST_LINE)
	{
		job_file.close();

		std::ofstream new_file;
		new_file.open("./" + folder + JOB_FILE_NAME);
		new_file << JOB_FIRST_LINE << "\n";
		new_file.close();
	}
	else
	{
		std::getline(job_file, line);
		while (!line.empty())
		{
			mygetline(line, it, ','); // title
			std::string title = it;
			
			Job* j = new Job(title, NULL);

			mygetline(line, it, ','); // skills
			while (mygetline(it, it2, ';')) j->add_skill(it2);

			mygetline(line, it); // company
			j->company = get_company(it);
			
			std::getline(job_file, line);
		}
	}
	
	//------------------------WORKERS--------------------------
	List<std::string> co_workers_names;
	// first line workers
	std::getline(wrk_file, line);
	if (line != WRK_FIRST_LINE)
	{
		wrk_file.close();

		std::ofstream new_file;
		new_file.open("./" + folder + WRK_FILE_NAME);
		new_file << WRK_FIRST_LINE << "\n";
		new_file.close();
	}
	else
	{
		std::getline(wrk_file, line);
		while (!line.empty())
		{
			mygetline(line, it, ','); // first name
			std::string first_name = it;
			mygetline(line, it, ','); // last name
			std::string last_name = it;
			mygetline(line, it, ','); // email
			std::string email = it;
			
			Worker* w = new Worker(first_name, last_name, email);

			mygetline(line, it, ','); // zip code
			w->set_zip_code(it);

			mygetline(line, it, ','); // skills
			while (mygetline(it, it2, ';')) w->add_skill(it2);

			mygetline(line, it, ','); // co_workers
			co_workers_names.addlast(new std::string(it));
			
			mygetline(line, it); // company
			w->set_company(get_company(it));

			std::getline(wrk_file, line);
		}
	}

	// Linking co_workers
	std::string tmp_str;
	auto wrk_it = get_workers()->first();
	auto id_it = co_workers_names.first();
	while (wrk_it != get_workers()->end())
	{
		if (!(* *id_it).empty())
		{
			tmp_str = * *id_it;
			while (mygetline(tmp_str, it, ';')) (*wrk_it)->co_workers.addlast(get_worker(it));
		}
		wrk_it++;
		id_it++;
	}

	cmp_file.close();
	job_file.close();
	wrk_file.close();
}

void save(std::string folder)
{
	if (!path_exist(folder)) system(("mkdir -p " + folder).c_str());

	std::ofstream cmp_file, job_file, wrk_file;
	cmp_file.open("./" + folder + CMP_FILE_NAME);
	job_file.open("./" + folder + JOB_FILE_NAME);
	wrk_file.open("./" + folder + WRK_FILE_NAME);

	//------------------------WORKERS--------------------------
	auto wrk_it = get_workers()->first();
	wrk_file << WRK_FIRST_LINE << "\n";
	while (wrk_it != get_workers()->end())
	{
		// first name,last name,email,zip code
		wrk_file << (*wrk_it)->first_name << ","
		<< (*wrk_it)->last_name << ","
		<< (*wrk_it)->email << ","
		<< (*wrk_it)->zip_code << ",";
		
		// Skills
		auto skl_it2 = (*wrk_it)->skills.first();
		while (skl_it2 != (*wrk_it)->skills.last())
		{
			wrk_file << * *skl_it2 << ";";
			skl_it2++;
		}
		if (skl_it2 != (*wrk_it)->skills.end()) wrk_file << * *skl_it2;
		
		wrk_file << ",";
		
		// co_workers
		auto coll_it = (*wrk_it)->co_workers.first();
		while (coll_it != (*wrk_it)->co_workers.last())
		{
			wrk_file << (*coll_it)->first_name << " " << (*coll_it)->last_name << ";";
			coll_it++;
		}
		if (coll_it != (*wrk_it)->co_workers.end()) wrk_file << (*coll_it)->first_name << " " << (*coll_it)->last_name;
		wrk_file << ",";
		
		// company
		if ((*wrk_it)->employed()) wrk_file << (*wrk_it)->company->name;
		
		wrk_file << "\n";
		wrk_it++;
	}
	
	//------------------------JOBS--------------------------
	auto job_it = get_jobs()->first();
	job_file << JOB_FIRST_LINE << "\n";
	while (job_it != get_jobs()->end())
	{
		// title
		job_file << (*job_it)->title << ",";

		// Skills
		auto skl_it = (*job_it)->skills.first();
		while (skl_it != (*job_it)->skills.last())
		{
			job_file << * *skl_it << ";";
			skl_it++;
		}
		if (skl_it != (*job_it)->skills.end()) job_file << * *skl_it;
		job_file << ",";
		
		// Company
		job_file << (*job_it)->company->name << "\n";

		job_it++;
	}
	
	//------------------------COMPANIES--------------------------
	auto cmp_it = get_companies()->first();
	cmp_file << CMP_FIRST_LINE << "\n";
	while (cmp_it != get_companies()->end())
	{
		Company* c = *cmp_it;
		// name,zip code,email
		cmp_file << c->name << ","
		<< c->zip_code << ","
		<< c->email << "\n";

		cmp_it++;
		delete c;
	}
	
	get_companies()->clean();
	get_jobs()->clean();
	get_workers()->clean();

	cmp_file.close();
	job_file.close();
	wrk_file.close();
}
