/**
 * @file voyant.h
 * @author —
 * @date —
 * @brief Interface de gestion des voyants de la borne.
 *
 * Ce fichier définit les fonctions permettant
 * de contrôler les voyants lumineux :
 * - charge,
 * - disponibilité,
 * - défaut.
 */

#ifndef VOYANT_H
#define VOYANT_H

#include <lcarte.h>
#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h>

/*----------- Prototypes des fonctions ------------- */

/**
 * @brief Initialise l’accès aux voyants.
 */
void voyant_initialiser();

/**
 * @brief Définit l’état du voyant de charge.
 *
 * @param ledstate État du voyant
 */
void voyants_set_charge(led ledstate);

/**
 * @brief Définit l’état du voyant de disponibilité.
 *
 * @param Mode État ou couleur du voyant
 */
void voyant_set_dispo(led Mode);

/**
 * @brief Fait clignoter le voyant de charge.
 *
 * @param Mode Couleur du voyant
 */
void voyant_blink_charge(led Mode);

/**
 * @brief Définit l’état du voyant de défaut.
 *
 * @param Mode État ou couleur du voyant
 */
void voyant_set_defaut(led Mode);

/**
 * @brief Fait clignoter le voyant de défaut.
 *
 * @param Mode Couleur du voyant
 */
void voyant_blink_defaut(led Mode);

/**
 * @brief Indique si la borne est disponible.
 *
 * @return 1 si disponible, 0 sinon
 */
int voyant_dispo();

#endif // VOYANT_H
