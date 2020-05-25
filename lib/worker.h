#pragma once

#include "liste.h"
#include "mylog.h"

#define UNEMPLOYED 0
#define EMPLOYED 1

typedef struct worker
{
  char* first_name;
  char* last_name;
  char* email;
  char* zip_code;
  node* skills;
  node* colleagues;
  void* company;
} worker;

// créé un nouvel travailleur qui peut etre employée ou chercheur d'emploi
worker* wrk_create(char* first_name, char* last_name, char* email);

// supprime w
void wrk_delete(worker* w);

// rajoute une compétence a w
void wrk_add_skill(worker* w, char* skill);

// rajoute un collegue a w
void wrk_add_colleague(worker* w, worker* colleague);

// change le code postal de w
void wrk_set_zip_code(worker* w, char* zip_code);

// change l'entreprise de w
void wrk_set_company(worker* w, void* company);

// donne l'etat de w (EMPLOYED = employée, UNEMPLOYED = chercheur d'emploi)
int wrk_get_state(worker* w);
