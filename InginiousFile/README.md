Projet 1 : Synchronisation multi-threadée

Introduction

Ce projet aborde trois problèmes de synchronisation :

Producteurs-Consommateurs
Lecteurs-Écrivains
Philosophes
Nous comparons des mécanismes de synchronisation personnalisés (TAS et TATAS) avec les primitives POSIX et analysons leurs performances.

A - Implémentations

    1 - Producteurs-Consommateurs : Mise en œuvre d'un buffer circulaire permettant aux producteurs d'ajouter des éléments et aux consommateurs de les retirer sans risque d'incohérence.

    2 - Lecteurs-Écrivains : Utilisation de mécanismes de synchronisation garantissant l'équité entre lecteurs (qui peuvent accéder simultanément aux données) et écrivains (qui doivent être exclusifs), afin d'éviter la famine.

    3 - Philosophes : Résolution du problème classique des philosophes mangeurs, en garantissant un partage des ressources sans interblocage (deadlock) et sans famine, en utilisant des algorithmes de synchronisation adaptés.

    4 - TAS et TATAS et Interfaces semaphores (post & wait ) : Ces mécanismes sont basés sur l'instruction atomique xchgl pour réaliser des opérations d'exclusion  mutuelle entre threads, garantissant ainsi une synchronisation correcte et efficace.

B - Organisation des Dossiers et Fichiers

    1 - Sourcefile/ : Contient tous les fichiers source implémentant les différents problèmes avec les mécanismes de synchronisation (POSIX, TAS et TATAS).

    2 - DataInginious/ : Contient les fichiers CSV générés par le serveur d'Inginious lors de l'exécution des tests.

    3 - ScriptBash2.sh : Script Bash automatisant l'exécution des tests pour générer les fichiers CSV à partir des programmes compilés. Il est utilisé pour exécuter les simulations sur les problèmes synchronisés et enregistrer les résultats.

    4 - scriptPython.py : Ce script génère des graphiques individuels à partir des fichiers CSV ou permet de comparer les résultats de TAS et TATAS pour le même problème, en affichant les différences de performance.

    5 - scriptPython3Graphs.py : Ce script permet de comparer les résultats des différentes implémentations (POSIX, TAS et TATAS) en générant des graphiques comparatifs pour chacun des problèmes étudiés (Producteurs-Consommateurs, Lecteurs-Écrivains, Philosophes).

    6 - Makefile : 

C - 
    Graphique (Données Inginious) : make all
    Nettoyage : make clean
    Aide : make help


D - Notes importante : 
    1 - Un problème subsiste dans l'organisation des fichiers pour les tests de performance des lecteurs/écrivains. Le fichier read2.c a été utilisé pour générer les résultats liés aux primitives POSIX. Cependant, le fichier read.c a été modifié pour intégrer nos propres mutex et sémaphores personnalisés (TAS/TATAS), 
    et read2.c n'a pas été converti pour ces mécanismes. Cependant read.c et read2.c ont exactement les mêmes graphes lors de la compilation.

    2 - Le script Bash (scriptBash.sh) est conçu pour exécuter les tests et récupérer les résultats sous forme de fichiers CSV. Il redirige la sortie vers stdout (standard output), mais dans le Makefile, il n'est pas directement utilisé pour l'affichage des résultats. Il est principalement destiné à être utilisé pour générer des fichiers CSV à partir des données des tests Inginious et non pour l'affichage en temps réel dans le terminal.

    3 - Il est également possible de générer des graphiques à partir des données locales issues des exécutions réelles, c'est-à-dire des résultats produits par vos propres tests lors de l'exécution du programme. Ces données locales sont stockées dans le dossier Csvfile et peuvent être utilisées pour générer des graphiques distincts de ceux produits à partir des données Inginious, qui sont présentes dans le dossier DataInginious. (Fait un make help pour plus d'informations)

    4 - Des dossiers tels que Csvfile, Plots, et Objfile seront générés lors de l'exécution du Makefile. Ils contiendront respectivement des fichiers CSV, des fichiers objets et des graphiques issus des exécutions réelles. Ces dossiers peuvent être supprimés en exécutant la commande make clean.