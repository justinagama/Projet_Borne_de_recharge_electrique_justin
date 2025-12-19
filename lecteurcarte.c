#include "lecteurcarte.h"
#include "bool.h"


entrees* io_lc;
int shmid_lc;
int numero_carte = 0;
void lecteurcarte_initialiser()
{
    initialisations_ports();
    printf("Port init success\n");
}

void lecteurcarte_lire_carte()
{
        //int numero_carte = 0;
    Bool N ;
    int nouvelle_carte =0;
    io_lc = acces_memoire(&shmid_lc);
    printf("Inserez votre carte\n");
    attente_insertion_carte();
    
    numero_carte = lecture_numero_carte();
    if(carte_inseree())
    {
        //numero_carte = lecture_numero_carte();
        //base_clients_ajouter(numero_carte);
        printf("Numero du clien: %d\n", numero_carte);
        N = base_clients_authentifier(numero_carte);
        if (N)
        {
            printf("authentification reussi\n");
            
            if (boutons_attente_charge()==0)
            {
            }
            else
            {
                voyant_dispo(OFF);
                voyant_blink_charge(VERT);

            }

        }
        else
        {
            printf("Desoler vous n'ete pas dans la liste \n");
            // faire clignoter le voyant <<defaut>> pendant 8s
            
            voyant_defaut(ROUGE);

            // ici nous allons demander au client si il veux s'enregister oui ou non 

            printf("Voulez vous faire l'enregistrement de votre carte ? entrez 1 si oui 0 si non :");
            scanf("%d",&nouvelle_carte);
            if(nouvelle_carte==1)
            {
                // demande de droit d'administration qui sera implementé dans la fonction base_clients_ajouter
                base_clients_ajouter(numero_carte);
            }
            else
            {
                printf("Vous avez choisir de ne pas enregistrer votre carte :) \n");
            }
        }

        attente_retrait_carte();
        printf("Carte retiree\n");
        //liberation_ports();
    }
    else
    {
        printf("Aucune carte inserree\n");
    }
    return;

}

