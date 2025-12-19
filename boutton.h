#ifndef BOUTONS_H
#define BOUTONS_H

#include <donnees_borne.h>
#include <memoire_borne.h>
#include "voyant.h"
#include "timer.h"
#include <unistd.h>

void boutons_initialiser();
void boutons_dispo_off(void);
int boutons_attente_charge(void);
int bouton_stop(void);

#endif // BOUTONS_H
