#include "lecteurcarte.h"
#include "generateur_save.h"

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

    int nouvelle_carte =0;
    io_lc = acces_memoire(&shmid_lc);
    printf("Inserez votre carte\n");
    attente_insertion_carte();
    
    numero_carte = lecture_numero_carte();
    if(carte_inseree()&&voyant_dispo())
    {
        printf("Numero du clien: %d\n", numero_carte);

        if (base_clients_authentifier(numero_carte))
        {
            printf("authentification reussi\n");
            voyant_blink_charge(VERT);
            numero_carte_global=numero_carte;
            if (boutons_appuie_boutons_charge()==1)
            {
                voyant_set_dispo(OFF);
                
            }
            else
            {
               voyant_set_dispo(VERT);
            }

        }
        else
        {
            printf("Desoler vous n'ete pas dans la liste \n");
            // faire clignoter le voyant <<defaut>> pendant 8s
            
            voyant_blink_defaut(ROUGE);

            // // ici nous allons demander au client si il veux s'enregister oui ou non 

            // printf("Voulez vous faire l'enregistrement de votre carte ? entrez 1 si oui 0 si non :");
            // scanf("%d",&nouvelle_carte);
            // if(nouvelle_carte==1)
            // {
            //     // demande de droit d'administration qui sera implementé dans la fonction base_clients_ajouter
            //     base_clients_ajouter(numero_carte);
            // }
            // else
            // {
            //     printf("Vous avez choisir de ne pas enregistrer votre carte :) \n");
            // }
        }

        attente_retrait_carte();
        printf("Carte retiree\n");

        //liberation_ports();
    }
    else
    {
        printf("Aucune carte inserree\n");
    }

    return 0;
}

void lecteur_carte_reprise_vehicule()
{
    io_lc = acces_memoire(&shmid_lc);
    int numero_carte = 0;

    printf("\nChargement termine. Veuillez inserer la carte pour reprendre votre vehicule.\n");
    attente_insertion_carte();

    numero_carte = lecture_numero_carte();
    if(carte_inseree())
    {
        if (base_clients_authentifier(numero_carte) && (numero_carte == numero_carte_global))
        {   
            printf("Authentification reussie. Vous pouvez reprendre votre vehicule.\n");
            generateur_deconnecter();
            numero_carte_global = 0; // reset du numero de carte global
        }
        else
        {
            printf("Authentification echouee. Carte non reconnue.\n");
            voyant_blink_defaut(ROUGE);
        }
    }
}
