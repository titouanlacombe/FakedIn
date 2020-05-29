#include <iostream>
#include <string>
#include "UI.h"

using namespace std;

void home()
{
	char choice;
	bool loop;
	do
	{
		cout << "====== Bienvenu sur FakedIn ! <insérez slogan> ======\n\n"
		"~~ Menu Principal ~~\n\n"
		"Vous êtes :\n"
			"\t1. Une entreprise\n"
			"\t2. Un employé\n"
			"\t3. À la recherche d'un emploi\n\n"
		"Entrez votre choix ('q' pour quitter) : ";
		cin >> choice;
		cout << endl;

		loop = false;
		switch(choice)
		{
		case '1':
			pre_company();
			break;
		case '2':
			pre_wrk(1);
			break;
		case '3':
			pre_wrk(0);
			break;
		case 'q':
			break;
		default:
			loop = true; // cin invalid
		}
	} while (loop);
}

void pre_company()
{
	string name;

	cout << "~~ Menu Entreprise ~~\n\n"
	"Pour vous connecter saisissez le nom de votre entreprise \n"
	"Si vous souhaitez créer un nouveau profil entreprise, saisissez n \n"
	"Si vous souhaitez annuler et retourner au menu principal, saisissez p : ";
	cin >> name;
	cout << endl;

	if (name == "n") create_cmp();
	else if (name != "p")
	{
		Company* c = cmp_search_name(companies, name);
		company(c);
	}
	else home();
}

void create_cmp()
{
	string name, zip, mail;
	Company* c;

	cout << "~~ Creation de Profil d'Entreprise ~~\n\n"
		"Merci d'indiquer :\n"
			"\t1. le nom de l'entreprise : ";
	cin >> name;
	cout << "\t2. un code postal : ";
	cin >> zip;
	cout << "h\t3. une adresse mail : ";
	cin >> mail;
	cout << endl;

	c = new Company(name, zip, mail);

	log_write("New Company created: " + name + ", " + zip + ", " + mail);
	cout << "Entreprise créée\n" << endl;
	company(c);
}

