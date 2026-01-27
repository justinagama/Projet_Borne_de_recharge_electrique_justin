/**
 * @file boutton.c
 * @author —
 * @date —
 * @brief Gestion des boutons physiques de la borne de recharge.
 *
 * Ce module permet :
 * - l'initialisation de l'accès aux boutons,
 * - la détection de l'appui sur le bouton de charge,
 * - la détection de l'appui sur le bouton d'arrêt (stop).
 *
 * Les boutons sont lus via une mémoire partagée.
 */

#include "boutton.h"

/**
 * @brief Pointeur vers la mémoire partagée des boutons.
 */
entrees* io_bt;

/**
 * @brief Identifiant de la mémoire partagée associée aux boutons.
 */
int shmid_bt;

/**
 * @brief Initialise l'accès aux boutons physiques.
 *
 * Cette fonction associe la mémoire partagée
 * afin de pouvoir lire l'état des boutons.
 */
void boutons_initialiser()
{
    io_bt = acces_memoire(&shmid_bt);
}

/**
 * @brief Attend l'appui sur le bouton de charge.
 *
 * Cette fonction surveille l'état du bouton de charge
 * pendant une durée maximale de 60 secondes.
 *
 * @return 1 si le bouton est pressé, 0 sinon
 */
int boutons_appuie_boutons_charge(void)
{
    int etat_btn = 0;   /**< État du bouton charge */
    int time_att;       /**< Temps de référence pour la temporisation */

    timer_raz(&time_att);

    io_bt->bouton_charge = 0;

    /**
     * Attente de l'appui sur le bouton ou expiration du délai
     */
    while ((io_bt->bouton_charge == 0) &&
           (timer_valeur(time_att) <= 60))
    {
        usleep(1000);
    }

    etat_btn = io_bt->bouton_charge;

    /**
     * Réinitialisation de l'état du bouton
     */
    io_bt->bouton_charge = 0;

    return etat_btn;
}

/**
 * @brief Vérifie l'état du bouton d'arrêt (STOP).
 *
 * Cette fonction lit l'état du bouton STOP
 * puis le réinitialise immédiatement.
 *
 * @return 1 si le bouton STOP est pressé, 0 sinon
 */
int bouton_appuie_boutons_stop(void)
{
    int etat_btn = io_bt->bouton_stop;

    /**
     * Réinitialisation de l'état du bouton STOP
     */
    io_bt->bouton_stop = 0;

    return etat_btn;
}
