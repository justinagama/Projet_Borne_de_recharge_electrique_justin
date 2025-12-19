#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <lcarte.h>
#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h>

#include "bool.h"
#include "voyant.h"

// structure boubleen pour qui servira pour certain test 
// typedef enum boole
// {
//     false,
//     true
// }Bool;


void lecteurcarte_initialiser();
void lecteurcarte_lire_carte();

#endif // LECTEURCARTE_H