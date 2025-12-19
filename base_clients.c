#include "base_clients.h"

Bool base_clients_authentifier(int numero_carte)
{
    int table[20];
    int i = 0;
    Bool N;

    FILE *file = fopen("base_clients.txt", "r");

    if (file == NULL)
    {
        fprintf(stderr, "Erreur\n");
        return 0;
    }
    
    int client = 0;
    while (fscanf(file, "%d", &client) == 1)
    {
        table[i] = client;
        i++;
        //printf("tab =  \n",table[i]);
    }

    for(int j =0; j < 20; j++)
    {
        if(table[j] == numero_carte)
        {
            N=true;
            return N;
        }
        else
        {
            N =false;
        }
    }

    fclose(file);

    return N;
}


/*Nous devons lire la carte du client pour sa premiere connection si il 
existe deja on ne l'ajoute pas*/

/* pour ajouter un client dans la base nous devons avoir le droit de l'administrateur*/

void base_clients_ajouter()
{
    int numero_tempo = 0;
    int numero_carte = 0;
    int codeAdmi =0;
    int nfoi =0;

    numero_carte = lecture_numero_carte();

    FILE *file = fopen("base_clients.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Erreur\n");
        return ;
    }


    // on passe une verification du numero de la carte dans la base de donner 
    while (fscanf(file, "%d", &numero_tempo) == 1)
    {
        if(numero_tempo == numero_carte)
        {
            printf("Cette carte existe deja.\n");
            fclose(file);
            return ;
        }
    }

    fclose(file);

    /*  ici pour ajouter le numero de la carte nous devons demander un code 
        faire une boucle do while pour avois 3 essai de code 
    */
    do
    { 
        printf("\nEnter le code administrateur tentative %d/3 : ",nfoi+1);
        scanf("%d",&codeAdmi);
        if (codeAdmi != CodeAdmi)
         {
          printf("Code administrateur incorrect.\n");
         }

        nfoi ++;
    }while(codeAdmi!=CodeAdmi && nfoi <3);

    if (codeAdmi != CodeAdmi)
    {
        printf("Echec de l'authentification. Ajout impossible.\n");
        // clignoter le voyant 
        return;
    }

    if (codeAdmi==CodeAdmi)
    {
        file = fopen("base_clients.txt", "a");

        if (file == NULL)
        {
            printf("Erreur lors de l'ouverture du fichier en ecriture.\n");
            return;
        }

        fprintf(file, "\n%d\n", numero_carte);
        printf("Client ajoute avec success\n");
        fclose(file);
        return;
    }

}

void afficher_liste_clients()
{
    FILE *file = fopen("base_clients.txt", "r");
    int client;
    if (file == NULL)
    {
        fprintf(stderr, "Erreur\n");
        return 0;
    }

    printf("La liste des clients enregistre: \n");
    while(fscanf(file, "%d", &client) == 1)
    {
        printf("Numero de client: %d\n", client);
    }
    fclose(file);


}