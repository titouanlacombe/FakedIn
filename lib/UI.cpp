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

void home()
{
	char choice;

	do
	{
		cout << "~~ Menu Principal ~~\n\n"
		"Vous êtes:\n"
			"\t1. Une entreprise\n"
			"\t2. Un employé\n"
			"\t3. À la recherche d'un emploi\n\n"
		"Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
		cout << "\n";
	} while (choice != '1' && choice != '2' && choice != 'q');

	switch(choice)
	{
	case '1':
		pre_company();
		break;
	case '2':
		pre_worker();
		break;
	case 'q':
		break;
	}
}

void pre_company()
{
	char choice;

	do
	{
		cout << "~~ Menu Entreprise ~~\n\n"
			"Vous souhaitez:\n"
				"\t1. Créér un nouveau compte Entreprise\n"
				"\t2. Vous connecter a votre compte Entreprise\n"
		"Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
		cout << "\n";
	} while (choice != '1' && choice != '2' && choice != 'q');

	switch(choice)
	{
	case '1':
		create_company();
		break;
	case '2':
		login_company();
		break;
	case 'q':
		break;
	}
}

void create_company()
{
	string name, zip, mail;
	Company* c;

	cout << "~~ Création du compte Entreprise ~~\n\n"
		"Merci d'indiquer:\n"
			"\tLe nom de votre entreprise: ";
	cin >> name;
	cout << "\tLe code postal de votre entreprise: ";
	cin >> zip;
	cout << "h\tL'adresse mail de votre entreprise: ";
	cin >> mail;
	cout << endl;

	c = new Company(name, zip, mail);
	companies->addlast(c);

	log_write("New Company created: " + name + ", " + zip + ", " + mail);
	cout << "Compte Entreprise créé\n" << endl;
}

void login_company()
{
	Company* c;
	string name;

	cout << "~~ Connexion Entreprise ~~\n\n";
	do
	{
		cout << "Entrez le nom de votre Entreprise ('q' pour quitter): ";
		cin >> name;
		cout << "\n";

		if (name == "q") return;
		c = srch_cmp_list(companies, name);
		if (c == NULL) cout << "Erreur: l'Entreprise '" << name << "' n'existe pas\n";
	} while (c == NULL);
}

void company(Company* c)
{
	char choice;
	
	do
	{
		cout << "~~ Menu Entreprise (" << c->name << ") ~~\n\n"
		"Vous voulez:\n"
			"\t1. Faire une recherche parmi les chercheurs d'emploi\n\n"
			"\t2. Créér une nouvelle offre d'emploi\n"
			"\t3. Supprimer une offre d'emploi\n"
			"\t4. Supprimer votre compte Entreprise\n"
		"Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
		cout << "\n";
	} while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != 'q');

	switch(choice)
	{
	case '1':
		search_worker(c);
		break;
	case '2':
		create_job(c);
		break;
	case '3':
		delete_job(c);
		break;
	case '4':
		delete_company(c);
		break;
	case 'q':
		break;
	}
}

void search_worker(Company* c)
{
	List<Worker*>* resultats;
	string title;
	Job *j;
	char zip;

	do
	{
		cout << "Entrez le titre de l'offre d'emploi: ";
		cin >> title;
		cout << "\n";

		j = srch_job_list(jobs, c, title);
		if (c == NULL) cout << "Erreur: l'offre d'emploi '" << title << "' n'existe pas\n";
	} while (c == NULL);

	cout << "\n";

	do
	{
		cout << "Voulez vous ne voir que les travailleur du même code postal (o/n): ";
		cin >> zip;
		cout << "\n";
	} while (zip != 'o' && zip != 'n');

	cout << "\n";

	resultats = srch_wrk_profile_job(workers, j, zip == 'o');

	cout << "Résultats:\n";
	resultats->print();

	delete resultats;
}

