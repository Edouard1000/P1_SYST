#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define ITEMS 131072  

int buffer[8];         // buffer circulaire avec une capacité de 8 éléments
int inProd = 0;        // Indice d'insertion pour le producteur
int outCons = 0;       // Indice de consommation pour le consommateur
int prodCount = 0;     // Nombre total d'éléments courant produits
int consCount = 0;     // Nombre total d'éléments courant consommés

pthread_mutex_t mutex; // Mutex pour protéger l'accès au buffer partagé
pthread_mutex_t mutex2; // Mutex pour protéger les compteurs prodCount et consCount

sem_t empty;           // Sémaphore pour compter les espaces disponibles dans le buffer
sem_t full;            // Sémaphore pour compter les éléments disponibles dans le buffer


void process() {
    for (size_t i = 0; i < 10000; i++) {
        // Ne fait rien, c'est juste pour simuler une opération lente
    }
}

// Fonction exécutée par chaque thread producteur
void* producteur(void* arg) {
    int idPthread = *(int*)arg; 

    while (true) {
        pthread_mutex_lock(&mutex2);
        if (prodCount == ITEMS) {
            pthread_mutex_unlock(&mutex2);
            break;  // Si on a produit ITEMS éléments, le producteur arrête de produire
        }  
        prodCount++;
        pthread_mutex_unlock(&mutex2);

        sem_wait(&empty);  // Attente jusqu'à ce qu'il y ait de la place dans le buffer
        pthread_mutex_lock(&mutex);  // Accès exclusif au buffer partagé

        
        buffer[inProd] = idPthread;
        inProd = (inProd + 1) % 8;  // Mise à jour de l'indice du producteur
        
        pthread_mutex_unlock(&mutex); // Libération du verrou
        sem_post(&full);  // Signal qu'un nouvel élément est disponible pour la consommation
  

        process(); // Simule une tâche coûteuse

    }
    return NULL;
}


void* consommateur(void* arg) {
    while (true) {
        pthread_mutex_lock(&mutex2);
        if (consCount == ITEMS) {
            pthread_mutex_unlock(&mutex2);
            break;  // Si on a consommé ITEMS éléments, le consommateur arrête de consommer
        }  
        consCount++;
        pthread_mutex_unlock(&mutex2);

        sem_wait(&full);  // Attente jusqu'à ce qu'un élément soit disponible à consommer
        pthread_mutex_lock(&mutex);  // Accès exclusif au tampon partagé

   
        int elem = buffer[outCons];
        outCons = (outCons + 1) % 8;  // Mise à jour de l'indice du consommateur

        pthread_mutex_unlock(&mutex); // Libération du verrou
        sem_post(&empty);  // Signal qu'un espace est maintenant libre dans le buffer

        process(); // Simule une tâche coûteuse


    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
      
        return 1;
    }

    // Initialisation des sémaphores et mutex
    sem_init(&empty, 0, 8);  
    sem_init(&full, 0, 0);   
    pthread_mutex_init(&mutex, NULL); 
    pthread_mutex_init(&mutex2, NULL);

    int numbProd = atoi(argv[1]);  // Nombre de producteurs à créer
    int numCons = atoi(argv[2]);   // Nombre de consommateurs à créer

    pthread_t prod[numbProd];  
    pthread_t consum[numCons]; 
    int idsProds[numbProd];    

    // Création des threads producteurs
    for (size_t i = 0; i < numbProd; i++) {
        idsProds[i] = i + 1;  // ID de chaque producteur (commence à 1)
        pthread_create(&prod[i], NULL, producteur, (void*)&idsProds[i]);
    }

  
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

    // Destruction des sémaphores et mutex
    sem_destroy(&empty);   
    sem_destroy(&full);     
    pthread_mutex_destroy(&mutex);  
    pthread_mutex_destroy(&mutex2);  


  

    return 0;
}
