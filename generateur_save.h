#ifndef GENERATEUR_SAVE_H
#define GENERATEUR_SAVE_H
#include <lcarte.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "voyant.h"
#include "timer.h"
#include "boutton.h"
#include "prise.h"

void generateur_initialiser(void);
void generateur_charger(void);
void generateur_mef (void);
void generateur_deconnecter(void);
void generateur_generer_PWM(pwm tension);
void generateur_ouvrir_AC(void);
void generateur_fermer_AC(void);
float generateur_tension(void);

#endif // GENERATEUR_SAVE