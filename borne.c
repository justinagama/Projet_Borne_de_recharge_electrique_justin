#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>


#include "lecteurcarte.h"
#include "base_clients.h"
#include "timer.h"
#include "voyant.h"
#include "prise.h"
#include "generateur_save.h"





int main()
{


    lecteurcarte_initialiser();
    timer_initialiser();
    voyant_initialiser();
    generateur_initialiser();
    boutons_initialiser();
    prise_init();

    printf("\nChoisir l'operation a effectuer : \n");
    printf("1- Mode Administrateur \n");
    printf("2- Mode Utilisateur \n");
    int choix_mode =0;
    scanf("%d",&choix_mode);
    if(choix_mode==1)
    {
        administration_mode();
    }
    else if(choix_mode==2)
    {
        printf("Mode utilisateur selectionne \n");
        while (1)
        {        
            lecteurcarte_lire_carte();
            generateur_charger_vehicule();
            lecteur_carte_reprise_vehicule();    
        }
    }
    else
    {
        printf("Choix invalide \n");
    }
    return 0;
}