void create_job(Company* c)
{
	List<string>* skills = new List<string>;
	string title, skills_raw, tmp;
	Job* j;

	cout << "~~ Création d'offre d'emploi' ~~\n\n"
		"Merci d'indiquer:\n"
		"Le titre du poste: ";
	cin >> title;
	cout << "Indiquez les compétences requises pour ce poste (Compétence 1,Compétence 2...): ";
	cin >> skills_raw;

	while (mygetline(skills_raw, tmp, ','))
	{
		skills->addlast(tmp);
	}
	
	j = new Job(title, skills, c);
	jobs->addlast(j);

	log_write("New Job created: " + title + ", skills: " + skills_raw);
	cout << "Offre d'emploi créée" << endl;
}

void delete_job(Company* c)
{
	string title;
	Job* j;

	do
	{
		cout << "Entrez le titre de l'offre d'emploi a suprimmer ('q' pour quitter): ";
		cin >> title;
		cout << "\n";

		if (title == "q") return;
		j = srch_job_list(jobs, c, title);
		if (j == NULL) cout << "Erreur: l'offre d'emploi '" << title << "' n'existe pas\n";
	} while (j == NULL);
	
	jobs->remove(j);

	cout << "Offre d'emploi supprimée" << endl;
	log_write("Job " + title + " from " + c->name + " deleted");

	delete j;
}

void delete_company(Company* c)
{
	List<Job*>* lj;
	List<Worker*>* lw;
	char choice;

	cout << "Voulez vous vraiment suprimer votre compte ?";
	cout << "Taper 'o' pour confirmer: ";
	cin >> choice;

	if(choice == 'o')
	{
		lj = company_jobs(jobs, c);
		*jobs -= *lj;
		lj->delete_data();
		delete lj;

		lw = company_employees(workers, c);
		auto tmp = lw->first;
		while (tmp != NULL)
		{
			tmp->data->company = NULL;
		}
		delete lw;

		companies->remove(c);

		cout << "Entreprise supprimée" << endl;
		log_write("Company deleted: " + c->name);
		
		delete c;
	}
}

void pre_worker(bool emp)
{
	string name, surname;
	cout << "~~ Profil utilisateur ~~\n\n"
	"Pour vous connecter saisissez votre nom \n"
	"Si vous souhaitez créer un nouveau profil utilisateur, saisissez n \n"
	"Si vous souhaitez annuler et retourner au menu principal, saisissez p: ";
	cin >> name;

	if (name == "n") create_wrk(emp);
	else if (name == "p") home();
	else
	{
		Worker* w = srch_wrk_list(workers, name, surname);
		if (w->employed()) employee(w);
		else seeker(w);
	}
}

void create_worker(bool emp)
{
	string name, surname, mail, zip, skill, company_name;
	Worker* coll = NULL;
	Company* c = NULL;

	cout << "~~ Creation de Profil Utilisateur ~~\n\n"
		"Merci d'indiquer:\n"
			"\tVotre nom: ";
	cin >> name;
	cout << "\tVotre prénom: ";
	cin >> surname;
	cout << "\tVotre adresse mail: ";
	cin >> mail;
	cout << "\tVotre code postal: ";
	cin >> zip;

	auto w = new Worker(surname, name, mail);

	do
	{
		cout << "\tIndiquez l'une de vos compétence: (entrez 'q' si vous avez terminé)";
		cin >> skill;
		if (skill != "q") w->add_skill(skill);
	} while (skill != "q");

	if (emp)
	{
		while (c == NULL)
		{
			cout << "\tIndiquez le nom de votre Entreprise: ";
			cin >> name;
			c = cmp_login(companies, company_name);
			if(c == NULL) cout << "L'entreprise " << company_name << " n'est pas sur FakedIn." << endl;
		}
		w->set_company(c);
	}

	do
	{
		cout << "\tIndiquez le prénom d'un de vos ancien collègues: (entrez 'q' pour quitter)";
		cin >> surname;
		if (surname != "q")
		{
			cout << "\tIndiquez le nom de famille de cet ancien collègue:";
			cin >> name;
			coll = srch_wrk_list(workers, name, surname);
			if(coll == NULL) cout << surname << " " << name << " n'est pas inscrit sur FakedIn." << endl;
			else
			{
				w->add_colleague(coll);
				cout << surname << " " << name << " ajouté à vos anciens collègues" << endl;
			}
		}
	} while (surname != "q");

	log_write("New Worker created: " + name + ", " + surname);
	cout << "\nProfil créé\n" << endl;
	
	if(emp) employee(w);
	else seeker(w);
}

