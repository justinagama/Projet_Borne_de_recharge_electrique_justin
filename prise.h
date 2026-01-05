/**
 * @file prise.h
 * @author —
 * @date —
 * @brief Interface de gestion de la prise de charge.
 *
 * Ce fichier définit les fonctions permettant
 * de contrôler la prise et la trappe associée
 * à la borne de recharge.
 */

#ifndef PRISE_H
#define PRISE_H

#include <donnees_borne.h>
#include <memoire_borne.h>

/**
 * @brief Initialise la prise et la trappe.
 */
void prise_init(void);

/**
 * @brief Verrouille la trappe de la prise.
 */
void verrouiller_trappe(void);

/**
 * @brief Déverrouille la trappe de la prise.
 */
void deverrouiller_trappe(void);

/**
 * @brief Définit l’état du voyant de la prise.
 *
 * @param ledstate État du voyant
 */
void prise_set_prise(led ledstate);

#endif // PRISE_H
