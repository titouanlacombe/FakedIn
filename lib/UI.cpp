#include "UI.h"

using namespace std;

List<Company*>* companies;
List<Job*>* jobs;
List<Worker*>* workers;

void init_lists(List<Company*>* _companies, List<Job*>* _jobs, List<Worker*>* _workers)
{
	companies = _companies;
	jobs = _jobs;
	workers = _workers;
}

bool valid_email(string email)
{
	string copy(email), tmp;

	mygetline(copy, tmp, '@');
	if (tmp.empty()) return false;
	mygetline(copy, tmp, '.');
	if (tmp.empty()) return false;
	mygetline(copy, tmp);
	if (tmp.empty()) return false;
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

int request_choice(int nb)
{
	int choice;
	string tmp;
	do
	{
		cout << "Entrez votre choix ('q' pour annuler): ";
		getline(cin, tmp);
		if (tmp == "q") return -1;
		if (is_number(tmp)) {
			choice = stoi(tmp);
			if (choice > 0 && choice <= nb) return choice;
		}
		cout << "Erreur: choix invalide.";
	} while (true);
}

bool request_yn_choice()
{
	string tmp;
	do
	{
		cout << "Entrez votre choix o/n: ";
		getline(cin, tmp);
		if (tmp == "o") return true;
		else if (tmp == "n") return false;
		cout << "Erreur: choix invalide.";
	} while (true);
}

string request_cmp_name()
{
	string name;
	bool loop = true;
	do
	{
		cout << "-Le nom de votre entreprise: ";
		getline(cin, name);
		if (cmp_exist(companies, name)) cout << "Erreur: l'entreprise '" << name << "' existe déjà." << endl;
		else if (name.empty()) cout << "Erreur: le nom est vide." << endl;
		else if (name == "q") cout << "Erreur: le nom ne peut pas etre 'q'." << endl;
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
		if (name == "q") return NULL;

		c = srch_cmp_list(companies, name);
		if (c == NULL) cout << "Erreur: l'Entreprise '" << name << "' n'existe pas\n";
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
		cout << "-Votre adresse email (x@y.z): ";
		getline(cin, email);
		if (!valid_email(email)) cout << "Erreur: l'email '" << email << "' est invalide." << endl;
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
		cout << "-Votre code postal: ";
		getline(cin, zip);
		if (!valid_zip(zip)) cout << "Erreur: le code postal '" << zip << "' n'est pas un nombre." << endl;
		else loop = false;
	} while (loop);
	return zip;
}

string request_job_title(Company* c)
{
	string title;
	bool loop = true;
	do
	{
		cout << "-Le titre du poste: ";
		getline(cin, title);
		if (job_exist(jobs, c, title)) cout << "Erreur: l'offre '" << title << "' existe déjà dans votre entreprise." << endl;
		else if (title.empty()) cout << "Erreur: le titre de l'offre est vide." << endl;
		else if (title == "q") cout << "Erreur: le titre de l'offre ne peut pas etre 'q'." << endl;
		else loop = false;
	} while (loop);
	return title;
}

Job* request_job_login(Company* c, string request_phrase)
{
	Job* j;
	string title;
	bool loop = true;
	do
	{
		cout << request_phrase;
		getline(cin, title);
		if (title == "q") return NULL;
		
		j = srch_job_list(jobs, c, title);
		if (j == NULL) cout << "Erreur: l'offre d'emploi '" << title << "' n'existe pas\n";
		else loop = false;
	} while (loop);
	return j;
}

List<string>* request_skills(string request_phrase)
{
	auto skills = new List<string>;
	string skills_raw, tmp;
	cout << request_phrase;
	getline(cin, skills_raw);
	while (mygetline(skills_raw, tmp, ',')) skills->addlast(tmp);
	return skills;
}

void request_wrk_name(string& first_name, string& full_name)
{
	bool loop = true;
	do
	{
		cout << "-Votre nom (nom prénom): ";
		getline(cin, full_name);
		mygetline(full_name, first_name, ' ');
		if (wrk_exist(workers, first_name, full_name)) cout << "Erreur: le Travailleur '" << (first_name + " " + full_name) << "' existe déjà." << endl;
		else if (full_name.empty() || first_name.empty()) cout << "Erreur: nom ou prénom vide" << endl;
		else loop = false;
	} while (loop);
}

void request_wrk_coll(Worker* w)
{
	Worker* coll;
	string first_name, full_name;
	bool loop = true;
	do
	{
		cout << "-Entrez le nom d'un collègue (nom prénom) (vide pour arreter): ";
		getline(cin, full_name);
		if (!full_name.empty())
		{
			mygetline(full_name, first_name, ' ');
			coll = srch_wrk_list(workers, first_name, full_name);
			if (coll == NULL) cout << "Erreur: le Travailleur '" + first_name + " " + full_name + "' n'existe pas\n";
			else if (coll == w) cout << "Erreur: vous ne pouvez pas être votre propre collègue." << endl;
			else w->add_colleague(coll);
		}
		else loop = false;
	} while (loop);
}

void request_wrk_cmp(Worker* w)
{
	Company* c;
	string name;
	bool loop = true;
	do
	{
		cout << "-Entrez le nom de votre Entreprise (vide pour aucune): ";
		getline(cin, name);
		if (!name.empty())
		{
			c = srch_cmp_list(companies, name);
			if (c == NULL) cout << "Erreur: l'Entreprise '" + name + "' n'existe pas\n";
			else
			{
				w->set_company(c);
				loop = false;
			}
		}
		else {
			w->set_company(NULL);
			loop = false;
		}
	} while (loop);
}

void home()
{
	int choice;

	do
	{
		cout << "\n~~ Menu Principal ~~\n\n";
		cout << "Vous êtes:\n";
		cout << "\t1. Une Entreprise\n";
		cout << "\t2. Un Travailleur\n";
		cout << endl;
		
		choice = request_choice(2);
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
		}
	} while (true);
}

