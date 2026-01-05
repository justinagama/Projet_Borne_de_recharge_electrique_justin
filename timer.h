/**
 * @file timer.h
 * @author —
 * @date —
 * @brief Interface de gestion du timer logiciel.
 *
 * Ce fichier définit les fonctions permettant
 * de manipuler un timer basé sur une mémoire partagée.
 */

#ifndef TIMER_H
#define TIMER_H

#include <donnees_borne.h>
#include <memoire_borne.h>

/**
 * @brief Initialise l’accès au timer.
 */
void timer_initialiser();

/**
 * @brief Initialise une référence temporelle.
 *
 * @param tim Pointeur vers la variable de référence
 */
void timer_raz(int *tim);

/**
 * @brief Calcule le temps écoulé depuis une référence.
 *
 * @param tim Valeur de référence
 * @return Temps écoulé en secondes
 */
int timer_valeur(int tim);

#endif // TIMER_H
