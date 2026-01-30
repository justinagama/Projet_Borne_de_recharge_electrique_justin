# ⚡ Borne de Recharge pour Véhicule Électrique – Projet C
Squelette de développement pour le projet de borne de recharge de véhicule électrique (travaux pratiques EEA)

Squelette du code de commande de la borne de recharge. Projet à but pédagogique.

make clean
make depend
make
ipcclean
sim_borne &.
./borne

🎥 Démonstration vidéo : https://justinagama.github.io/Projet_Borne_de_recharge_electrique_justin/ 

Description du projet

Ce projet consiste à développer le logiciel de contrôle d’une borne de recharge pour véhicule électrique, implémenté en langage C et exécuté sur une plateforme embarquée simulée.

Le système permet :
1.	L’authentification des utilisateurs par carte,
2.	La gestion complète du cycle de charge,
3.	La sécurisation de la prise et de la trappe,
4.	L’indication de l’état du système via des voyants lumineux,
5.	Un mode administrateur pour la gestion des clients.

Le projet a été conçu selon une démarche de conception UML, avant toute implémentation, afin de garantir une architecture claire, modulaire et maintenable.

Conception UML

La conception du système repose sur plusieurs modèles UML, réalisés en amont du développement :

Modèles utilisés

1.	Diagrammes de cas d’utilisation

o Mode utilisateur

o	Mode administrateur

2.	Diagrammes de séquence
   
o	Lecture de carte

o	Authentification client

o	Processus de charge

o	Reprise du véhicule

4.	Diagramme d’états

o	Machine à états finis (MEF) du générateur de charge

Avantages de l’approche UML
1.	Vision claire du fonctionnement global
2.	Séparation nette des responsabilités entre modules
3.	Traduction directe des diagrammes en code C
4.	Facilité de maintenance et d’évolution du système
 
Architecture logicielle
Le projet est organisé de manière modulaire, chaque composant fonctionnel étant isolé dans un module dédié.

Module	Rôle
1. lecteurcarte	: Lecture et validation des cartes
2. base_clients	: Gestion des clients et du mode administrateur
3. generateur_save	: Machine à états de charge (PWM, AC, DC)
4. prise	: Gestion de la prise et de la trappe
5. voyant	: Gestion des voyants (charge, défaut, disponibilité)
6. bouton	: Gestion des boutons (charge, arrêt)
7. timer :	Gestion des temporisations
8. Borne	: Point d’entrée du programme

Fonctionnement global

Mode Utilisateur

1.	Insertion de la carte
2.	Authentification du client
3.	Démarrage du processus de charge
4.	Gestion sécurisée de la charge (MEF)
5.	Fin de charge
6.	Réinsertion de la carte pour reprise du véhicule
   
Mode Administrateur

1. Ajout d’un client
2. Suppression d’un client
3.	Consultation de la base des clients
4.	Accès sécurisé par code administrateur

Gestion des voyants

Voyant	Signification

Vert (disponibilité)	Borne prête

Rouge (charge)	Charge en cours

Clignotement	Authentification / défaut

OFF	Système inactif

Gestion du temps

Le module timer permet :
1.	Les temporisations du système,
2.	Le clignotement des voyants,
3.	La gestion des délais (boutons, sécurité).

