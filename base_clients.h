/**
 * @file base_clients.h
 * @author —
 * @date —
 * @brief Interface de gestion de la base clients.
 *
 * Ce fichier définit les fonctions permettant
 * l’authentification et l’administration des clients
 * de la borne de recharge.
 */

#ifndef BASE_CLIENTS_H
#define BASE_CLIENTS_H

#include <lcarte.h>
#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>
#include <stdlib.h>

#include "bool.h"
#include "voyant.h"

/**
 * @brief Code administrateur requis pour modifier la base clients.
 */
#define CodeAdmi 2025

/**
 * @brief Vérifie si un numéro de carte est présent dans la base.
 *
 * @param numero_carte Numéro de carte à authentifier
 * @return 1 si authentifié, 0 sinon
 */
int base_clients_authentifier(int numero_carte);

/**
 * @brief Ajoute un client à la base de données.
 *
 * Nécessite une authentification administrateur.
 */
void base_clients_ajouter();

/**
 * @brief Affiche la liste des clients enregistrés.
 */
void afficher_liste_clients();

/**
 * @brief Lance le mode administrateur.
 *
 * Donne accès aux fonctions d’administration
 * de la base clients.
 */
void administrateur_mode();

#endif // BASE_CLIENTS_H