void pre_company()
{
	int choice;

	cout << "Vous souhaitez:\n";
	cout << "\t1. Vous connecter a votre compte Entreprise\n";
	cout << "\t2. Créér un nouveau compte Entreprise\n";
	cout << endl;
	
	choice = request_choice(2);
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
	Company* c;

	cout << "~~ Création du compte Entreprise ~~\n\n";
	
	cout << "Merci d'indiquer:\n";
	name = request_cmp_name();
	zip = request_zip();
	email = request_email();
	cout << endl;

	c = new Company(name, zip, email);
	companies->addlast(c);

	cout << "Compte Entreprise créé\n" << endl;
	log_write("New Company created: " + name + ", " + zip + ", " + email);

	company_menu(c);
}

void login_company()
{
	Company* c;
	string name;

	cout << "~~ Connexion Entreprise ~~\n\n";
	
	c = request_cmp_login("Entrez le nom de votre Entreprise ('q' pour annuler): ");
	if (c == NULL) return;
	
	cout << endl;
	
	company_menu(c);
}

void company_menu(Company* c)
{
	int choice;
	
	do
	{
		cout << "\n~~ Menu Entreprise (" << c->name << ") ~~\n\n";
		cout << "Vous voulez:\n";
		cout << "\t1. Faire une recherche parmi les chercheurs d'emploi\n";
		cout << "\t2. Créér une nouvelle offre d'emploi\n";
		cout << "\t3. Supprimer une offre d'emploi\n";
		cout << "\t4. Supprimer votre compte Entreprise\n";
		cout <<	endl;
		
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
			break;
		}
	} while (true);
}

void search_worker(Company* c)
{
	List<Worker>* results;
	string title;
	bool zip;
	Job *j;

	cout << "~~ Recherche de travailleur ~~\n\n";

	j = request_job_login(c, "Entrez le titre du poste vacant (q pour annuler): ");
	if (j == NULL) return;

	cout << endl;
	cout << "Voulez vous ne voir que les travailleur du même code postal ?\n";
	zip = request_yn_choice();

	cout << endl;

	results = srch_wrk_profile_job(workers, j, zip);

	cout << "Résultats:\n";
	results->print();
	cout << "\nEntrez une touche pour revenir au menu Entreprise.";
	getline(cin, title);

	delete results;
}

