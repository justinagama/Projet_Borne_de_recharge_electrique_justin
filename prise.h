#ifndef PRISE_H
#define PRISE_H

#include <donnees_borne.h>
#include <memoire_borne.h>

void prise_init (void);
void verrouiller_trappe (void);
void deverrouiller_trappe(void);
void prise_set_prise(led ledstate);


#endif //PRISE_H
