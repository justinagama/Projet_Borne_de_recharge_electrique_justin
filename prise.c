#include "prise.h"

/**
 * @file prise.c
 * @brief Gestion des fonctions liées à la prise de charge et à la trappe.
 *
 * Ce fichier implémente les fonctions pour initialiser la prise,
 * verrouiller/déverrouiller la trappe, et configurer l'état des voyants associés.
 */

entrees *io_p;  /**< Pointeur vers la mémoire partagée pour la gestion de la prise. */
int shmid_p;    /**< Identifiant de la mémoire partagée. */

/**
 * @brief Initialise la gestion de la prise et de la trappe.
 *
 * Configure l'accès à la mémoire partagée pour contrôler l'état de la prise
 * et de la trappe.
 */
void prise_init(void) {
    io_p = acces_memoire(&shmid_p);
}

/**
 * @brief Déverrouille la trappe de la prise.
 *
 * La fonction active le voyant vert indiquant que la trappe est déverrouillée,
 * permettant ainsi d'insérer ou de retirer la prise.
 */
void deverrouiller_trappe(void) {
    io_p->led_trappe = VERT;
}

/**
 * @brief Verrouille la trappe de la prise.
 *
 * La fonction désactive le voyant de la trappe pour indiquer qu'elle est verrouillée,
 * empêchant l'utilisateur de débrancher la prise pendant la charge.
 */
void verrouiller_trappe(void) {
    io_p->led_trappe = OFF;
}

/**
 * @brief Configure l'état du voyant de la prise.
 *
 * Permet d'allumer ou d'éteindre le voyant associé à l'état de la prise
 * en fonction du paramètre fourni.
 *
 * @param ledstate État du voyant de la prise (VERT pour allumé, OFF pour éteint).
 */
void prise_set_prise(led ledstate) {
    io_p->led_prise = ledstate;
}