void create_job(Company* c)
{
	List<string>* skills;
	string title;
	Job* j;

	cout << "~~ Création d'offre d'emploi ~~\n\n";
	
	cout << "Merci d'indiquer:\n";
	title = request_job_title(c);
	skills = request_skills("-Indiquez les compétences requises pour ce poste (Compétence 1,Compétence 2...): ");

	j = new Job(title, skills, c);
	jobs->addlast(j);

	cout << "Offre d'emploi créée" << endl;
	log_write("New Job created: " + title);
}

void delete_job(Company* c)
{
	string title;
	Job* j;

	cout << "~~ Suppression d'offre d'emploi ~~\n\n";

	j = request_job_login(c, "Entrez le titre de l'offre d'emploi a suprimmer ('q' pour annuler): ");
	if (j == NULL) return;
	
	cout << endl;
	
	jobs->remove(j);

	cout << "Offre d'emploi supprimée" << endl;
	log_write("Job " + title + " from " + c->name + " deleted");

	delete j;
}

void delete_company(Company* c)
{
	List<Job*>* lj;
	List<Worker*>* lw;
	bool choice;

	cout << "~~ Suppression de compte Entreprise ~~\n\n";
	
	cout << "Voulez vous vraiment suprimer votre compte ?\n";
	choice = request_yn_choice();

	cout << endl;

	if(choice)
	{
		lj = company_jobs(jobs, c);
		*jobs -= *lj;
		lj->delete_data();
		delete lj;

		lw = company_employees(workers, c);
		auto tmp = lw->first;
		while (tmp != NULL)
		{
			tmp->data->set_company(NULL);
		}
		delete lw;

		companies->remove(c);

		cout << "Entreprise supprimée\n" << endl;
		log_write("Company deleted: " + c->name);
		
		delete c;
	}
	else cout << "Suppression annulée\n" << endl;
}

void pre_worker()
{
	int choice;

	cout << "Vous souhaitez:\n";
	cout << "\t1. Vous connecter a votre compte Travailleur\n";
	cout << "\t2. Créér un nouveau compte Travailleur\n";
	cout << endl;

	choice = request_choice(2);
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
	List<string>* skills;
	string first_name, full_name, email, zip;
	Worker* w;

	cout << "~~ Création de profil Travailleur ~~\n\n";
	
	cout << "Merci d'indiquer:\n";
	request_wrk_name(first_name, full_name);
	email = request_email();
	zip = request_zip();

	w = new Worker(first_name, full_name, email);
	w->set_zip_code(zip);
	workers->addlast(w);

	// Compétences
	skills = request_skills("-Indiquez vos compétences (Compétence 1,Compétence 2...): ");
	auto it = skills->first;
	while (it != NULL)
	{
		w->add_skill(it->data);
		it = it->next;
	}
	delete skills;
	
	request_wrk_coll(w);
	request_wrk_cmp(w);

	cout << "\nProfil créé\n" << endl;
	log_write("New worker created: " + first_name + " " + full_name);

	worker_menu(w);
}

void login_worker()
{
	bool loop;
	Worker* w;
	string full_name, first_name;

	cout << "~~ Connexion Travailleur ~~\n\n";
	loop = true;
	do
	{
		cout << "Entrez votre nom (nom prénom) ('q' pour annuler): ";
		getline(cin, full_name);
		if (full_name == "q") return;

		mygetline(full_name, first_name, ' ');
		w = srch_wrk_list(workers, first_name, full_name);
		if (w == NULL) cout << "Erreur: le Travailleur '" + first_name + " " + full_name + "' n'existe pas\n";
		else loop = false;
	} while (loop);
	
	cout << endl;

	worker_menu(w);
}

void worker_menu(Worker* w)
{
	int choice;

	do
	{
		cout << "\n~~ Menu Employé (" << w->first_name << " " << w->last_name << ") ~~\n\n";
		cout << "Vous voulez:\n";
		cout << "\t1. Chercher un nouvel emploi\n";
		cout << "\t2. Rechercher un profil parmis vos ancien collègue\n";
		cout << "\t3. Modifier votre profil\n";
		cout << "\t4. Supprimer votre profil\n";
		cout << endl;
		
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
			break;
		}
	} while (true);
}

