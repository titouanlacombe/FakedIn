#include "UI.h"

using namespace std;

bool valid_email(string email)
{
	string copy(email), it;

	mygetline(copy, it, '@');
	if (it.empty()) return false;
	mygetline(copy, it, '.');
	if (it.empty()) return false;
	mygetline(copy, it);
	if (it.empty()) return false;
	return true;
}

bool is_number(string str)
{
	auto it = str.begin();
	while (it != str.end() && isdigit(*it)) ++it;
	return !str.empty() && it == str.end();
}

bool valid_zip(string zip)
{
	return is_number(zip);
}

void print_error(string str)
{
	cout << get_phrase(106) << ": " << str << endl;
}

void print_error(string start, string help, string end)
{
	print_error(start + " '" + help + "' " + end);
}

void print_error(int str)
{
	print_error(get_phrase(str));
}

void print_error(int start, string help, int end)
{
	print_error(get_phrase(start), help, get_phrase(end));
}

void print_title(string title)
{
	cout << "~~ " << title << " ~~\n" << endl;
}

void print_title(int title)
{
	cout << "~~ " << get_phrase(title) << " ~~\n" << endl;
}

void print_menu(int nb_choices, string title, char* choices_str[])
{
	print_title(title);
	cout << get_phrase(37) + ":\n";
	for (int i = 0; i < nb_choices; i++)
	{
		cout << "\t" << to_string(i + 1) << ". " << choices_str[i] << endl;
	}
	cout << endl;
}

void print_menu(int nb_choices, int title, int choices_str[])
{
	char** tab = (char**)malloc(nb_choices * sizeof(char*));
	for (int i = 0; i < nb_choices; i++)
	{
		string tmp = get_phrase(choices_str[i]);
		tab[i] = (char*)malloc((tmp.length() + 1) * sizeof(char));
		strcpy(tab[i], tmp.c_str());
	}

	print_menu(nb_choices, get_phrase(title), tab);

	for (int i = 0; i < nb_choices; i++) free(tab[i]);
	free(tab);
}

void print_menu(int nb_choices, string title, int choices_str[])
{
	char** tab = (char**)malloc(nb_choices * sizeof(char*));
	for (int i = 0; i < nb_choices; i++)
	{
		string tmp = get_phrase(choices_str[i]);
		tab[i] = (char*)malloc((tmp.length() + 1) * sizeof(char));
		strcpy(tab[i], tmp.c_str());
	}

	print_menu(nb_choices, title, tab);

	for (int i = 0; i < nb_choices; i++) free(tab[i]);
	free(tab);
}

int request_choice(int nb)
{
	int choice;
	string it;
	do
	{
		cout << get_phrase(1) + ": ";
		getline(cin, it);
		if (it.empty()) return -1;
		if (is_number(it)) {
			choice = stoi(it);
			if (choice > 0 && choice <= nb) return choice;
		}
		print_error(2);
	} while (true);
}

bool request_yn_choice()
{
	string it;
	do
	{
		cout << get_phrase(3) + ": ";
		getline(cin, it);
		if (it == "o" || it == "y") return true;
		else if (it == "n") return false;
		print_error(2);
	} while (true);
}

string request_cmp_name()
{
	string name;
	bool loop = true;
	do
	{
		cout << "- " << get_phrase(4) << ": ";
		getline(cin, name);
		if (cmp_exist(name)) print_error(5, name, 6);
		else if (name.empty()) print_error(7);
		else loop = false;
	} while (loop);
	return name;
}

Company* request_cmp_login(string request_line)
{
	Company* c;
	string name;
	bool loop = true;
	do
	{
		cout << request_line;
		getline(cin, name);
		if (name.empty()) return NULL;
		c = get_company(name);
		if (c == NULL) print_error(5, name, 9);
		else loop = false;
	} while (loop);
	return c;
}

string request_email()
{
	string email;
	bool loop = true;
	do
	{
		cout << "- " << get_phrase(10) << ": ";
		getline(cin, email);
		if (!valid_email(email)) print_error(11, email, 12);
		else loop = false;
	} while (loop);
	return email;
}

string request_zip()
{
	bool loop;
	string zip;
	loop = true;
	do
	{
		cout << "- " << get_phrase(13) << ": ";
		getline(cin, zip);
		if (!valid_zip(zip)) print_error(14, zip, 15);
		else loop = false;
	} while (loop);
	return zip;
}