void worker_menu(Worker* w)
{
	char choice;
	bool loop;

	do
	{
		cout << "~~ Menu Employé ~~\n\n"
		"Vous voulez:\n"
			"\t1. Modifier votre profil\n"
			"\t2. Supprimer votre profil\n"
			"\t3. Chercher un nouvel emploi\n"
			"\t4. Rechercher un profil parmis vos ancien collègue\n\n"
		"Entrez votre choix ('q' pour quitter, 'p' pour menu principal): ";
		cin >> choice;

		loop = false;
		switch(choice)
		{
		case '1':
			modify_wrk(w);
			break;
		case '2':
			delete_wrk(w);
			break;
		case '3':
			search_job(w);
			break;
		case '4':
			search_wrk(w);
			break;
		case 'p':
			home();
			break;
		case 'q':
			break;
		default:
			loop = true; // cin invalid
		}
	} while (loop);
}

void modify_worker(Worker* w)
{
	string zip, skill, company, name, surname;
	Worker* coll;
	Company* c;
	List<Worker*>* old_coworkers;
	char choice, new_emp;

	cout << "~~ Modification du Profil ~~\n\n"

	"Voici votre Profil: \n"
	<< w->first_name << " " << w->last_name << "\n" 
	<< w->email << " " << w->zip_code << "\n";
	if(w->employed()) cout << "travaille à " << w->company->name << "\n";
	cout << "Vous avez " << w->colleagues->length << " anciens collègues sur FakedIn\n";

	do
	{
		cout << "\nQue voulez vous modifier ?\n"
			"\t1. Ajouter une compétence\n"
			"\t2. Ajouter un ancien collègue de travail\n"
			"\t3. Nouveau code postal\n"
			"\t4. Nouveau Statut"
			"\t5. Nouvelle entreprise\n\n"
		"Entrez votre choix ('q' pour annuler): ";
		cin >> choice;
		cout << endl;
	} while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != 'q');
	
	switch(choice)
	{
	case '1':
		do
		{
			cout << "\tIndiquez l'une de vos compétence: (entrez 'q' si vous avez terminé)";
			cin >> skill;
			if(skill != "q") w->add_skill(skill);
		} while (skill != "q");
		log_write("New skills added on a Worker");
		break;
	case '2':
		do
		{
			cout << "\tIndiquez le prénom d'un de vos ancien collègues: (entrez 'q' pour quitter)";
			cin >> surname;
			if(surname != "q")
			{
				cout << "\tIndiquez le nom de famille de cet ancien collègue:";
				cin >> name;
				coll = srch_wrk_list(workers, name, surname);
				if(coll == NULL) cout << surname << " " << name << " n'est pas inscrit sur FakedIn." << endl;
				else
				{
					w->add_colleague(coll);
					cout << surname << " " << name << " ajouté à vos anciens collègues" << endl;
				}
			}
		} while (surname != "q");
		log_write("New colleagues added on a Worker");
		break;
	case '3':
		cout << "Entrez votre nouveau code postal (entrez 'q' pour annuler): ";
		cin >> zip;
		w->set_zip_code(zip);
		log_write("zip_code modified on a Worker");
		break;
	case '4':
		cout << "Si vous avez actuellement un Emploi, saisissez 1, sinon saisissez 0:";
		cin >> new_emp;

		if (!w->employed() && new_emp)
		{
			// = a trouve un emploi
			//case '5'
		}
		else
		{
			if (w->employed() && !new_emp)
			{
				// = a perdu son emploi
				old_coworkers = srch_coll_from_cmp(w, w->company);
				auto tmp = old_coworkers->first;
				while(tmp != NULL)
				{
					w->add_colleague(tmp->data);
					tmp = tmp->next;
				}

				w->set_company(NULL);
				log_write("Worker transfered from employee to seeker");
			}
			break;
		}
	case '5':
		while(c == NULL)
		{
			cout << "Entrez le nom de votre nouvelle entreprise (entrez 'q' pour annuler): ";
			cin >> company;
			cout << endl;
			if(company != "q")
			{
				c = cmp_login(companies, company);
				if(c == NULL) cout << "L'entreprise " << company << " n'est pas sur FakedIn." << endl;
			}
		}
		if(company != "q")
		{
			if(w->employed())
			{ 	
				//a changé d'entreprise
				// old_coworkers = company_coll(w, w->company);
				old_coworkers = new List<Worker *>;
				auto tmp = old_coworkers->first;
				while(tmp != NULL)
				{
					w->add_colleague(tmp->data);
					tmp = tmp->next;
				}

				w->set_company(c);
				log_write("Company modified on a Worker");
			} 
			else
			{
				w->set_company(c);
				log_write("Worker transfered from seeker to employee");
			}
		}
		break;
	}
	if(w->employed()) employee(w);
	else seeker(w);
}

