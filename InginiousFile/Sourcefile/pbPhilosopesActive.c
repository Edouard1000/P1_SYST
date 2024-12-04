#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "headers.h"

typedef struct {
    int N;            // Nombre de philosophes
    int ids;          // Identifiant du philosophe (de 0 à N-1)
    int* verrous;     // Tableau de verrous (entiers) pour chaque philosophe
} Arguments;

// Fonction pour simuler le processus de manger
void manger(int i) {

}


// Fonction pour simuler le processus de penser
void penser(int i) {

}

// Fonction exécutée par chaque philosophe (thread)
void* philosopher(void* arg) {
    Arguments* arguments = (Arguments*)arg;
    int N = arguments->N;       // Nombre de philosophes
    int i = arguments->ids;     // Identifiant du philosophe
    int* verrous = arguments->verrous;  // Tableau de verrous pour la synchronisation

    int gauche = i;             // Philosophe de gauche
    int droite = (i + 1) % N;   // Philosophe de droite (index circulaire)

    for (size_t idx = 0; idx < 1000000; idx++) {  // Nombre d'itérations pour la simulation
    
        penser(i);  // Philosophe pense

        // Philosophe essaie de prendre les fourchettes (verrous) dans un ordre spécifique pour éviter un deadlock
        if (gauche < droite) {
            verrou_lock(&verrous[gauche]);  // Prendre la fourchette gauche
            verrou_lock(&verrous[droite]);  // Prendre la fourchette droite
        } else {
            verrou_lock(&verrous[droite]);  // Prendre la fourchette droite
            verrou_lock(&verrous[gauche]);  // Prendre la fourchette gauche
        }

        manger(i);  // Philosophe mange

        // Relâcher les fourchettes (verrous)
        verrou_unlock(&verrous[droite]);
        verrou_unlock(&verrous[gauche]);
    }
    
    return NULL;
}

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);  // Nombre de philosophes (nombre de threads)
    pthread_t Philosophes[N];  // Tableau de threads pour les philosophes
    int verrous[N];            // Tableau de verrous pour chaque philosophe

    Arguments arguments[N];    // Tableau d'arguments pour chaque philosophe (thread)

    // Initialisation des verrous
    for (int i = 0; i < N; i++) {
        verrous[i] = 0;  // Initialisation : tous les verrous sont disponibles
    }

    // Création des threads pour les philosophes
    for (int i = 0; i < N; i++) {
        arguments[i].N = N;
        arguments[i].ids = i;
        arguments[i].verrous = verrous;

        if (pthread_create(&Philosophes[i], NULL, philosopher, (void*)&arguments[i]) != 0) {
            perror("Erreur de création de thread");
            return 1;
        }
    }
    
    // Attente de la fin de tous les threads (les philosophes)
    for (int i = 0; i < N; i++) {
        pthread_join(Philosophes[i], NULL);
    }

    return 0;
}
