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
	string choice;

	cout << "~~ Menu Principal ~~\n\n";
	cout << "Vous êtes:\n";
	cout << "\t1. Une Entreprise\n";
	cout << "\t2. Un Travailleur\n";
	cout << "\n";
	
	do
	{
		cout << "Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
	} while (choice != "1" && choice != "2" && choice != "q");

	cout << "\n";

	switch(choice[0])
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
	string choice;

	cout << "Vous souhaitez:\n";
	cout << "\t1. Créér un nouveau compte Entreprise\n";
	cout << "\t2. Vous connecter a votre compte Entreprise\n";
	
	do
	{
		cout << "Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
	} while (choice != "1" && choice != "2" && choice != "q");

	cout << "\n";

	switch(choice[0])
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

	cout << "~~ Création du compte Entreprise ~~\n\n";
	cout << "Merci d'indiquer:\n";

	cout << "-Le nom de votre entreprise: ";
	cin >> name;
	cout << "-Le code postal de votre entreprise: ";
	cin >> zip;
	cout << "-L'adresse mail de votre entreprise: ";
	cin >> mail;
	cout << endl;

	c = new Company(name, zip, mail);
	companies->addlast(c);

	cout << "Compte Entreprise créé\n" << endl;
	log_write("New Company created: " + name + ", " + zip + ", " + mail);

	company_menu(c);
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

		if (name == "q") return;
		c = srch_cmp_list(companies, name);
		if (c == NULL) cout << "Erreur: l'Entreprise '" << name << "' n'existe pas\n";
	} while (c == NULL);
	
	cout << "\n";
	
	company_menu(c);
}

void company_menu(Company* c)
{
	string choice;
	
	cout << "~~ Menu Entreprise (" << c->name << ") ~~\n\n";
	cout << "Vous voulez:\n";
	cout << "\t1. Faire une recherche parmi les chercheurs d'emploi\n";
	cout << "\t2. Créér une nouvelle offre d'emploi\n";
	cout << "\t3. Supprimer une offre d'emploi\n";
	cout << "\t4. Supprimer votre compte Entreprise\n";
	cout << "\t5. Retour au menu principal\n";
	cout <<	"\n";
	
	do
	{
		cout << "Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
	} while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "q");

	cout << "\n";

	switch(choice[0])
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
	string title, zip;
	Job *j;

	cout << "~~ Recherche de travailleur ~~\n\n";

	do
	{
		cout << "Entrez le titre du poste vacant: ";
		cin >> title;

		j = srch_job_list(jobs, c, title);
		if (c == NULL) cout << "Erreur: le poste '" << title << "' n'existe pas\n";
	} while (c == NULL);

	cout << "\n";

	do
	{
		cout << "Voulez vous ne voir que les travailleur du même code postal (o/n): ";
		cin >> zip;
	} while (zip != "o" && zip != "n");

	cout << "\n";

	resultats = srch_wrk_profile_job(workers, j, zip == "o");

	cout << "Résultats:\n";
	resultats->print();

	delete resultats;
}

void create_job(Company* c)
{
	List<string>* skills = new List<string>;
	string title, skills_raw, tmp, skills_str;
	Job* j;

	cout << "~~ Création d'offre d'emploi ~~\n\n";
	cout << "Merci d'indiquer:\n";

	cout << "-Le titre du poste: ";
	cin >> title;
	cout << "-Indiquez les compétences requises pour ce poste (Compétence 1,Compétence 2...): ";
	cin >> skills_raw;

	while (mygetline(skills_raw, tmp, ','))
	{
		skills->addlast(tmp);
		skills_str += tmp;
	}
	
	j = new Job(title, skills, c);
	jobs->addlast(j);

	cout << "Offre d'emploi créée" << endl;
	log_write("New Job created: " + title + ", skills: " + skills_str);
}

void delete_job(Company* c)
{
	string title;
	Job* j;

	cout << "~~ Suppression d'offre d'emploi ~~\n\n";

	do
	{
		cout << "Entrez le titre de l'offre d'emploi a suprimmer ('q' pour quitter): ";
		cin >> title;

		if (title == "q") return;
		j = srch_job_list(jobs, c, title);
		if (j == NULL) cout << "Erreur: l'offre d'emploi '" << title << "' n'existe pas\n";
	} while (j == NULL);
	
	cout << "\n";
	
	jobs->remove(j);

	cout << "Offre d'emploi supprimée" << endl;
	log_write("Job " + title + " from " + c->name + " deleted");

	delete j;
}

void delete_company(Company* c)
{
	List<Job*>* lj;
	List<Worker*>* lw;
	string choice;

	cout << "~~ Suppression de compte Entreprise ~~\n\n";
	
	cout << "Voulez vous vraiment suprimer votre compte ?\n";
	cout << "Entrez 'o' pour confirmer: ";
	cin >> choice;

	cout << "\n";

	if(choice == "o")
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
	else
	{
		cout << "Suppression annulée" << endl;
	}
}