string request_job_title(Company& c)
{
	string title;
	bool loop = true;
	do
	{
		cout << "- " << get_phrase(16) << ": ";
		getline(cin, title);
		if (job_exist(c, title)) print_error(17, title, 18);
		else if (title.empty()) print_error(19);
		else loop = false;
	} while (loop);
	return title;
}

Job* request_job_login(Company& c, string request_phrase)
{
	Job *j;
	string title;
	bool loop = true;
	do
	{
		cout << request_phrase;
		getline(cin, title);
		if (title.empty()) return NULL;
		j = get_job(c, title);
		if (j == NULL) print_error(17, title, 9);
		else loop = false;
	} while (loop);
	return j;
}

bool has_same_str(List<string> ls, string s)
{
	auto it = ls.first();
	while (it != ls.end())
	{
		if ((* *it) == s) return true;
		it++;
	}
	return false;
}

template <typename T>
void request_skills(T& w, string request_phrase)
{
	string skills_raw, it;
	cout << request_phrase;
	getline(cin, skills_raw);
	while (mygetline(skills_raw, it, ',')) {
		if (it.empty()) print_error(21);
		else if (has_same_str(w.skills, it)) print_error(22, it, 23);
		else w.add_skill(it);
	}
}

void request_wrk_name(string& first_name, string& full_name)
{
	bool loop = true;
	do
	{
		cout << "- " << get_phrase(24) << ": ";
		getline(cin, full_name);
		mygetline(full_name, first_name, ' ');
		if (wrk_exist(first_name, full_name)) print_error(25, first_name + " " + full_name, 6);
		else if (full_name.empty() || first_name.empty()) print_error(26);
		else loop = false;
	} while (loop);
}

void request_wrk_coll(Worker& w)
{
	Worker* coll;
	string first_name, full_name;
	bool loop = true;
	do
	{
		cout << "- " << get_phrase(27) << ": ";
		getline(cin, full_name);
		if (!full_name.empty())
		{
			mygetline(full_name, first_name, ' ');
			coll = get_worker(first_name, full_name);
			if (coll == NULL) print_error(25, first_name + " " + full_name, 9);
			else if (*coll == w) print_error(28);
			else if (!coll->employed()) print_error(29);
			else if (w.co_workers.has(coll)) print_error(30, coll->first_name + " " + coll->last_name, 31);
			else
			{
				w.add_co_worker(*coll);
				coll->add_co_worker(w);
			}
		}
		else loop = false;
	} while (loop);
}

void request_wrk_cmp(Worker& w)
{
	Company* c;
	string name;
	bool loop = true;
	do
	{
		cout << "- " << get_phrase(32) << ": ";
		getline(cin, name);
		if (!name.empty())
		{
			c = get_company(name);
			if (c == NULL) print_error(5, name, 9);
			else
			{
				w.set_company(c);
				loop = false;
			}
		}
		else
		{
			w.set_company(NULL);
			loop = false;
		}
	} while (loop);
}

void change_lang()
{
	bool loop;
	string lang;
	loop = true;
	do
	{
		cout << "Please enter the language you want\n(you need to have yourlanguage.lang in the language folder): ";
		getline(cin, lang);
		if (!path_exist("./languages/" + lang + ".lang")) cout << "Error: the file '" << lang << ".lang" << "' does not exist" << endl;
		else loop = false;
	} while (loop);
	
	load_language("./languages/" + lang + ".lang");
}

void home()
{
	do
	{
		cout << endl;

		int choices_str[3] = {34, 35, 36};
		print_menu(3, 33, choices_str);
		
		int choice = request_choice(3);
		if (choice == -1) return;
		cout << endl;

		switch(choice)
		{
		case 1:
			pre_company();
			break;
		case 2:
			pre_worker();
			break;
		case 3:
			change_lang();
			break;
		}
	} while (true);
}

void pre_company()
{
	int choices_str[2] = {38, 39};
	print_menu(2, 34, choices_str);
	
	int choice = request_choice(2);
	if (choice == -1) return;
	cout << endl;

	switch(choice)
	{
	case 1:
		login_company();
		break;
	case 2:
		create_company();
		break;
	}
}

