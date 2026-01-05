/**
 * @file timer.c
 * @author —
 * @date —
 * @brief Gestion du timer logiciel de la borne.
 *
 * Ce module fournit des fonctions permettant :
 * - d'initialiser l'accès au timer,
 * - de remettre à zéro une référence temporelle,
 * - de mesurer un temps écoulé en secondes.
 *
 * Le timer repose sur une valeur incrémentée
 * dans une mémoire partagée.
 */

#include "timer.h"

/**
 * @brief Pointeur vers la mémoire partagée contenant le timer.
 */
entrees *io;

/**
 * @brief Identifiant de la mémoire partagée associée au timer.
 */
int shmid_t;

/**
 * @brief Initialise l’accès au timer.
 *
 * Associe la zone de mémoire partagée au pointeur
 * permettant d’accéder au compteur de secondes.
 */
void timer_initialiser()
{
    io = acces_memoire(&shmid_t);

    if (io == NULL) 
    {
        printf("Erreur pas de mem sh\n");
    }
}

/**
 * @brief Remet à zéro une référence temporelle.
 *
 * Cette fonction initialise la variable passée en paramètre
 * avec la valeur actuelle du compteur de secondes.
 *
 * @param tim Pointeur vers la variable de référence du temps
 */
void timer_raz(int *tim)
{
    *tim = io->timer_sec;
}

/**
 * @brief Retourne le temps écoulé depuis une référence.
 *
 * Calcule la différence entre la valeur actuelle du timer
 * et la valeur de référence fournie.
 *
 * @param tim Valeur de référence du temps
 * @return Temps écoulé en secondes
 */
int timer_valeur(int tim)
{
    int val = io->timer_sec - tim;
    return val;
}
