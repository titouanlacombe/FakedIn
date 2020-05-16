#pragma once

#include "liste.h"
#include "mylog.h"

typedef struct
{
  char * nom;
  char * prenom;
  char * mail;
  char * postal;
  node * skills;
  node * collegues;
  void * entreprise;
} worker;

//cree un nouvel employé/chercheur d'emploi
worker* create_worker(char * nom, char * prenom, char * mail);

//rajoute une competence au worker selctionner
void add_skill(worker, char * skill);

//rajoute collegue a worker selctionner
void add_collegues(worker, char * collegue);

//change postal du worker selectionner
void change_postal(worker, char * postal);

//change entreprise du worker selectionner
void change_entreprise(worker, void * entreprise);

//supprime le worker choisis
void delete_worker(worker);

//donne l'etat du worker employé ou chercheur d'emploi
bool etat_employe(worker);