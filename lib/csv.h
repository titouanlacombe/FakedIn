#pragma once

#include "group.h"

//initialise les 4 fichiers csv qui contiendront les bases de données
//les crée si besoin et écrit la première ligne
void init_table();

//lis les 4 bases de données et construit les listes correspondantes
void load(List<Company*>* list_cmp, List<Job*>* list_job, Group* list_wrk_emp, Group* list_wrk_seeker);

//utilise les listes données en paramètre pour écrire les 4 bases de données
void save(List<Company*>* list_cmp, List<Job*>* list_job, Group* list_wrk_emp, Group* list_wrk_seeker);