#ifndef VOYANT_H
#define VOYANT_H


#include <lcarte.h>
#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h>
//#include <mem_sh.h>
//#include <donnees.h>

/*----------- Protoypes des fonctions ------------- */
void voyant_initialiser();
void voyants_set_charge(led ledstate);
void voyant_set_dispo(led Mode);
void voyant_blink_charge(led Mode);
void voyant_set_defaut(led Mode);
void voyant_blink_defaut(led Mode);
void voyant_set_prise(led Mode);
void voyant_set_trappe(led Mode);


#endif