void create_company()
{
	string name, zip, email;
	Company *c;

	print_title(40);
	cout << get_phrase(41) + ":\n";
	name = request_cmp_name();
	zip = request_zip();
	email = request_email();
	cout << endl;

	c = new Company(name, zip, email);

	cout << get_phrase(42) + "\n" << endl;
	log_write("New Company created: " + name + ", " + zip + ", " + email);
	company_menu(*c);
}

void login_company()
{
	Company* c;
	string name;

	print_title(43);
	c = request_cmp_login(get_phrase(44) + ": ");
	if (c == NULL) return;
	
	company_menu(*c);
}

void company_menu(Company& c)
{
	int choice;
	
	do
	{
		int choices_str[4] = {47, 48, 49, 50};
		print_menu(4, get_phrase(45) + " (" + c.name + ")", choices_str);
		
		choice = request_choice(4);
		if (choice == -1) return;
		cout << endl;

		switch(choice)
		{
		case 1:
			search_worker(c);
			break;
		case 2:
			create_job(c);
			break;
		case 3:
			delete_job(c);
			break;
		case 4:
			delete_company(c);
			return;
		}
	} while (true);
}

void search_worker(Company& c)
{
	List<Worker>* results;
	string title;
	bool zip;
	Job *j;

	print_title(51);
	j = request_job_login(c, get_phrase(52) + ": ");
	if (j == NULL) return;
	cout << endl;
	cout << get_phrase(53) + "\n";
	zip = request_yn_choice();
	cout << endl;

	results = srch_wrk_profile_job(*j, zip);

	if (results->length > 0) results->print(get_phrase(54), false);
	else cout << get_phrase(55) << endl;
	cout << "\n" + get_phrase(56);
	getline(cin, title);
	delete results;
}

void create_job(Company& c)
{
	string title;
	Job *j;

	print_title(57);
	cout << get_phrase(41) + ":\n";
	title = request_job_title(c);

	j = new Job(title, &c);

	request_skills(*j, "- " + get_phrase(58) + ": ");
	cout << get_phrase(59) << endl;
	log_write("New Job created: " + title);
}

void delete_job(Company& c)
{
	string title;
	Job* j;

	print_title(60);
	j = request_job_login(c, get_phrase(61) + ": ");
	if (j == NULL) return;
	cout << endl;
	cout << get_phrase(62) << endl;
	log_write("Job " + title + " from " + c.name + " deleted");
	delete j;
}

void delete_company(Company& c)
{
	List<Job>* lj;
	List<Worker>* lw;
	bool choice;

	print_title(63);
	cout << get_phrase(64) + "\n";
	choice = request_yn_choice();
	cout << endl;

	if(choice)
	{
		lj = company_jobs(c);
		get_jobs()->remove(*lj);
		delete lj;

		lw = company_employees(c);
		auto it = lw->first();
		while (it != lw->end())
		{
			(*it)->set_company(NULL);
			it++;
		}
		delete lw;

		delete &c;

		cout << get_phrase(65) << endl;
		log_write("Company deleted: " + c.name);
	}
	else cout << get_phrase(66) << endl;
}

void pre_worker()
{
	int choices_str[2] = {67, 68};
	print_menu(2, 35, choices_str);

	int choice = request_choice(2);
	if (choice == -1) return;
	cout << endl;
	
	switch(choice)
	{
	case 1:
		login_worker();
		break;
	case 2:
		create_worker();
		break;
	}
}

void create_worker()
{
	string first_name, full_name, email, zip;
	Worker *w;

	print_title(69);
	cout << get_phrase(41) + ":\n";
	request_wrk_name(first_name, full_name);
	email = request_email();
	zip = request_zip();

	w = new Worker(first_name, full_name, email);
	w->set_zip_code(zip);

	// Compétences
	request_skills(*w, "- " + get_phrase(70) + ": ");
	request_wrk_coll(*w);
	request_wrk_cmp(*w);
	cout << "\n" + get_phrase(71) + "\n" << endl;
	log_write("New worker created: " + first_name + " " + full_name);
	worker_menu(*w);
}

void login_worker()
{
	bool loop;
	Worker* w;
	string full_name;

	print_title(72);
	loop = true;
	do
	{
		cout << get_phrase(73) << ": ";
		getline(cin, full_name);
		if (full_name.empty()) return;
		w = get_worker(full_name);
		if (w == NULL) cout << get_phrase(25) + full_name + get_phrase(9) << endl;
		else loop = false;
	} while (loop);
	
	worker_menu(*w);
}

