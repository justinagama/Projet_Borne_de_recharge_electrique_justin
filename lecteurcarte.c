/**
 * @file lecteurcarte.c
 * @author —
 * @date —
 * @brief Gestion du lecteur de carte pour l’authentification des utilisateurs.
 *
 * Ce module permet :
 * - l’initialisation du lecteur de carte,
 * - la lecture et l’authentification d’une carte client,
 * - le lancement du processus de charge,
 * - la reprise du véhicule après la charge.
 *
 * Il interagit avec :
 * - la base de données clients,
 * - le générateur,
 * - les voyants et boutons de la borne.
 */

#include "lecteurcarte.h"
#include "generateur_save.h"
#include "boutton.h"
#include "bool.h"
#include "base_clients.h"

/**
 * @brief Pointeur vers la mémoire partagée du lecteur de carte.
 */
entrees* io_lc;

/**
 * @brief Identifiant de la mémoire partagée associée au lecteur de carte.
 */
int shmid_lc;

/**
 * @brief Numéro de carte lu lors de l’insertion.
 */
int numero_carte = 0;

/**
 * @brief Numéro de carte global mémorisé pendant la charge.
 *
 * Ce numéro permet de vérifier que la carte utilisée
 * pour reprendre le véhicule est bien celle ayant lancé la charge.
 */
int numero_carte_global = 0;

/**
 * @brief Initialise le lecteur de carte.
 *
 * Cette fonction initialise les ports matériels
 * nécessaires à la lecture des cartes.
 */
void lecteurcarte_initialiser()
{
    initialisations_ports();
    printf("Port init success\n");
}

/**
 * @brief Gère la lecture et l’authentification d’une carte client.
 *
 * Cette fonction :
 * - attend l’insertion d’une carte,
 * - lit son numéro,
 * - vérifie l’authentification dans la base clients,
 * - lance la charge si l’utilisateur est autorisé,
 * - gère les voyants et boutons associés.
 *
 * @return 0 Fin normale de la fonction
 */
void lecteurcarte_lire_carte()
{
    int nouvelle_carte = 0;

    io_lc = acces_memoire(&shmid_lc);
    printf("Inserez votre carte\n");

    attente_insertion_carte();

    numero_carte = lecture_numero_carte();

    /**
     * Vérification :
     * - carte bien insérée
     * - borne disponible
     */
    if (carte_inseree() && voyant_dispo())
    {
        printf("Numero du client: %d\n", numero_carte);

        /**
         * Authentification du client
         */
        if (base_clients_authentifier(numero_carte))
        {
            printf("Authentification reussie\n");

            voyant_blink_charge(VERT);
            numero_carte_global = numero_carte;

            /**
             * Vérification du bouton charge
             */
            if (boutons_appuie_boutons_charge() == 1)
            {
                voyant_set_dispo(OFF);
                printf("Retirez votre carte\n");
                attente_retrait_carte();
                printf("Carte retiree\n");

                /**
                * Lancement du processus de charge
                */
                generateur_charger_vehicule();
                sleep(2);

                /**
                * Procédure de reprise du véhicule après charge
                */
                lecteur_carte_reprise_vehicule();
            }
            else
            {
                voyant_set_dispo(VERT);
            }

           
        }
        else
        {
            /**
             * Carte non reconnue
             */
            printf("Desole, vous n'etes pas dans la liste\n");
            printf("Connectez-vous en mode administrateur pour vous enregistrer\n");

            voyant_blink_defaut(ROUGE);
        }

        printf("Retirez votre carte\n");
        attente_retrait_carte();
        printf("Carte retiree\n");
    }
    else
    {
        printf("Aucune carte inseree\n");
    }

    return 0;
}

/**
 * @brief Permet au client de reprendre son véhicule après la charge.
 *
 * Cette fonction :
 * - attend l’insertion de la carte,
 * - vérifie que la carte correspond à celle ayant lancé la charge,
 * - déconnecte le générateur,
 * - remet la borne dans son état initial.
 */
void lecteur_carte_reprise_vehicule()
{
    io_lc = acces_memoire(&shmid_lc);
    int numero_carte = 0;
    int val_check = 0;
    do
    {

    printf("\nChargement termine. Veuillez inserer la carte pour reprendre votre vehicule.\n");
    
    attente_insertion_carte();
    numero_carte = lecture_numero_carte();

    if (carte_inseree())
    {
        /**
         * Vérification de l'identité du client
         */
        if (base_clients_authentifier(numero_carte) &&
            (numero_carte == numero_carte_global))
        {
            printf("Authentification reussie. Vous pouvez reprendre votre vehicule.\n");

            generateur_deconnecter();
            verrouiller_trappe();
            voyants_set_charge(OFF);
            prise_set_prise(OFF);
            voyant_set_dispo(VERT);
            generateur_generer_PWM(OFF);

            /**
             * Réinitialisation du numéro de carte global
             */
            numero_carte_global = 0;
            val_check = 1;
            return;
        }
        else
        {
            printf("Authentification echouee. Carte non reconnue.\n");
            voyant_blink_defaut(ROUGE);
            val_check = 2;
            voyant_set_defaut(OFF);
        }
    }
    }while(val_check == 2);
}