void company(Company* c)
{
	char choice;
	bool loop;
	
	do
	{
		cout << "~~ Menu Entreprise ~~\n\n"
		"Vous voulez :\n"
			"\t1. Supprimer le profil de votre entreprise\n"
			"\t2. Proposer une nouvelle offre d'emploi\n"
			"\t3. Supprimer une offre d'emploi\n"
			"\t4. Faire une recherche parmi les chercheurs d'emploi\n\n"
		"Entrez votre choix ('q' pour quitter, 'p' pour menu principal) : ";
		cin >> choice;
	
		loop = false;
		switch(choice)
		{
		case '1':
			delete_cmp(c);
			break;
		case '2':
			create_job(c);
			break;
		case '3':
			delete_job(c);
			break;
		case '4':
			search_seeker(c);
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

void pre_wrk(bool emp)
{
	string name, surname;
	cout << "~~ Profil utilisateur ~~\n\n"
	"Pour vous connecter saisissez votre nom \n"
	"Si vous souhaitez créer un nouveau profil utilisateur, saisissez n \n"
	"Si vous souhaitez annuler et retourner au menu principal, saisissez p : ";
	cin >> name;

	if (name == "n") create_wrk(emp);
	else if (name == "p") home();
	else
	{
		Worker* w = wrk_search_name(workers, name, surname);
		if (w->employed()) employee(w);
		else seeker(w);
	}
}

void create_wrk(bool emp)
{
	string name, surname, mail, zip, skill, company_name;
	Worker* coll = NULL;
	Company* c = NULL;

	cout << "~~ Creation de Profil Utilisateur ~~\n\n"
		"Merci d'indiquer :\n"
			"\tVotre nom : ";
	cin >> name;
	cout << "\tVotre prénom : ";
	cin >> surname;
	cout << "\tVotre adresse mail : ";
	cin >> mail;
	cout << "\tVotre code postal : ";
	cin >> zip;

	auto w = new Worker(surname, name, mail);

	do
	{
		cout << "\tIndiquez l'une de vos compétence : (entrez 'q' si vous avez terminé)";
		cin >> skill;
		if (skill != "q") w->add_skill(skill);
	} while (skill != "q");

	if (emp)
	{
		while (c == NULL)
		{
			cout << "\tIndiquez le nom de votre Entreprise : ";
			cin >> name;
			c = cmp_search_name(companies, company_name);
			if(c == NULL) cout << "L'entreprise " << company_name << " n'est pas sur FakedIn." << endl;
		}
		w->set_company(c);
	}

	do
	{
		cout << "\tIndiquez le prénom d'un de vos ancien collègues : (entrez 'q' pour quitter)";
		cin >> surname;
		if (surname != "q")
		{
			cout << "\tIndiquez le nom de famille de cet ancien collègue :";
			cin >> name;
			coll = wrk_search_name(workers, name, surname);
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

void employee(Worker* w)
{
	char choice;
	bool loop;

	do
	{
		cout << "~~ Menu Employé ~~\n\n"
		"Vous voulez :\n"
			"\t1. Modifier votre profil\n"
			"\t2. Supprimer votre profil\n"
			"\t3. Chercher un nouvel emploi\n"
			"\t4. Rechercher un profil parmis vos ancien collègue\n\n"
		"Entrez votre choix ('q' pour quitter, 'p' pour menu principal) : ";
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

void seeker(Worker* w)
{
	char choice;
	bool loop;

	do
	{
		cout << "~~ Menu Chercheur d'Emploi ~~\n\n"
		"Vous voulez :\n"
			"\t1. Modifier votre profil\n"
			"\t2. Supprimer votre profil\n"
			"\t3. Chercher un emploi\n"
			"\t4. Rechercher un profil parmis vos ancien collègue\n\n"
		"Entrez votre choix ('q' pour quitter, 'p' pour menu principal) : ";
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

void delete_cmp(Company* c)
{
	char choice;
	List<Job*>* cmp_job;

	do
	{
		cout << "~~ Suppression de Profil d'Entreprise ~~\n\n"
			"Pour confirmer la suppression de votre entreprise, tapez y\n"
			"Pour annuler, tapez n : ";
		cin >> choice;
	} while (choice != 'n' && choice != 'y');

	if(choice == 'n') company(c);
	else
	{
		cmp_job = job_search_cmp(jobs, c);
		log_write("Company deleted: " + c->name);
		*jobs -= *cmp_job;
		companies->remove(c);
		delete c;
		cout << "Entreprise supprimée\n" << endl;
		home();
	}
}

void create_job(Company* c)
{
	string title, skill;
	List<string>* all_skills = NULL;
	Job* j;

	cout << "~~ Création d'Offre d'Emploi' ~~\n\n"
		"Quel est le titre du poste : ";
	cin >> title;
	
	cout << "Indiquez une compétence requise pour ce poste : ";
	cin >> skill;

	do{
		all_skills->addlast(skill);
		cout << "Le cas échéant indiquez une autre compétence requise, sinon entrez 'q' : ";
		cin >> skill;
	}while(skill != "q");

	j = new Job(title, all_skills, c);
	jobs->addlast(j);

	log_write("New Job created");
	cout << "Offre d'emploi créée" << endl;
	company(c);
}

void delete_job(Company* c)
{
	string job_name;
	Job* j = NULL;

	while (j == NULL)
	{
		cout << "~~ Suppression d'Offre d'Emploi ~~\n\n"
		"\tIndiquez le titre de l'offre à supprimer : ";
		cin >> job_name;

		j = job_search_name(jobs, c, job_name);
	}

	jobs->remove(j);
	delete j;
	log_write("Job deleted");
	cout << "Offre d'emploi supprimée" << endl;
	company(c);
}

void search_seeker(Company* c)
{
	string zip, skill;
	List<string>* all_skills = NULL;

	cout << "~~ Menu de Parcour des Demandeurs d'Emploi ~~\n\n";
	cout << "Indiquez une compétence que vous recherchez : ";
	cin >> skill;

	while (skill != "q")
	{
		all_skills->addlast(skill);
		cout << "Le cas échéant indiquez une autre compétence recherchée, sinon entrez 'q' : ";
		cin >> skill;
	}
	cout << "Saisissez un code postal si vous souhaitez restreindre votre recherche, sinon tapez q :";
	cin >> zip;
	if(zip == "q") seek_search_skill(workers, all_skills);
	else seek_search_skill(workers, all_skills, zip);

	//afficher resultats
	company(c);
}

void modify_wrk(Worker* w)
{
	string zip, skill, company, name, surname;
	Worker* coll;
	Company* c;
	List<Worker*>* old_coworkers;
	char choice, new_emp;

	do
	{
		cout << "~~ Modification du Profil ~~\n\n"
		"Voici votre Profil : \n"
		<< w->first_name << " " << w->last_name << 
		"\n" << w->email << " " << w->zip_code;
		if(w->employed()) cout << "travaille à " << w->company->name << endl;
		cout << "\nQue voulez vous modifier ?\n"
			"\t1. Ajouter une compétence\n"
			"\t2. Ajouter un ancien collègue de travail\n"
			"\t3. Nouveau code postal\n"
			"\t4. Nouveau Statut"
			"\t5. Nouvelle entreprise\n\n"
		"Entrez votre choix ('q' pour annuler) : ";
		cin >> choice;
		cout << endl;
	} while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != 'q');
	
	switch(choice)
	{
	case '1':
		do
		{
			cout << "\tIndiquez l'une de vos compétence : (entrez 'q' si vous avez terminé)";
			cin >> skill;
			if(skill != "q") w->add_skill(skill);
		} while (skill != "q");
		log_write("New skills added on a Worker");
		break;
	case '2':
		do
		{
			cout << "\tIndiquez le prénom d'un de vos ancien collègues : (entrez 'q' pour quitter)";
			cin >> surname;
			if(surname != "q")
			{
				cout << "\tIndiquez le nom de famille de cet ancien collègue :";
				cin >> name;
				coll = wrk_search_name(workers, name, surname);
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
		cout << "Entrez votre nouveau code postal (entrez 'q' pour annuler) : ";
		cin >> zip;
		w->set_zip_code(zip);
		log_write("zip_code modified on a Worker");
		break;
	case '4':
		cout << "Si vous avez actuellement un Emploi, saisissez 1, sinon saisissez 0 :";
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
				old_coworkers = coll_search_cmp(w, w->company);
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
			cout << "Entrez le nom de votre nouvelle entreprise (entrez 'q' pour annuler) : ";
			cin >> company;
			cout << endl;
			if(company != "q")
			{
				c = cmp_search_name(companies, company);
				if(c == NULL) cout << "L'entreprise " << company << " n'est pas sur FakedIn." << endl;
			}
		}
		if(company != "q")
		{
			if(w->employed())
			{ 	
				//a changé d'entreprise
				old_coworkers = coll_search_cmp(w, w->company);
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

void delete_wrk(Worker* w)
{
	char choice;

	do
	{
		cout << "~~ Suppression de Profil Utilisateur ~~\n\n"
			"Pour confirmer la suppression de votre profil, tapez y\n"
			"Pour annuler, tapez n : ";
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
		"Saisissez un code postal si vous souhaitez limitez votre recherche, sinon entrez 'q' : ";
	cin >> zip;
	cout << endl;

	//if(zip == "q") j = job_search_skill(w, jobs);
	//else j = job_search_skill(w, jobs, zip);

	//afficher j liste des jobs ok

	if(w->employed()) employee(w);
	else seeker(w);
}

void search_wrk(Worker* w)
{
	bool loop;
	char choice;
	string name;

	do
	{
		cout << "~~ Menu de Recherche Parmis vos Anciens Collègues ~~\n\n"
		"Voulez vous :\n"
			"\t1. Trouver des anciens collegues travaillant dans une certaine entreprise\n"
			"\t2. Trouver des anciens collegues travaillant dans une entreprise cherchant votre profil\n"
		"Entrez votre choix : ";
		cin >> choice;
		cout << endl;

		loop = false;
		switch(choice)
		{
		case '1':
			cout << "Indiquez le nom de l'entreprise dans laquelle vous cherchez vos anciens collègues : ";
			cin >> name;
			cout << endl;
			coll_search_cmp(w,cmp_search_name(companies,name));
			//afficher resultat
			break;

		case '2':
			coll_search_skill(w, jobs);
			//afficher resultat
			break;
		default:
			loop = true; // cin invalid
		}
	}while(loop);

	if(w->employed()) employee(w);
	else seeker(w);
}