void pre_worker()
{
	string choice;

	cout << "Vous souhaitez:\n";
	cout << "\t1. Créér un nouveau compte Travailleur\n";
	cout << "\t2. Vous connecter a votre compte Travailleur\n";
	cout << "\n";

	do
	{
		cout << "Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
	} while (choice != "1" && choice != "2" && choice != "q");

	cout << "\n";
	
	switch(choice[0])
	{
	case '1':
		create_worker();
		break;
	case '2':
		login_worker();
		break;
	case 'q':
		break;
	}
}

void create_worker()
{
	string first_name, last_name, email, zip;
	string skills_raw, coll_str, company_name, tmp;
	Worker* w, *coll;
	Company* c = NULL;

	cout << "~~ Création de profil Travailleur ~~\n\n";
	cout << "Merci d'indiquer:\n";
	cout << "-Votre nom: ";
	cin >> last_name;
	cout << "-Votre prénom: ";
	cin >> first_name;
	cout << "-Votre adresse email: ";
	cin >> email;
	cout << "-Votre code postal: ";
	cin >> zip;

	w = new Worker(first_name, last_name, email);

	// Compétences
	cout << "-Indiquez vos compétences (Compétence 1,Compétence 2...): ";
	cin >> skills_raw;

	while (mygetline(skills_raw, tmp, ','))
	{
		w->add_skill(tmp);
	}
	
	// Collegues
	do
	{
		cout << "Entrez le nom d'un collègue (nom prénom) (vide pour arreter): ";
		cin >> coll_str;
		if (coll_str != "")
		{
			mygetline(coll_str, tmp, ' ');
			coll = srch_wrk_list(workers, tmp, coll_str);
			if (coll == NULL) cout << "Erreur: le Travailleur '" + tmp + " " + coll_str + "' n'existe pas\n";
			else w->add_colleague(coll);
		}
	} while (coll_str != "");

	// Entreprise
	do
	{
		cout << "Entrez le nom de votre Entreprise (vide pour aucune): ";
		cin >> tmp;
		if (tmp != "")
		{
			c = srch_cmp_list(companies, tmp);
			if (c == NULL) cout << "Erreur: l'Entreprise '" + tmp + "' n'existe pas\n";
			else w->set_company(c);
		}
	} while (tmp != "" && c == NULL);

	cout << "\nProfil créé\n" << endl;
	log_write("New worker created: " + first_name + " " + last_name);

	worker_menu(w);
}

void login_worker()
{
	Worker* w;
	string full_name, first_name;

	cout << "~~ Connexion Travailleur ~~\n\n";
	do
	{
		cout << "Entrez votre nom (nom prénom) ('q' pour quitter): ";
		cin >> full_name;
		if (full_name == "q") return;

		mygetline(full_name, first_name, ' ');
		w = srch_wrk_list(workers, first_name, full_name);
		if (w == NULL) cout << "Erreur: le Travailleur '" + first_name + " " + full_name + "' n'existe pas\n";
	} while (w == NULL);
	
	cout << "\n";

	worker_menu(w);
}

void worker_menu(Worker* w)
{
	string choice;

	cout << "~~ Menu Employé (" << w->first_name << " " << w->last_name << ") ~~\n\n";
	cout << "Vous voulez:\n";
	cout << "\t1. Chercher un nouvel emploi\n";
	cout << "\t2. Rechercher un profil parmis vos ancien collègue\n";
	cout << "\t3. Modifier votre profil\n";
	cout << "\t4. Supprimer votre profil\n";
	cout << "\t5. Retour au menu principal\n";
	cout << "\n";
	
	do
	{
		cout << "Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
	} while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "q");

	cout << "\n";

	switch(choice[0])
	{
	case '1':
		search_job(w);
		break;
	case '2':
		search_coll(w);
		break;
	case '3':
		modify_worker(w);
		break;
	case '4':
		delete_worker(w);
		break;
	case 'q':
		break;
	}
}

void search_job(Worker* w)
{
	List<Job*>* results;
	char zip;

	cout << "~~ Recherche d'offre d'emploi ~~\n\n";

	do
	{
		cout << "Voulez vous ne voir que les travailleur du même code postal (o/n): ";
		cin >> zip;
	} while (zip != 'o' && zip != 'n');
	
	cout << "\n";

	results = srch_job_profile_wrk(jobs, w, zip == 'o');
	results->print();

	delete results;
}