void delete_worker(Worker* w)
{
	char choice;

	do
	{
		cout << "~~ Suppression de Profil Utilisateur ~~\n\n"
			"Pour confirmer la suppression de votre profil, tapez y\n"
			"Pour annuler, tapez n: ";
		cin >> choice;
		cout << endl;
	} while (choice != 'n' && choice != 'y');

	if (choice == 'y')
	{
		//remove des gens qui l'ont en collegue
		workers->remove(w);
		delete w;
		log_write("Worker deleted");
		cout << "Profil supprimé" << endl;
		home();
	}
	else
	{
		if(w->employed()) employee(w);
		else seeker(w);
	}
}

void search_job(Worker* w)
{
	string zip;
	//List<Job*>* j;
	cout << "~~ Menu de Parcour des Offres d'Emploi ~~\n\n"
		"Saisissez un code postal si vous souhaitez limitez votre recherche, sinon entrez 'q': ";
	cin >> zip;
	cout << endl;

	//if(zip == "q") j = job_search_skill(w, jobs);
	//else j = job_search_skill(w, jobs, zip);

	//afficher j liste des jobs ok

	if(w->employed()) employee(w);
	else seeker(w);
}

void search_coll(Worker* w)
{
	bool loop;
	char choice;
	string name;
	//List<Worker*>* res;

	do
	{
		cout << "~~ Menu de Recherche Parmis vos Anciens Collègues ~~\n\n"
		"Voulez vous:\n"
			"\t1. Trouver des anciens collegues travaillant dans une certaine entreprise\n"
			"\t2. Trouver des anciens collegues travaillant dans une entreprise cherchant votre profil\n"
		"Entrez votre choix: ";
		cin >> choice;
		cout << endl;

		loop = false;
		switch(choice)
		{
		case '1':
			cout << "Indiquez le nom de l'entreprise dans laquelle vous cherchez vos anciens collègues: ";
			cin >> name;
			cout << endl;
			//res = coll_search_cmp(w,cmp_login(companies,name));
			//afficher resultat
			break;
		case '2':
			//res = coll_search_skill(w, jobs);
			//afficher resultat
			break;
		default:
			loop = true; // cin invalid
		}
	}while(loop);

	if(w->employed()) employee(w);
	else seeker(w);
}

void load_UI()
{
	return;
}
