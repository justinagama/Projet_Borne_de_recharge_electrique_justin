#include "generateur_save.h"
#include "boutton.h"


/**
 * @file generateur_save.c
 * @brief Gestion des fonctionnalités liées au générateur et au processus de charge.
 *
 * Ce fichier implémente les fonctions permettant de gérer le générateur, les transitions
 * d'états de charge, ainsi que l'interaction avec les prises et les voyants.
 */

entrees* io_gs; /**< Pointeur vers la mémoire partagée pour le générateur. */
int shmid_gs;   /**< Identifiant de la mémoire partagée. */

/**
 * @brief Initialise le générateur.
 *
 * Configure l'accès à la mémoire partagée pour contrôler le générateur.
 */
void generateur_initialiser(void) 
{
    io_gs = acces_memoire(&shmid_gs);
}

/**
 * @brief Lance le processus de charge.
 *
 * La fonction appelle une machine à états finis (MEF) pour gérer
 * toutes les étapes du processus de charge d'un véhicule électrique.
 */
void generateur_charger_vehicule(void) 
{
    generateur_mef();
}

/**
 * @brief Machine à états finis (MEF) pour gérer la charge du véhicule.
 *
 * Cette fonction utilise une MEF pour contrôler les étapes du processus de charge,
 * de la détection du branchement de la prise jusqu'à la fin de la charge.
 */
void generateur_mef(void) {
    typedef enum { A, B, C, D, E } etat; /**< États possibles de la machine à états. */
    etat state = A;
    int Fin = 0;

    while (1) {
        switch (state) 
        {
            case A:
                voyants_set_charge(ROUGE);
                
                generateur_generer_PWM(DC);
                deverrouiller_trappe();
                //printf("Attente branchement prise...\n");
                if(generateur_tension() == 9) 
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
                if(bouton_appuie_boutons_stop()==1)
                {
                    state = E;
                    generateur_generer_PWM(STOP);
                    break;
                }
                
                prise_set_prise(VERT);
                verrouiller_trappe();
               // generateur_ouvrir_AC();
                generateur_generer_PWM(AC_1K);
                
                
				sleep(2);
				
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
                if (bouton_appuie_boutons_stop() == 1) 
                {
                    state = E;
                    generateur_generer_PWM(STOP);
                    break ;
                }
                
          
                generateur_fermer_AC();
                generateur_generer_PWM(AC_CL);
                
                
    
                if( generateur_tension() == 6)
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
                printf("En cours de charge...\n");
                if((generateur_tension() == 9) || (bouton_appuie_boutons_stop() == 1)) 
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
 * @brief Gère la déconnexion après la fin de la charge.
 *
 * La fonction effectue les étapes nécessaires pour déverrouiller la trappe,
 * attendre le débranchedelay_secment de la prise, et réinitialiser l'état de la borne.
 */
void generateur_deconnecter(void) 
{
    generateur_ouvrir_AC();
	generateur_generer_PWM(OFF);
    deverrouiller_trappe();
    printf("Attente débranchement prise...\n");
    
    while (generateur_tension() != 12) { }

    verrouiller_trappe();
    voyants_set_charge(OFF);
    prise_set_prise(OFF);
    voyant_set_dispo(VERT);
    
}

/**
 * @brief Génère un signal PWM pour le générateur.
 *
 * La fonction configure la tension fournie par le générateur via PWM.
 *
 * @param tension La valeur de PWM à appliquer (DC, AC_1K, AC_CL, OFF, etc.).
 */
void generateur_generer_PWM(pwm tension) 
{
    io_gs->gene_pwm = tension;
}

/**
 * @brief Ouvre le contacteur AC.
 *
 * Coupe le circuit AC pour mettre fin à la charge ou réinitialiser le générateur.
 */
void generateur_ouvrir_AC(void) 
{
    io_gs->contacteur_AC = 0;
}

/**
 * @brief Ferme le contacteur AC.
 *
 * Active le circuit AC pour permettre la charge du véhicule.
 */
void generateur_fermer_AC(void) 
{
    io_gs->contacteur_AC = 1;
}

/**
 * @brief Retourne la tension actuelle générée.
 *
 * Mesure la tension délivrée par le générateur pour vérifier l'état du processus de charge.
 *
 * @return La tension actuelle sous forme de nombre flottant.
 */
int generateur_tension(void) 
{
    return io_gs->gene_u;
}

