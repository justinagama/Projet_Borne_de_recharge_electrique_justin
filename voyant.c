#include "voyant.h"
#include "timer.h"


int run = 0; /**< Indicateur global pour les opératio_vns (non utilisé actuellement). */

entrees* io_v; /**< Pointeur vers la mémoire partagée pour l'accès aux voyants. */
int shmid_v;   /**< Identifiant de la mémoire partagée. */

void voyant_initialiser()
{
    io_v=acces_memoire(&shmid_v);
    /* associe la zone de memoire partagee au pointeur */
    if (io_v==NULL) 
    {
        printf("Erreur pas de mem sh\n");
    }
}
/*---------------------------------------------------------------------*/

void voyants_set_charge(led ledstate) 
{
    io_v->led_charge = ledstate;
}

/*--------------------------------------------------------------------- */
void voyant_set_dispo(led Mode)
{
    io_v->led_dispo = Mode;
}


/*---------------------------------------------------------------------*/
// le voyan charge doit clignoter 

void voyant_blink_charge(led Mode)
{
  int depart_timer = 0,temps_precedent =0;
    timer_initialiser();
    timer_raz(&depart_timer);
     while (timer_valeur(depart_timer)<=8)
    {
        if (timer_valeur(depart_timer) % 2 ==0)
        {
            //temps_precedent = io_v->timer_sec;
            io_v->led_charge = Mode;
        } 
        else
        {
            io_v->led_charge = OFF;      // Voyant éteint
        }
    }

    
    
}
/*---------------------------------------------------------------------*/
void voyant_set_defaut(led Mode)
{
  io_v->led_defaut = Mode;
}

/*---------------------------------------------------------------------*/
void voyant_blink_defaut(led Mode)
{
    int depart_timer =0;

    timer_initialiser();
    timer_raz(&depart_timer);

    while (timer_valeur(depart_timer)<=8)
    {
        if (timer_valeur(depart_timer) % 2 ==0)
        {
            io_v->led_defaut = Mode;
        } 
        else
        {
            io_v->led_defaut = OFF;      // Voyant éteint
        }
    }

}
/*---------------------------------------------------------------------*/

// void voyant_set_prise(led Mode);
// {
//     io_v->led_prise=Mode;
// }


/*---------------------------------------------------------------------*/
// la fonction pour verifier la disponibilter du voyant vert ou non elle retourne 1 si dispo 0 sinon
int voyant_dispo()
{
    int val_dispo =0;
    if(io_v->led_dispo == VERT)
    {
        val_dispo = 1;
    }
    else
    {
        val_dispo = 0;
    }
    return val_dispo;
}