void search_coll(Worker* w)
{
	List<Worker*>* results;
	Company* c;
	string name;
	string choice;

	cout << "~~ Recherche parmis vos anciens collègues ~~\n\n";
	cout << "Voulez vous:\n";
	cout << "\t1. Trouver des anciens collegues travaillant dans une certaine entreprise\n";
	cout << "\t2. Trouver des anciens collegues travaillant dans une entreprise cherchant votre profil\n";
	cout << "\n";
	
	do
	{
		cout << "Entrez votre choix ('q' pour quitter): ";
		cin >> choice;
		if (choice == "q") return;
	} while (choice != "1" && choice != "2");
	
	cout << "\n";

	switch(choice[0])
	{
	case '1':
		do
		{
			cout << "Indiquez le nom de l'entreprise dans laquelle vous cherchez vos anciens collègues: ";
			cin >> name;
			c = srch_cmp_list(companies, name);
			if (c == NULL) cout << "Erreur: l'Entreprise '" + name + "' n'existe pas\n";
		} while (c == NULL);
		
		results = srch_coll_from_cmp(w, c);
		results->print();
		break;
	case '2':
		results = srch_coll_skills(jobs, w);
		results->print();
		break;
	}
	delete results;
}

void modify_worker(Worker* w)
{
	string skills_raw, tmp, coll_raw, zip, skills_str, coll_str;
	Worker* coll;
	Company* c;
	string choice;

	cout << "~~ Modification du compte Travailleur ~~\n\n"

	"Votre profil actuel: \n"
	<< w->first_name << " " << w->last_name << "\n" 
	<< "email: " << w->email << " Code postal: " << w->zip_code << "\n";
	if(w->employed()) cout << "Travaille à: " << w->company;
	cout << "Skills: ";
	w->skills->printl();
	cout << "Collègues: ";
	w->colleagues->printl();
	cout << endl;

	cout << "Que voulez vous modifier ?\n";
	cout << "\t1. Ajouter une compétence\n";
	cout << "\t2. Ajouter un collègue de travail\n";
	cout << "\t3. Nouveau code postal\n";
	cout << "\t4. Nouvelle entreprise\n";
	cout << "\n";

	do
	{
		cout << "Entrez votre choix ('q' pour annuler): ";
		cin >> choice;
		if (choice == "q") return;
		cout << endl;
	} while (choice != "1" && choice != "2" && choice != "3" && choice != "4");
	
	cout << "\n";
	
	switch(choice[0])
	{
	case '1':
		// Compétences
		cout << "-Indiquez vos nouvelles compétences (Compétence 1,Compétence 2...): ";
		cin >> skills_raw;

		while (mygetline(skills_raw, tmp, ','))
		{
			w->add_skill(tmp);
			skills_str += tmp;
		}
		log_write("Added skills to " + w->first_name + " " + w->last_name + ": " + skills_str);
		break;
	case '2':
		// Collegues
		do
		{
			cout << "Entrez le nom d'un collègue (nom prénom) (vide pour arreter): ";
			cin >> coll_raw;
			if (coll_raw != "")
			{
				mygetline(coll_raw, tmp, ' ');
				coll = srch_wrk_list(workers, tmp, coll_raw);
				if (coll == NULL) cout << "Erreur: le Travailleur '" + tmp + " " + coll_raw + "' n'existe pas\n";
				else {
					w->add_colleague(coll);
					coll_str += tmp;
				}
			}
		} while (coll_raw != "");
		log_write("New colleagues added to " + w->first_name + " " + w->last_name + ": " + coll_str);
		break;
	case '3':
		cout << "Entrez votre nouveau code postal ('q' pour annuler): ";
		cin >> zip;
		if (zip == "q") return;
		w->set_zip_code(zip);
		log_write("zip code of " + w->first_name + " " + w->last_name + " modified: " + zip);
		break;
	case '4':
		// Entreprise
		do
		{
			cout << "Entrez le nom de votre nouvelle Entreprise (vide pour aucune): ";
			cin >> tmp;
			if (tmp != "")
			{
				c = srch_cmp_list(companies, tmp);
				if (c == NULL) cout << "Erreur: l'Entreprise '" + tmp + "' n'existe pas\n";
				else w->set_company(c);
			}
		} while (tmp != "" && c == NULL);
		if (tmp == "") w->set_company(NULL);
		break;
	}
}

void delete_worker(Worker* w)
{
	string choice;

	cout << "~~ Suppression de compte Travailleur ~~\n\n";
	
	cout << "Voulez vous vraiment suprimer votre compte ?\n";
	cout << "Entrez 'o' pour confirmer: ";
	cin >> choice;
	cout << "\n";

	if(choice == "o")
	{
		workers->remove(w);
		w->remove_from_coll();

		cout << "Travailleur supprimée" << endl;
		log_write("Worker deleted: " + w->first_name + " " + w->last_name);
		
		delete w;
	}
	else
	{
		cout << "Suppression annulée" << endl;
	}
}

void load_UI()
{
	return;
}
