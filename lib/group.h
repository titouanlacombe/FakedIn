#pragma once

#include "worker.h"

class Group
{
public:
    List<Worker*>* list_wrk;

    Group();
    ~Group();

    //retourne la taille du groupe
    int g_size();
    //retourne le travailleur d'id donné
    Worker* g_index(int const id);
    //determine si deux travailleurs sont collegues
    bool g_colleagues(int const id_a, int const id_b);
    //determine s'il existe une chaine de collegues entre deux travailleurs
    bool g_linked(int const id_a, int const id_b);
};

