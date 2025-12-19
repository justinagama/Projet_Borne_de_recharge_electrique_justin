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
void voyant_dispo(led Mode);
void voyant_blink_charge(led Mode);
void voyant_defaut(led Mode);
void voyant_prise(led Mode);


#endif