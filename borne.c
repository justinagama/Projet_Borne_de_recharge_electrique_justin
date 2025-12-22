#include <stdio.h>
#include <memoire_borne.h>
#include <donnees_borne.h>

#include "lecteurcarte.h"
#include "base_clients.h"
#include "timer.h"
#include "voyant.h"

int main()
{

    lecteurcarte_initialiser();
    timer_initialiser();
    voyant_initialiser();
    generateur_initialiser();
    boutons_initialiser();

    prise_init();
    while (1)
    {        
        lecteurcarte_lire_carte();
        generateur_charger_vehicule();
    }

}
