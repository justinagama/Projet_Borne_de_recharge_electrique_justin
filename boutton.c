#include "boutton.h"


/**
 * @file boutons.c
 * @brief Gestion des boutons pour le contrôle de la borne de recharge.
 *
 * Ce module fournit des fonctions pour initialiser et gérer les boutons physiques
 * utilisés dans une borne de recharge, incluant le bouton de charge et le bouton d'arrêt.
 */

entrees* io_bt;
int shmid_bt;

/**
 * @brief Initialise l'accès aux boutons physiques.
 *
 * Cette fonction configure l'accès mémoire partagé pour interagir avec
 * les boutons de la borne de recharge.
 *
 * @note Elle doit être appelée avant d'utiliser toute autre fonction liée aux boutons.
 */
void boutons_initialiser()
{
    io_bt = acces_memoire(&shmid_bt);
}

/**
 * @brief Attend l'appui sur le bouton de charge dans une durée limitée.
 *
 * Cette fonction surveille l'état du bouton de charge pendant une période de 60 secondes.
 * Si le bouton est pressé, la fonction retourne un indicateur de succès. Sinon,
 * elle retourne un indicateur d'échec après l'expiration du délai.
 *
 * @return 1 si le bouton de charge est pressé, 0 sinon.
 */
int boutons_attente_charge(void)
{
    int etat_btn = 0;              /**< État du bouton (1: pressé, 0: relâché). */
    int time_att;
    timer_raz(&time_att);
       /**< Temps initial de la minuterie. */
   // int time2 = time1;             /**< Temps courant de la minuterie. */

    io_bt->bouton_charge = 0;

    // Boucle pour attendre l'appui sur le bouton ou la fin du délai
    while ((io_bt->bouton_charge == 0) && (  timer_valeur(time_att) <= 60)) 
    {
        usleep(1000);
    }

    etat_btn = io_bt->bouton_charge;

    printf("Etat du boutton: %d\n", etat_btn);
    io_bt->bouton_charge = 0; 

    return etat_btn;
}

/**
 * @brief Vérifie l'état du bouton d'arrêt.
 *
 * Cette fonction retourne l'état actuel du bouton d'arrêt (stop). Si le bouton est
 * pressé, l'état est retourné et réinitialisé immédiatement après.
 *
 * @return 1 si le bouton d'arrêt est pressé, 0 sinon.
 */
int bouton_stop(void)
{
    int etat_btn = io_bt->bouton_stop;  /**< État du bouton (1: pressé, 0: relâché). */
    io_bt->bouton_stop = 0;            /**< Réinitialise l'état du bouton après lecture. */
    return etat_btn;
}