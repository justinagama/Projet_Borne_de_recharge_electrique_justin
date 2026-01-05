/**
 * @file prise.c
 * @author —
 * @date —
 * @brief Gestion de la prise de charge et de la trappe.
 *
 * Ce module permet :
 * - l'initialisation de la prise,
 * - le verrouillage et le déverrouillage de la trappe,
 * - la gestion du voyant associé à la prise.
 *
 * Les informations sont échangées via une mémoire partagée.
 */

#include "prise.h"

/**
 * @brief Pointeur vers la mémoire partagée de la prise.
 */
entrees *io_p;

/**
 * @brief Identifiant de la mémoire partagée associée à la prise.
 */
int shmid_p;

/**
 * @brief Initialise la gestion de la prise et de la trappe.
 *
 * Cette fonction associe la mémoire partagée au pointeur
 * afin de permettre le contrôle de la prise et de la trappe.
 */
void prise_init(void)
{
    io_p = acces_memoire(&shmid_p);
}

/**
 * @brief Déverrouille la trappe de la prise.
 *
 * Active le voyant vert indiquant que la trappe
 * est déverrouillée et que la prise peut être manipulée.
 */
void deverrouiller_trappe(void)
{
    io_p->led_trappe = VERT;
}

/**
 * @brief Verrouille la trappe de la prise.
 *
 * Éteint le voyant de la trappe afin d’indiquer
 * que la prise est verrouillée pendant la charge.
 */
void verrouiller_trappe(void)
{
    io_p->led_trappe = OFF;
}

/**
 * @brief Définit l’état du voyant de la prise.
 *
 * Permet d’allumer ou d’éteindre le voyant
 * indiquant l’état de la prise.
 *
 * @param ledstate État du voyant (VERT, OFF, etc.)
 */
void prise_set_prise(led ledstate)
{
    io_p->led_prise = ledstate;
}
