#include "search.h"

// Rechercher parmi les chercheurs d'emploi pour des profils qui 
// correspondent à un poste à pourvoir (recherche par zip_code ou pas)
List<Worker*>* srch_wrk_profile_job(List<Worker*>& workers, Job& j, bool zip_code)
{
	List<Worker*>* l = new List<Worker*>();
	List<int> li = List<int>();
	auto it = workers.begin();
	int n;
	while (it != workers.end())
	{
		if (!(*it)->employed())
		{
			n = j.skills.in_common((*it)->skills);
			if (n > 0)
			{
				if (zip_code)
				{
					if (j.company->zip_code == (*it)->zip_code)
					{
						l->addlast(*it);
						li.addlast(n);
					}
				}
				else
				{
					l->addlast(*it);
					li.addlast(n);
				}
			}
			it++;
		}
	}
	l->sort(li, false);
	return l;
}

// Rechercher parmi les jobs ceux qui correspondent
// au profil de w (recherche par zip_code ou pas)
List<Job*>* srch_job_profile_wrk(List<Job*>& jobs, Worker& w, bool zip_code)
{
	List<Job*>* l = new List<Job*>();
	auto it = jobs.begin();
	List<int> li = List<int>();
	int n;
	while (it != jobs.end())
	{
		n = (*it)->skills.in_common(w.skills);
		if (n > 0)
		{
			if (zip_code)
			{
				if (w.zip_code == (*it)->company->zip_code)
				{
					l->addlast(*it);
					li.addlast(n);
				}
			}
			else
			{
				l->addlast(*it);
				li.addlast(n);
			}
		}
		it++;
	}
	l->sort(li, false);
	return l;
}

// Retourne co_workers employés par company
List<Worker*>* srch_coll_from_cmp(Worker& w, Company& c)
{
	List<Worker*>* l = new List<Worker*>();
	auto it = w.co_workers.begin();
	while (it != w.co_workers.end())
	{
		if (*(*it)->company == c) l->addlast(*it);
		it++;
	}
	return l;
}

// retourne les anciens collègues employés aux entreprises 
// qui recherchent les compétences de w
List<Worker*>* srch_coll_skills(List<Job*>& jobs, Worker& w)
{
	List<Job*>* lj = srch_job_profile_wrk(jobs, w, false);
	List<Company*> lc = List<Company*>();
	List<Worker*>* lw = new List<Worker*>();
	Company *c;

	// convertir en companies
	auto it = lj->begin();
	while (it != lj->end())
	{
		c = (*it)->company;
		if (!lc.has(c)) lc.addlast(c);
		it++;
	}
	delete lj;
	
	// construire la liste de workers collègues
	auto it2 = w.co_workers.begin();
	while (it2 != w.co_workers.end())
	{
		if (lc.has((*it2)->company)) lw->addlast(*it2);
		it2++;
	}
	return lw;
}

void load_srch()
{
	return;
}
