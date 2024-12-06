Projet 1 : Synchronisation multi-threadée

Introduction

Ce projet aborde trois problèmes de synchronisation :

Producteurs-Consommateurs
Lecteurs-Écrivains
Philosophes
Nous comparons des mécanismes de synchronisation personnalisés (TAS et TATAS) avec les primitives POSIX et analysons leurs performances.

Implémentation

Mécanismes personnalisés : TAS et TATAS basés sur l'instruction atomique xchgl.
Primitives POSIX : Mutexes et sémaphores garantissant exclusion mutuelle et équité.
Problèmes
Producteurs-Consommateurs : Buffer circulaire avec producteurs et consommateurs.
Lecteurs-Écrivains : Garantit l'équité entre lecteurs et écrivains.
Philosophes : Partage des ressources sans interblocage.

Organisation
Fichier source principal : Implémente tous les problèmes (POSIX, TAS et TATAS).
Script Bash : Automatisation des tests pour générer les fichiers CSV.
Scripts Python :
Un script pour tracer des plots individuels ou comparer tas avec tatas.
Un second script pour comparer les résultats des différentes implémentations : Posix, tas et tatas.

Compilation : make plot
Nettoyage : make clean


