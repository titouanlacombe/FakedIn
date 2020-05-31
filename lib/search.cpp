#include "search.h"

Company* cmp_login(List<Company*>* companies, std::string name)
{
	Company* c;
	auto cur = companies->first;

	while (cur != NULL)
	{
		if (cur->data->name == name) c = cur->data;
		cur = cur->next;
	}
	if (cur == NULL) return NULL;
	else return c;
}

Worker* wrk_login(List<Worker*>* workers, std::string first_name, std::string last_name)
{
	Worker* w;
	auto cur = workers->first;

	while (cur != NULL)
	{
		if (cur->data->first_name == first_name && cur->data->last_name == last_name) w = cur->data;
		cur = cur->next;
	}
	if (cur == NULL) return NULL;
	else return w;
}

Job* job_login(List<Job*>* jobs, Company* c, std::string title)
{
	Job* j;
	auto cur = jobs->first;

	while (cur != NULL)
	{
		if (cur->data->title == title && cur->data->company == c) j = cur->data;
		cur = cur->next;
	}
	if (cur == NULL) return NULL;
	else return j;
}

// Rechercher parmi les chercheurs d'emploi pour des profils qui 
// correspondent à un poste à pourvoir (recherche par zip_code ou pas)
List<Worker*>* srch_wrk_profile_job(List<Worker*> *workers, Job* j, bool zip_code)
{
	List<Worker*>* l = new List<Worker*>;
	auto cur = workers->first;

	while (cur != NULL)
	{
		if (!cur->data->employed())
		{
			if (zip_code)
			{
				if (j->company->zip_code == cur->data->zip_code && j->skills->in_common(cur->data->skills) > 0) l->addlast(cur->data);
			}
			else
			{
				if (j->skills->in_common(cur->data->skills) > 0) l->addlast(cur->data);
			}
			cur = cur->next;
		}
	}
	return l;
}

// Rechercher parmi les jobs ceux qui correspondent
// au profil de w (recherche par zip_code ou pas)
List<Job*>* srch_job_profile_wrk(List<Job*> *jobs, Worker* w, bool zip_code)
{
	List<Job*>* l = new List<Job*>;
	auto cur = jobs->first;

	while (cur != NULL)
	{
		if (zip_code)
		{
			if (w->zip_code == cur->data->company->zip_code && cur->data->skills->in_common(w->skills) > 0) l->addlast(cur->data);
		}
		else
		{
			if (cur->data->skills->in_common(w->skills) > 0) l->addlast(cur->data);
		}
		cur = cur->next;
	}
	return l;
}

// Retourne colleagues employés par company
List<Worker*>* srch_coll_from_cmp(Worker *w, Company *c)
{
	List<Worker*>* l = new List<Worker*>;
	auto cur = w->colleagues->first;

	while (cur != NULL)
	{
		if (cur->data->company == c) l->addlast(cur->data);
		cur = cur->next;
	}
	return l;
}

// retourne les anciens collègues employés aux entreprises 
// qui recherchent les compétences de w
List<Worker*>* srch_coll_skills(List<Job*> *jobs, Worker *w)
{
	List<Job*>* lj = srch_job_profile_wrk(jobs, w, false);
	List<Company*>* lc = new List<Company*>;
	List<Worker*>* lw = new List<Worker*>;

	// convertir en companies
	auto tmp = lj->first;
	while (tmp != NULL)
	{
		if (!lc->has(tmp->data->company)) lc->addlast(tmp->data->company);
		tmp = tmp->next;
	}
	
	// construire la liste de workers collègues
	auto tmp2 = w->colleagues->first;
	while (tmp2 != NULL)
	{
		if (lc->has(tmp2->data->company)) lw->addlast(tmp2->data);
		tmp2 = tmp2->next;
	}
	
	delete lj;
	delete lc;
	
	return lw;
}

void load_srch()
{
	return;
}
