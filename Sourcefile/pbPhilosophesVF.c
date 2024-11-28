#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    int N;                // Nombre de philosophes
    int ids;                // Identifiant du philosophe (de 0 à N-1)
    pthread_mutex_t* mutex; // Tableau de mutex pour chaque philosophe
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
    int N = arguments->N;      // Nombre de philosophes
    int i = arguments->ids;      // Identifiant du philosophe
    pthread_mutex_t* mutex = arguments->mutex;  // Tableau de mutex pour la synchronisation
    //printf("N = %d \n", N);
    //printf("je suis le thread = %d \n", i);

    int gauche = i;            // Philosophe de gauche
    int droite = (i + 1) % N;  // Philosophe de droite (index circulaire)

    for (size_t idx = 0; idx < 1000000; idx++) {  // Nombre d'itérations pour la simulation
    
        penser(i);  // Philosophe pense

        // Philosophe essaie de prendre les fourchettes (mutex) dans un ordre spécifique pour éviter un deadlock
        if (gauche < droite) {
            //printf("je suis tread, %d,  je suis à mon %d cycle j'attend  le mutex g ou d \n", i, idx);
            pthread_mutex_lock(&mutex[gauche]);  // Prendre la fourchette gauche
            pthread_mutex_lock(&mutex[droite]);  // Prendre la fourchette droite
        } else {
            //printf("je suis tread %d j'attend le mutex g ou d du else \n", i);
            pthread_mutex_lock(&mutex[droite]);  // Prendre la fourchette droite
            pthread_mutex_lock(&mutex[gauche]);  // Prendre la fourchette gauche
        }

        manger(i);  // Philosophe mange

        // Relâcher les fourchettes (mutex)
        pthread_mutex_unlock(&mutex[droite]);        
        pthread_mutex_unlock(&mutex[gauche]);

        //printf(" je suis tread %d, je suis à mon %d cycle, j'ai libere les mutex \n", i, idx);
    }
    
    return NULL;
}

int main(int argc, char* argv[]) {
    int N = atoi(argv[1]);  // Nombre de philosophes (nombre de threads)
    pthread_t Philosophes[N];  // Tableau de threads pour les philosophes
    pthread_mutex_t mutex[N];  // Tableau de mutex pour chaque philosophe

    int err;
    Arguments arguments[N];  // Tableau d'arguments pour chaque philosophe (thread)

    // Initialisation des mutex pour chaque philosophe
    for (int i = 0; i < N; i++) {
        err = pthread_mutex_init(&mutex[i], NULL);  // Initialisation de chaque mutex
        if (err != 0) {
            //perror("Erreur lors de l'initialisation du mutex");
            return 1;
        }
    }

    // Création des threads pour les philosophes
    for (int i = 0; i < N; i++) {
        arguments[i].N = N;
        arguments[i].ids = i;
        arguments[i].mutex = mutex;

        if (pthread_create(&Philosophes[i], NULL, philosopher, (void*)&arguments[i]) != 0) {
            perror("Erreur de création de thread");
            return 1;
        }
    }
    
    // Attente de la fin de tous les threads (les philosophes)
    for (int i = 0; i < N; i++) {
        pthread_join(Philosophes[i], NULL);
    }

    // Destruction des mutex après usage
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&mutex[i]);  
    }



    return 0;
}
