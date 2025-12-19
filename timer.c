
#include "timer.h"

entrees *io; 
int shmid_t;
void timer_initialiser()
{
    io=acces_memoire(&shmid_t);
    /* associe la zone de memoire partagee au pointeur */
    if (io==NULL) 
    {
        printf("Erreur pas de mem sh\n");
    }
}


void timer_raz(int *tim)
{
    *tim = io->timer_sec;
}

int timer_valeur(int tim)
{
    int val = io->timer_sec - tim;
    return  val;
}