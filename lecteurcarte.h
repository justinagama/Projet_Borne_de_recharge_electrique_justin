#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <lcarte.h>
#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h>

#include "bool.h"
#include "voyant.h"

/* Nous allons definire une variable globale pour stocker le numero/
 de la carte inseree pour charger la baterie cela 
 nous permetra de l'utiliser pour verifier si le vehicule appartient au meme client
*/ 

//int numero_carte_global;

void lecteurcarte_initialiser();
void lecteurcarte_lire_carte();

#endif // LECTEURCARTE_H
