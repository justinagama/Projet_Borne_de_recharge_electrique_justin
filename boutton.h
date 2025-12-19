#ifndef BOUTONS_H
#define BOUTONS_H

#include <donnees_borne.h>
#include <memoire_borne.h>
#include "voyant.h"
#include "timer.h"
#include <unistd.h>

void boutons_initialiser();
int boutons_appuie_boutons_charge(void);
int bouton_appuie_boutons_stop(void);

#endif // BOUTONS_H
