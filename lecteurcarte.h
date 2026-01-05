/**
 * @file lecteurcarte.h
 * @author —
 * @date —
 * @brief Interface du module lecteur de carte.
 *
 * Ce fichier définit les fonctions permettant :
 * - l’initialisation du lecteur de carte,
 * - la lecture et l’authentification d’une carte client,
 * - le contrôle de l’accès à la borne de recharge.
 */

#ifndef LECTEURCARTE_H
#define LECTEURCARTE_H

#include <lcarte.h>
#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <unistd.h>

#include "bool.h"
#include "voyant.h"

/**
 * @brief Initialise le lecteur de carte.
 *
 * Configure les ports matériels nécessaires
 * à l’utilisation du lecteur.
 */
void lecteurcarte_initialiser();

/**
 * @brief Lit et traite une carte client.
 *
 * Cette fonction gère :
 * - l’insertion de la carte,
 * - l’authentification du client,
 * - le lancement de la charge si autorisé.
 */
void lecteurcarte_lire_carte();

#endif // LECTEURCARTE_H
