/**
 * @file generateur_save.c
 * @author —
 * @date —
 * @brief Gestion du générateur et du processus de charge d’un véhicule électrique.
 *
 * Ce module implémente :
 * - l'initialisation du générateur,
 * - la machine à états finis (MEF) de charge,
 * - la gestion du contacteur AC,
 * - la génération du signal PWM,
 * - la déconnexion du véhicule après charge.
 *
 * Il s'appuie sur une mémoire partagée permettant la communication
 * avec les entrées/sorties de la borne de recharge.
 */

#include "generateur_save.h"
#include "boutton.h"

/**
 * @brief Pointeur vers la structure des entrées/sorties du générateur.
 *
 * Cette structure est partagée entre plusieurs processus via
 * une mémoire partagée.
 */
entrees* io_gs;

/**
 * @brief Identifiant de la mémoire partagée associée au générateur.
 */
int shmid_gs;

/**
 * @brief Initialise le générateur.
 *
 * Cette fonction établit l’accès à la mémoire partagée
 * afin de permettre le pilotage du générateur et
 * la lecture des tensions.
 */
void generateur_initialiser(void) 
{
    io_gs = acces_memoire(&shmid_gs);
}

/**
 * @brief Lance la procédure de charge du véhicule.
 *
 * Cette fonction appelle la machine à états finis (MEF)
 * qui gère l’ensemble des étapes de la charge.
 */
void generateur_charger_vehicule(void) 
{
    generateur_mef();
}

/**
 * @brief Machine à états finis (MEF) du processus de charge.
 *
 * La MEF gère les transitions suivantes :
 * - attente de branchement,
 * - verrouillage de la trappe,
 * - validation du véhicule,
 * - charge en cours,
 * - arrêt et fin de charge.
 *
 * Les états sont déterminés par la tension détectée
 * et l’action éventuelle sur le bouton d’arrêt.
 */
void generateur_mef(void) 
{
    /**
     * @enum etat
     * @brief États possibles de la machine à états.
     */
    typedef enum { 
        A, /**< Attente branchement prise */
        B, /**< Prise branchée et verrouillage */
        C, /**< Validation du véhicule */
        D, /**< Charge en cours */
        E  /**< Fin de charge */
    } etat;

    etat state = A; /**< État courant de la MEF */
    int Fin = 0;    /**< Indicateur de fin de processus */

    while (1) {
        switch (state) 
        {
            case A:
                voyants_set_charge(ROUGE);
                generateur_generer_PWM(DC);
                deverrouiller_trappe();

                /**
                 * Attente du branchement de la prise :
                 * tension attendue = 9V
                 */
                if (generateur_tension() == 9) 
                {
                    state = B;
                }
                else
                {
                    state = A;
                }

                sleep(2);
                break;

            case B:
                /**
                 * Arrêt immédiat si le bouton stop est pressé
                 */
                if (bouton_appuie_boutons_stop() == 1)
                {
                    state = E;
                    generateur_generer_PWM(STOP);
                    break;
                }

                prise_set_prise(VERT);
                verrouiller_trappe();
                generateur_generer_PWM(AC_1K);

                /**
                 * Validation de la connexion véhicule :
                 * tension attendue = 6V
                 */
                if (generateur_tension() == 6)
                {
                    state = C;
                }
                else
                {
                    state = B;
                }

                sleep(2);
                break;

            case C:
                /**
                 * Arrêt si bouton stop pressé
                 */
                if (bouton_appuie_boutons_stop() == 1) 
                {
                    state = E;
                    generateur_generer_PWM(STOP);
                    break;
                }

                generateur_fermer_AC();
                generateur_generer_PWM(AC_CL);

                if (generateur_tension() == 6)
                {
                    state = D;
                }
                else
                {
                    state = C;
                }

                sleep(2);
                break;

            case D:
                /**
                 * Phase de charge active
                 */
                printf("En cours de charge...\n");

                if ((generateur_tension() == 9) ||
                    (bouton_appuie_boutons_stop() == 1)) 
                {
                    state = E;
                }
                else
                {
                    state = D;
                }

                sleep(2);
                break;

            case E:
                /**
                 * Fin de charge et remise en état
                 */
                generateur_ouvrir_AC();
                generateur_generer_PWM(DC);
                voyants_set_charge(VERT);
                Fin = 1;
                break;
        }

        if (Fin) break;
    }
}

/**
 * @brief Gère la déconnexion du véhicule après la charge.
 *
 * Cette fonction :
 * - ouvre le contacteur AC,
 * - déverrouille la trappe,
 * - attend le débranchement complet de la prise
 *   (tension = 12V).
 */
void generateur_deconnecter(void) 
{
    int tension = 0;

    generateur_ouvrir_AC();
    deverrouiller_trappe();
    printf("Attente débranchement prise...\n");

    tension = generateur_tension();
    while (tension != 12)
    {
        sleep(2);
        tension = generateur_tension();
    }
}

/**
 * @brief Génère un signal PWM pour le générateur.
 *
 * Cette fonction écrit directement dans la mémoire partagée
 * la valeur PWM souhaitée.
 *
 * @param tension Valeur PWM à appliquer (DC, AC_1K, AC_CL, STOP…)
 */
void generateur_generer_PWM(pwm tension) 
{
    io_gs->gene_pwm = tension;
}

/**
 * @brief Ouvre le contacteur AC.
 *
 * Cette action coupe l’alimentation AC du véhicule.
 */
void generateur_ouvrir_AC(void) 
{
    io_gs->contacteur_AC = 0;
}

/**
 * @brief Ferme le contacteur AC.
 *
 * Autorise le passage du courant AC vers le véhicule.
 */
void generateur_fermer_AC(void) 
{
    io_gs->contacteur_AC = 1;
}

/**
 * @brief Lit la tension actuelle du générateur.
 *
 * @return Tension mesurée (en volts, valeur entière).
 */
int generateur_tension(void) 
{
    return io_gs->gene_u;
}