void search_job(Worker* w)
{
	List<Job>* results;
	bool zip;
	string tmp;

	cout << "~~ Recherche d'offre d'emploi ~~\n\n";

	cout << "Voulez vous ne voir que les travailleur du même code postal ?\n";
	zip = request_yn_choice();
	
	cout << endl;

	results = srch_job_profile_wrk(jobs, w, zip);
	results->print();
	cout << "\nEntrez une touche pour revenir au menu Travailleur.";
	getline(cin, tmp);

	delete results;
}

void search_coll(Worker* w)
{
	List<Worker>* results;
	Company* c;
	string name;
	int choice;

	cout << "~~ Recherche parmis vos anciens collègues ~~\n\n";
	cout << "Voulez vous:\n";
	cout << "\t1. Trouver des anciens collegues travaillant dans une certaine entreprise\n";
	cout << "\t2. Trouver des anciens collegues travaillant dans une entreprise cherchant votre profil\n";
	cout << endl;
	
	choice = request_choice(2);
	if (choice == -1) return;	
	cout << endl;

	switch(choice)
	{
	case 1:
		c = request_cmp_login("Indiquez le nom de l'entreprise dans laquelle vous cherchez vos anciens collègues ('q' pour annuler): ");
		if (c == NULL) return;
		
		results = srch_coll_from_cmp(w, c);
		results->print();
		break;
	case 2:
		results = srch_coll_skills(jobs, w);
		results->print();
		break;
	}
	delete results;
	
	cout << "\nEntrez une touche pour revenir au menu Travailleur.";
	getline(cin, name);
}

void modify_worker(Worker* w)
{
	List<string>* skills;
	string zip;
	int choice;
	Node<string>* it2;

	cout << "~~ Modification du compte Travailleur ~~\n\n"

	"Votre profil actuel: \n"
	<< w->first_name << " " << w->last_name << "\n"
	<< "email: " << w->email << "\nCode postal: " << w->zip_code << endl;
	if(w->employed()) cout << "Travaille à: " << w->company->name << endl;
	cout << "Skills: ";
	w->skills->printl();
	cout << "Collègues: ";
	auto it = w->colleagues->first;
	while (it != w->colleagues->last)
	{
		cout << it->data->first_name << " " << it->data->last_name << ", ";
		it = it->next;
	}
	if (it != NULL) cout << it->data->first_name << " " << it->data->last_name;
	else cout << "Aucun";
	cout << endl;
	cout << endl;

	cout << "Que voulez vous modifier ?\n";
	cout << "\t1. Ajouter une compétence\n";
	cout << "\t2. Ajouter un collègue de travail\n";
	cout << "\t3. Nouveau code postal\n";
	cout << "\t4. Nouvelle entreprise\n";
	cout << endl;

	choice = request_choice(4);
	if (choice == -1) return;	
	cout << endl;
	
	switch(choice)
	{
	case 1:
		// Compétences
		skills = request_skills("-Indiquez vos nouvelles compétences (Compétence 1,Compétence 2...): ");
		it2 = skills->first;
		while (it2 != NULL)
		{
			w->add_skill(it2->data);
			it2 = it2->next;
		}
		delete skills;
		
		log_write("Added skills to " + w->first_name + " " + w->last_name);
		break;
	case 2:
		request_wrk_coll(w);
		log_write("New colleagues added to " + w->first_name + " " + w->last_name);
		break;
	case 3:
		zip = request_zip();
		w->set_zip_code(zip);
		log_write("zip code of " + w->first_name + " " + w->last_name + " modified: " + zip);
		break;
	case 4:
		request_wrk_cmp(w);
		break;
	}
}

void delete_worker(Worker* w)
{
	bool choice;

	cout << "~~ Suppression de compte Travailleur ~~\n\n";
	
	cout << "Voulez vous vraiment suprimer votre compte ?\n";
	choice = request_yn_choice();
	cout << endl;

	if(choice)
	{
		workers->remove(w);
		w->remove_from_coll();

		cout << "Travailleur supprimée\n" << endl;
		log_write("Worker deleted: " + w->first_name + " " + w->last_name);
		
		delete w;
	}
	else cout << "Suppression annulée\n" << endl;
}

void load_UI()
{
	return;
}
