# ⚡ Borne de Recharge pour Véhicule Électrique – Projet C
Squelette de développement pour le projet de borne de recharge de véhicule électrique (travaux pratiques EEA)

Squelette du code de commande de la borne de recharge. Projet à but pédagogique.

make clean
make depend
make
ipcclean
sim_borne &.
./borne


Description du projet

Ce projet consiste à développer le logiciel de contrôle d’une borne de recharge pour véhicule électrique, implémenté en langage C et exécuté sur une plateforme embarquée simulée.
Le système permet :
•	L’authentification des utilisateurs par carte,
•	La gestion complète du cycle de charge,
•	La sécurisation de la prise et de la trappe,
•	L’indication de l’état du système via des voyants lumineux,
•	Un mode administrateur pour la gestion des clients.

Le projet a été conçu selon une démarche de conception UML, avant toute implémentation, afin de garantir une architecture claire, modulaire et maintenable.

Conception UML

La conception du système repose sur plusieurs modèles UML, réalisés en amont du développement :
Modèles utilisés
•	Diagrammes de cas d’utilisation
o	Mode utilisateur
o	Mode administrateur
•	Diagrammes de séquence
o	Lecture de carte
o	Authentification client
o	Processus de charge
o	Reprise du véhicule
•	Diagramme d’états
o	Machine à états finis (MEF) du générateur de charge
Avantages de l’approche UML
•	Vision claire du fonctionnement global
•	Séparation nette des responsabilités entre modules
•	Traduction directe des diagrammes en code C
•	Facilité de maintenance et d’évolution du système
 
Architecture logicielle
Le projet est organisé de manière modulaire, chaque composant fonctionnel étant isolé dans un module dédié.

Module	Rôle
lecteurcarte	: Lecture et validation des cartes
base_clients	: Gestion des clients et du mode administrateur
generateur_save	: Machine à états de charge (PWM, AC, DC)
prise	: Gestion de la prise et de la trappe
voyant	: Gestion des voyants (charge, défaut, disponibilité)
bouton	: Gestion des boutons (charge, arrêt)
timer :	Gestion des temporisations
Borne	: Point d’entrée du programme

Fonctionnement global

Mode Utilisateur

1.	Insertion de la carte
2.	Authentification du client
3.	Démarrage du processus de charge
4.	Gestion sécurisée de la charge (MEF)
5.	Fin de charge
6.	Réinsertion de la carte pour reprise du véhicule
   
Mode Administrateur

•	Ajout d’un client
•	Suppression d’un client
•	Consultation de la base des clients
•	Accès sécurisé par code administrateur

Gestion des voyants

Voyant	Signification
Vert (disponibilité)	Borne prête
Rouge (charge)	Charge en cours
Clignotement	Authentification / défaut
OFF	Système inactif

Gestion du temps

Le module timer permet :
•	Les temporisations du système,
•	Le clignotement des voyants,
•	La gestion des délais (boutons, sécurité).

