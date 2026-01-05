/**
 * @file main.c
 * @author —
 * @date —
 * @brief Point d’entrée principal de la borne de recharge.
 *
 * Ce fichier contient la fonction main qui :
 * - initialise tous les modules de la borne,
 * - propose le choix entre le mode administrateur et le mode utilisateur,
 * - lance les traitements associés à chaque mode.
 *
 * Le programme fonctionne en boucle continue en mode utilisateur
 * afin de gérer plusieurs sessions de recharge successives.
 */

#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>

#include "lecteurcarte.h"
#include "base_clients.h"
#include "timer.h"
#include "voyant.h"
#include "prise.h"
#include "generateur_save.h"
#include "boutton.h"

/**
 * @brief Fonction principale du programme.
 *
 * Cette fonction :
 * - initialise les différents sous-systèmes de la borne,
 * - permet à l’utilisateur de choisir un mode de fonctionnement,
 * - lance le mode administrateur ou utilisateur selon le choix.
 *
 * @return 0 Fin normale du programme
 */
int main()
{
    /**
     * Initialisation des modules de la borne
     */
    lecteurcarte_initialiser();
    timer_initialiser();
    voyant_initialiser();
    generateur_initialiser();
    boutons_initialiser();
    prise_init();

    /**
     * Choix du mode de fonctionnement
     */
    printf("\nChoisir l'operation a effectuer : \n");
    printf("1- Mode Administrateur \n");
    printf("2- Mode Utilisateur \n");

    int choix_mode = 0;
    scanf("%d", &choix_mode);

    if (choix_mode == 1)
    {
        /**
         * Mode administrateur :
         * gestion de la base clients
         */
        administrateur_mode();
    }
    else if (choix_mode == 2)
    {
        /**
         * Mode utilisateur :
         * gestion des cycles de recharge
         */
        printf("Mode utilisateur selectionne \n");

        while (1)
        {        
            lecteurcarte_lire_carte();
            //generateur_charger_vehicule();
            //lecteur_carte_reprise_vehicule();    
        }
    }
    else
    {
        /**
         * Gestion d’un choix invalide
         */
        printf("Choix invalide \n");
    }

    return 0;
}
