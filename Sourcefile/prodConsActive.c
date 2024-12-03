#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "headers.h"

#define ITEMS 131072

int buffer[8];         // Buffer circulaire avec une capacité de 8 éléments
int inProd = 0;        // Indice d'insertion pour le producteur
int outCons = 0;       // Indice de consommation pour le consommateur
int prodCount = 0;     // Nombre total d'éléments produits
int consCount = 0;     // Nombre total d'éléments consommés

// Mutex personnalisés
int mutex = 0;
int mutex2 = 0;

// Sémaphores personnalisés
int empty_compteur = 8;
int empty_verrou = 0;

int full_compteur = 0;
int full_verrou = 0;

void process() {
    for (size_t i = 0; i < 10000; i++) {
        // Simulation d'une opération lente
    }
}


void* producteur(void* arg) {
    int idPthread = *(int*)arg; 

    while (true) {
        verrou_lock(&mutex2);
        if (prodCount == ITEMS) {
            verrou_unlock(&mutex2);
            break;  // Si on a produit ITEMS éléments, le producteur arrête de produire
        }  
        prodCount++;
        verrou_unlock(&mutex2);

        semaphore_wait(&empty_compteur, &empty_verrou);  // Attente jusqu'à ce qu'il y ait de la place
        verrou_lock(&mutex);  // Accès exclusif au buffer partagé

        buffer[inProd] = idPthread;
        inProd = (inProd + 1) % 8;  // Mise à jour de l'indice du producteur

        verrou_unlock(&mutex);  // Libération du verrou
        semaphore_post(&full_compteur);  // Signal qu'un nouvel élément est disponible

        process(); // Simule une tâche coûteuse
    }
    return NULL;
}

void* consommateur(void* arg) {
    while (true) {
        verrou_lock(&mutex2);
        if (consCount == ITEMS) {
            verrou_unlock(&mutex2);
            break;  // Si on a consommé ITEMS éléments, le consommateur arrête de consommer
        }  
        consCount++;
        verrou_unlock(&mutex2);

        semaphore_wait(&full_compteur, &full_verrou);  // Attente jusqu'à ce qu'un élément soit disponible
        verrou_lock(&mutex);  // Accès exclusif au tampon partagé

        int elem = buffer[outCons];
        outCons = (outCons + 1) % 8;  // Mise à jour de l'indice du consommateur

        verrou_unlock(&mutex);  // Libération du verrou
        semaphore_post(&empty_compteur);  // Signal qu'un espace est maintenant libre

        process(); // Simule une tâche coûteuse
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <num_producers> <num_consumers>\n", argv[0]);
        return 1;
    }

    int numbProd = atoi(argv[1]);  // Nombre de producteurs à créer
    int numCons = atoi(argv[2]);  // Nombre de consommateurs à créer

    pthread_t prod[numbProd];  
    pthread_t consum[numCons]; 
    int idsProds[numbProd];    

    // Création des threads producteurs
    for (size_t i = 0; i < numbProd; i++) {
        idsProds[i] = i + 1;  // ID de chaque producteur (commence à 1)
        pthread_create(&prod[i], NULL, producteur, (void*)&idsProds[i]);
    }

    // Création des threads consommateurs
    for (size_t i = 0; i < numCons; i++) {
        pthread_create(&consum[i], NULL, consommateur, NULL);
    }

    // Attente de la fin de tous les threads producteurs
    for (size_t i = 0; i < numbProd; i++) {
        pthread_join(prod[i], NULL);
    }

    // Attente de la fin de tous les threads consommateurs
    for (size_t i = 0; i < numCons; i++) {
        pthread_join(consum[i], NULL);
    }

    return 0;
}