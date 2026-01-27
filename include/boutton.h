/**
 * @file boutton.h
 * @author —
 * @date —
 * @brief Interface de gestion des boutons de la borne.
 *
 * Ce fichier définit les fonctions permettant
 * d'interagir avec les boutons physiques :
 * - bouton de charge,
 * - bouton d'arrêt (STOP).
 */

#ifndef BOUTONS_H
#define BOUTONS_H

#include <donnees_borne.h>
#include <memoire_borne.h>
#include <unistd.h>

#include "voyant.h"
#include "timer.h"

/**
 * @brief Initialise l'accès aux boutons.
 */
void boutons_initialiser();

/**
 * @brief Attend l'appui sur le bouton de charge.
 *
 * @return 1 si le bouton est pressé, 0 sinon
 */
int boutons_appuie_boutons_charge(void);

/**
 * @brief Vérifie l'appui sur le bouton STOP.
 *
 * @return 1 si le bouton est pressé, 0 sinon
 */
int bouton_appuie_boutons_stop(void);

#endif // BOUTONS_H
