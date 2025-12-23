#include "base_clients.h"

int base_clients_authentifier(int numero_carte)
{
    int table[20];
    int i = 0,j =0;

    FILE *file = fopen("base_clients.txt", "r");

    if (file == NULL)
    {
        fprintf(stderr, "Erreur\n");
        return 0;
    }
    
    int client = 0;
    while (fscanf(file, "%d", &client) == 1&& i < 20)
    {
        table[i] = client;
        i++;
        //printf("tab =  \n",table[i]);
    }

    for(j =0; j < 20; j++)
    {
        if(table[j] == numero_carte)
        {
            fclose(file);
            return 1;
        }

    }

    fclose(file);

    return 0;
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


void administrateur_mode()
{
    int choix_admin =0;
    int numero_carte =0;
    printf("Bienvenue dans le mode administrateur \n");
    printf("Entrez 1 pour ajouter un client \n");
    printf("Entrez 2 pour supprimer un client \n");
    printf("Entrez 3 pour regarder la liste des clients \n");
    printf("Votre choix : ");
    scanf("%d",&choix_admin);
    if(choix_admin==1)
    {
        
        attente_insertion_carte();
        base_clients_ajouter();
        attente_retrait_carte();
        printf("Carte retiree\n");
    }
    else if (choix_admin==2)
    {
        int numero_carte_admin=0;
        printf("Entrez le numero de la carte a supprimer : ");
        scanf("%d",&numero_carte_admin);
        base_clients_supprimer();
    }
    else if (choix_admin==3)
    {
        attente_insertion_carte();
        afficher_liste_clients();
        attente_retrait_carte();
        printf("Carte retiree\n");
    }
}

void base_clients_supprimer()
{
    int numero_carte =0; // numero de la carte a supprimer
    int numero_tempo =0; // numero temporaire pour la lecture
    int trouve =0; // flag pour indiquer si la carte a ete trouvee

    FILE *file = fopen("base_clients.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");

    if (file == NULL || temp_file == NULL)
    {
        fprintf(stderr, "Erreur\n");
        return ;
    }

    numero_carte = lecture_numero_carte();

    
    while (fscanf(file, "%d", &numero_tempo) == 1)
    {
        if(numero_tempo == numero_carte)
        {
            trouve = 1;
            continue; // ne pas ecrire cette carte dans le fichier temporaire
        }
        fprintf(temp_file, "%d\n", numero_tempo);
    }

    fclose(file);
    fclose(temp_file);

    if (trouve)
    {
        remove("base_clients.txt"); // supprimer l'ancien fichier
        rename("temp.txt", "base_clients.txt"); // renommer le fichier temporaire
        printf("Client supprime avec success\n");
    }
    else
    {
        remove("temp.txt");
        printf("Carte non trouvee dans la base.\n");
    }
}