#ifndef BASE_CLIENTS_H
#define BASE_CLIENTS_H

#include <lcarte.h>
#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <lcarte.h>
#include <stdlib.h>
#include "bool.h"
#include "voyant.h"

// le code administrateur pour ajouter un client 
#define  CodeAdmi 2025
// structure boubleen pour qui servira pour certain test 


int base_clients_authentifier(int numero_carte);

void base_clients_ajouter();

void afficher_liste_clients();

void administrateur_mode();

#endif