void worker_menu(Worker& w)
{
	int choice;

	do
	{
		int choices_str[4] = {75, 76, 77, 78};
		print_menu(4, get_phrase(74) + w.first_name + " " + w.last_name + ")", choices_str);

		choice = request_choice(4);
		if (choice == -1) return;
		cout << endl;

		switch(choice)
		{
		case 1:
			search_job(w);
			break;
		case 2:
			search_coll(w);
			break;
		case 3:
			modify_worker(w);
			break;
		case 4:
			delete_worker(w);
			return;
		}
	} while (true);
}

void search_job(Worker& w)
{
	List<Job>* results;
	bool zip;
	string it;

	print_title(79);
	cout << get_phrase(80) + "\n";
	zip = request_yn_choice();
	cout << endl;

	results = srch_job_profile_wrk(w, zip);
	if (results->length > 0) results->print(get_phrase(54), false);
	else cout << get_phrase(55) << endl;
	cout << "\n" + get_phrase(81);
	getline(cin, it);
	delete results;
}

void search_coll(Worker& w)
{
	List<Worker>* results;
	Company* c;
	string name;

	int choices_str[2] = {83, 84};
	print_menu(2, 82, choices_str);
	
	int choice = request_choice(2);
	if (choice == -1) return;	
	cout << endl;

	switch(choice)
	{
	case 1:
		c = request_cmp_login(get_phrase(85) + ": ");
		if (c == NULL) return;
		cout << endl;
		results = srch_coll_from_cmp(w, *c);
		if (results->length > 0) results->print(get_phrase(54), false);
		else cout << get_phrase(55) << endl;
		break;
	case 2:
		results = srch_coll_skills(w);
		if (results->length > 0) results->print(get_phrase(54), false);
		else cout << get_phrase(55) << endl;
		break;
	}
	cout << "\n" + get_phrase(81);
	getline(cin, name);
	delete results;
}

void modify_worker(Worker& w)
{
	string zip;
	int choice;

	cout << get_phrase(46) << endl;
	cout << get_phrase(87) + ":\n"
	<< w.first_name << " " << w.last_name << "\n"
	<< get_phrase(88) + ": " << w.email << "\n" + get_phrase(89) + ": " << w.zip_code << endl;
	if(w.employed()) cout << get_phrase(90) + ": " << w.company->name << endl;
	else cout << get_phrase(91) << endl;
	w.skills.print(get_phrase(92) + ": ", true);
	cout << get_phrase(93) + ": ";
	auto it = w.co_workers.first();
	while (it != w.co_workers.end())
	{
		cout << (*it)->first_name << " " << (*it)->last_name << ", ";
		it++;
	}
	if (it != w.co_workers.end()) cout << (*it)->first_name << " " << (*it)->last_name;
	else cout << get_phrase(94);
	cout << get_phrase(46) << endl;

	int choices_str[4] = {95, 96, 97, 98};
	print_menu(4, 86, choices_str);

	choice = request_choice(4);
	if (choice == -1) return;	
	cout << endl;
	
	switch(choice)
	{
	case 1:
		// Compétences
		request_skills(w, "- " + get_phrase(99) + ": ");
		log_write("Added skills to " + w.first_name + " " + w.last_name);
		break;
	case 2:
		request_wrk_coll(w);
		log_write("New co_workers added to " + w.first_name + " " + w.last_name);
		break;
	case 3:
		zip = request_zip();
		w.set_zip_code(zip);
		log_write("zip code of " + w.first_name + " " + w.last_name + " modified: " + zip);
		break;
	case 4:
		if (w.employed())
		{
			auto co_workers = company_employees(*w.company);
			co_workers->remove(&w);
			request_wrk_cmp(w);
			// Anti-double
			w.co_workers.remove(*co_workers);
			w.co_workers.addlast(*co_workers);
			delete co_workers;
		}
		else request_wrk_cmp(w);
		break;
	}
}

void delete_worker(Worker& w)
{
	bool choice;

	print_title(100);
	cout << get_phrase(64) + "\n";
	choice = request_yn_choice();
	cout << endl;

	if(choice)
	{
		w.remove_from_coll();
		delete &w;
		cout << get_phrase(101) << endl;
		log_write("Worker deleted: " + w.first_name + " " + w.last_name);
	}
	else cout << get_phrase(66) << endl;
}
