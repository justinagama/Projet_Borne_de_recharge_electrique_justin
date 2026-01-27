/**
 * @file voyant.c
 * @author —
 * @date —
 * @brief Gestion des voyants lumineux de la borne de recharge.
 *
 * Ce module permet de :
 * - contrôler les voyants de charge, de disponibilité et de défaut,
 * - faire clignoter les voyants selon des temporisations,
 * - vérifier l’état de disponibilité de la borne.
 *
 * Les voyants sont pilotés via une mémoire partagée.
 */

#include "voyant.h"
#include "timer.h"

/**
 * @brief Indicateur global (non utilisé actuellement).
 */
int run = 0;

/**
 * @brief Pointeur vers la mémoire partagée des voyants.
 */
entrees* io_v;

/**
 * @brief Identifiant de la mémoire partagée associée aux voyants.
 */
int shmid_v;

/**
 * @brief Initialise l’accès aux voyants.
 *
 * Associe la mémoire partagée au pointeur
 * permettant de contrôler les voyants.
 */
void voyant_initialiser()
{
    io_v = acces_memoire(&shmid_v);

    if (io_v == NULL)
    {
        printf("Erreur pas de mem sh\n");
    }
}

/*---------------------------------------------------------------------*/

/**
 * @brief Définit l’état du voyant de charge.
 *
 * @param ledstate État du voyant (VERT, ROUGE, OFF, etc.)
 */
void voyants_set_charge(led ledstate) 
{
    io_v->led_charge = ledstate;
}

/*---------------------------------------------------------------------*/

/**
 * @brief Définit l’état du voyant de disponibilité.
 *
 * @param Mode Couleur ou état du voyant
 */
void voyant_set_dispo(led Mode)
{
    io_v->led_dispo = Mode;
}

/*---------------------------------------------------------------------*/

/**
 * @brief Fait clignoter le voyant de charge.
 *
 * Le voyant clignote pendant 8 secondes,
 * avec une alternance ON/OFF toutes les secondes.
 *
 * @param Mode Couleur du voyant lors de l’allumage
 */
void voyant_blink_charge(led Mode)
{
    int depart_timer = 0;

    timer_initialiser();
    timer_raz(&depart_timer);

    while (timer_valeur(depart_timer) <= 8)
    {
        if (timer_valeur(depart_timer) % 2 == 0)
        {
            io_v->led_charge = Mode;
        }
        else
        {
            io_v->led_charge = OFF;
        }
    }
}

/*---------------------------------------------------------------------*/

/**
 * @brief Définit l’état du voyant de défaut.
 *
 * @param Mode Couleur ou état du voyant
 */
void voyant_set_defaut(led Mode)
{
    io_v->led_defaut = Mode;
}

/*---------------------------------------------------------------------*/

/**
 * @brief Fait clignoter le voyant de défaut.
 *
 * Le voyant clignote pendant 8 secondes,
 * avec une alternance ON/OFF toutes les secondes.
 *
 * @param Mode Couleur du voyant lors de l’allumage
 */
void voyant_blink_defaut(led Mode)
{
    int depart_timer = 0;

    timer_initialiser();
    timer_raz(&depart_timer);

    while (timer_valeur(depart_timer) <= 8)
    {
        if (timer_valeur(depart_timer) % 2 == 0)
        {
            io_v->led_defaut = Mode;
        }
        else
        {
            io_v->led_defaut = OFF;
        }
    }
}

/*---------------------------------------------------------------------*/

/**
 * @brief Vérifie la disponibilité de la borne.
 *
 * La borne est considérée disponible
 * si le voyant de disponibilité est vert.
 *
 * @return 1 si la borne est disponible, 0 sinon
 */
int voyant_dispo()
{
    int val_dispo = 0;

    if (io_v->led_dispo == VERT)
    {
        val_dispo = 1;
    }
    else
    {
        val_dispo = 0;
    }

    return val_dispo;
}
