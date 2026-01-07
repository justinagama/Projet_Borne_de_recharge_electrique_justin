/**
 * @file base_clients.c
 * @author â€”
 * @date â€”
 * @brief Gestion de la base de donnÃ©es des clients.
 *
 * Ce module permet :
 * - lâ€™authentification dâ€™un client via son numÃ©ro de carte,
 * - lâ€™ajout dâ€™un nouveau client (mode administrateur),
 * - la suppression dâ€™un client,
 * - lâ€™affichage de la liste des clients enregistrÃ©s.
 *
 * La base clients est stockÃ©e dans un fichier texte
 * nommÃ© "base_clients.txt".
 */

#include "base_clients.h"

/**
 * @brief Authentifie un client Ã  partir de son numÃ©ro de carte.
 *
 * Cette fonction lit le fichier de la base clients et
 * vÃ©rifie si le numÃ©ro de carte fourni existe.
 *
 * @param numero_carte NumÃ©ro de carte Ã  vÃ©rifier
 * @return 1 si la carte est trouvÃ©e, 0 sinon
 */
int base_clients_authentifier(int numero_carte)
{
    int table[20];
    int i = 0, j = 0;

    FILE *file = fopen("base_clients.txt", "r");

    if (file == NULL)
    {
        fprintf(stderr, "Erreur\n");
        return 0;
    }

    int client = 0;

    /**
     * Lecture des numÃ©ros de cartes depuis le fichier
     */
    while (fscanf(file, "%d", &client) == 1 && i < 20)
    {
        table[i] = client;
        i++;
    }

    /**
     * Recherche du numÃ©ro de carte dans la table
     */
    for (j = 0; j < 20; j++)
    {
        if (table[j] == numero_carte)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

/**
 * @brief Ajoute un nouveau client Ã  la base de donnÃ©es.
 *
 * Cette fonction :
 * - lit le numÃ©ro de carte,
 * - vÃ©rifie que la carte nâ€™existe pas dÃ©jÃ ,
 * - demande un code administrateur (3 tentatives),
 * - ajoute la carte au fichier si lâ€™authentification rÃ©ussit.
 */
void base_clients_ajouter()
{
    int numero_tempo = 0;
    int numero_carte = 0;
    int codeAdmi = 0;
    int nfoi = 0;

    numero_carte = lecture_numero_carte();

    FILE *file = fopen("base_clients.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Erreur\n");
        return;
    }

    /**
     * VÃ©rification de l'existence de la carte
     */
    while (fscanf(file, "%d", &numero_tempo) == 1)
    {
        if (numero_tempo == numero_carte)
        {
            printf("Cette carte existe deja.\n");
            fclose(file);
            return;
        }
    }

    fclose(file);

    /**
     * Authentification administrateur (3 tentatives max)
     */
    do
    { 
        printf("\nEntrez le code administrateur tentative %d/3 : ", nfoi + 1);
        scanf("%d", &codeAdmi);

        if (codeAdmi != CodeAdmi)
        {
            printf("Code administrateur incorrect.\n");
        }

        nfoi++;
    }
    while (codeAdmi != CodeAdmi && nfoi < 3);

    if (codeAdmi != CodeAdmi)
    {
        printf("Echec de l'authentification. Ajout impossible.\n");
        return;
    }

    /**
     * Ajout du client dans la base
     */
    file = fopen("base_clients.txt", "a");

    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier en ecriture.\n");
        return;
    }

    fprintf(file, "\n%d\n", numero_carte);
    printf("Client ajoute avec succes\n");
    fclose(file);
}

/**
 * @brief Affiche la liste des clients enregistrÃ©s.
 *
 * Cette fonction lit le fichier "base_clients.txt"
 * et affiche chaque numÃ©ro de client.
 */
