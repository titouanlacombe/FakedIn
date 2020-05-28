#include "group.h"

Group::Group(){

}

Group::~Group(){

}

int Group::g_size(){
    return list_wrk->length;
}

Worker* Group::g_index(int const id){
    return NULL;
}

bool Group::g_colleagues(int const id_a, int const id_b){
    return false;
}

bool Group::g_linked(int const id_a, int const id_b){
    return false;
}
