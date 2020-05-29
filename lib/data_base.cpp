#include "data_base.h"

#define CMP_FILE_NAME "/Companies.csv"
#define JOB_FILE_NAME "/Jobs.csv"
#define EMP_FILE_NAME "/Employees.csv"
#define SKR_FILE_NAME "/Seekers.csv"

void load(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder)
{
	std::ofstream cmp_file, job_file, emp_file, skr_file;
	List<int> cmp_id, job_id, emp_id, skr_id;

	cmp_file.open("./" + folder + CMP_FILE_NAME, std::ios::in);
	job_file.open("./" + folder + JOB_FILE_NAME, std::ios::in);
	emp_file.open("./" + folder + EMP_FILE_NAME, std::ios::in);
	skr_file.open("./" + folder + SKR_FILE_NAME, std::ios::in);

	// Loading companies
	std::string line, name, zip_code, email;
	cmp_file >> line;
	std::cout << line;
	// int id;
	// while (std::ios::getline(cmp_file, line))
	// {
	// 	std::cout << line << std::endl;
		
	// 	// companies->addlast(new Company(name, zip_code, email));
	// 	// cmp_id.addlast(id);
	// }
	// Loading jobs
	// Loading workers
	// Loading seekers
}

void save(List<Company*>* companies, List<Job*>* jobs, List<Worker*>* workers, std::string folder)
{
	std::ofstream cmp_file, job_file, emp_file, skr_file;
	List<int> cmp_id, job_id, emp_id, skr_id;

	cmp_file.open("./" + folder + CMP_FILE_NAME, std::ios::out);
	job_file.open("./" + folder + JOB_FILE_NAME, std::ios::out);
	emp_file.open("./" + folder + EMP_FILE_NAME, std::ios::out);
	skr_file.open("./" + folder + SKR_FILE_NAME, std::ios::out);

	// Saving companies
	// Saving jobs
	// Saving workers
	// Saving seekers
}