void afficher_liste_clients()
{
    FILE *file = fopen("base_clients.txt", "r");
    int client;

    if (file == NULL)
    {
        fprintf(stderr, "Erreur\n");
        return;
    }

    printf("La liste des clients enregistres :\n");

    while (fscanf(file, "%d", &client) == 1)
    {
        printf("Numero de client : %d\n", client);
    }

    fclose(file);

}
/**
 * @brief Active le mode administrateur.
 *  printf("Entrez le numero de la carte a supprimer : ");
        scanf("%d", &numero_carte_admin);
 * Permet Ã  lâ€™administrateur de :
 * - ajouter un client,
 * - supprimer un client,
 * - afficher la liste des clients.
 */
int administrateur_mode()
{
    int choix_admin = 0;

    printf("Bienvenue dans le mode administrateur\n");
    printf("Entrez 1 pour ajouter un client\n");
    printf("Entrez 2 pour supprimer un client\n");
    printf("Entrez 3 pour afficher la liste des clients\n");
    printf("Entrez 4 pour retourner dans le mode Utilisateur\n");
    printf("Votre choix : ");

    scanf("%d", &choix_admin);

    if (choix_admin == 1)
    {   
        printf("Inseree votre carte...\n");
        attente_insertion_carte();
        base_clients_ajouter();
        printf("retiree votre carte...\n");
        attente_retrait_carte();
        printf("Carte retiree\n");
        return 0;
    }
    else if (choix_admin == 2)
    {
        base_clients_supprimer();
        return 0;
    }
    else if (choix_admin == 3)
    {
        afficher_liste_clients();
        return 0;
    
    }
    else if (choix_admin == 4)
    {
        return 1;
    }
    return 0;

}

/**
 * @brief Supprime un   do
    { 
        printf("\nEntrez le code administrateur tentative %d/3 : ", nfoi + 1);
        scanf("%d", &codeAdmi);
    int codeAdmi = 0;
    int nfoi = 0;

        if (codeAdmi != CodeAdmi)
        {
            printf("Code administrateur incorrect.\n");
        }
 }
   
        nfoi++;
    } }
   
    while (codeAdmi != CodeAdmi && nfoi < 3);

    if (codeAdmi != CodeAdmi)
    {
        printf("Echec de l'authentification. Ajout impossible.\n");
        return;
    }
 client de la base de donnÃ©es.
 *
 * La suppression est rÃ©alisÃ©e en copiant la base
 * dans un fichier temporaire sans le client Ã  supprimer.
 *
 * @return 1 si la suppression a rÃ©ussi, 0 sinon
 */
int base_clients_supprimer(void)
{
    int codeAdmi = 0;
    int nfoi = 0;

    do
    { 
        printf("\nEntrez le code administrateur tentative %d/3 : ", nfoi + 1);
        scanf("%d", &codeAdmi);

        if (codeAdmi != CodeAdmi)
        {
            printf("Code administrateur incorrect.\n");
        }

        nfoi++;
    }
    while (codeAdmi != CodeAdmi && nfoi < 3);

    if (codeAdmi != CodeAdmi)
    {
        printf("Echec de l'authentification. Ajout impossible.\n");
        return;
    }

    int numero_carte;
    int numero_tempo;
    int trouve = 0;
    printf("Inseree votre carte...\n");
    attente_insertion_carte();
    numero_carte = lecture_numero_carte();

    FILE *file = fopen("base_clients.txt", "r");
    FILE *temp_file = fopen("temp.txt", "w");

    if (file == NULL || temp_file == NULL)
    {
        fprintf(stderr, "Erreur d'ouverture des fichiers\n");
        if (file) fclose(file);
        if (temp_file) fclose(temp_file);
        return 0;
    }

    /**
     * Copie de la base sans la carte Ã  supprimer
     */
    while (fscanf(file, "%d", &numero_tempo) == 1)
    {
        if (numero_tempo == numero_carte)
        {
            trouve = 1;
            continue;
        }
        fprintf(temp_file, "%d\n", numero_tempo);
    }

    fclose(file);
    fclose(temp_file);

    if (trouve)
    {
        remove("base_clients.txt");
        rename("temp.txt", "base_clients.txt");
        printf("Client supprime avec succes.\n");
        return 1;
    }
    else
    {
        remove("temp.txt");
        printf("Carte non trouvee dans la base.\n");
        return 0;
    }
}
