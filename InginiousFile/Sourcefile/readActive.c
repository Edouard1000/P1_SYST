#include "headers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NBR_ECRITURES 640
#define NBR_LECTURES 2540

// Initialisation des variables
int countEcritures = 0;            // Compte le nombre d'écritures totales courantes
int countLectures = 0;             // Compte le nombre de lectures totales courantes
int writeCount = 0;                // S'assure de stopper/relancer un thread qui souhaite lire la BD dès qu'un thread d'écriture est prête/terminée
int readCount = 0;                 // S'assure de stopper/relancer un thread qui souhaite écrire sur la BD dès qu'un thread de lecture est prête/terminée

// Variables pour les mutex et sémaphores personnalisés
int verrouCount = 1;
int verrouReader = 1;
int verrouWriter = 1;

int writerSem = 1;
int readerSem = 1;

void readDbProcess(void) {
    for (size_t i = 0; i < 10000; i++) {
        /* ceci est une simulation */
    }
}

void writeDbProcess(void) {
    for (size_t i = 0; i < 10000; i++) {
        /* ceci est une simulation */
    }
}

void* writer(void* arg) {
    int id = *((int*)arg);  // Identifiant de l'écrivain

    while (true) {
        // Vérifions si le thread courant doit nécessairement écrire
        verrou_lock(&verrouCount);
        if (countEcritures > NBR_ECRITURES) {
            verrou_unlock(&verrouCount);
            return NULL;
        }
        countEcritures++; // S'il traverse la condition, cela signifie qu'il y a encore des écritures à faire
        verrou_unlock(&verrouCount);

        verrou_lock(&verrouWriter);
        writeCount++;

        if (writeCount == 1) {
            semaphore_wait(&readerSem);
        }

        verrou_unlock(&verrouWriter);

        semaphore_wait(&writerSem);

        writeDbProcess();
        semaphore_post(&writerSem);

        verrou_lock(&verrouWriter);
        writeCount--;

        if (writeCount == 0) {
            semaphore_post(&readerSem);
        }
        verrou_unlock(&verrouWriter);
    }

    return NULL;
}

void* reader(void* arg) {
    int id = *((int*)arg);  // Identifiant du lecteur

    while (true) {
        // Vérifions si le thread courant doit nécessairement lire
        verrou_lock(&verrouCount);
        if (countLectures > NBR_LECTURES) {
            verrou_unlock(&verrouCount);
            return NULL;
        }

        countLectures++; // S'il traverse la condition, cela signifie qu'il y a encore des lectures à faire
        verrou_unlock(&verrouCount);

        verrou_lock(&verrouReader);
        readCount++;

        if (readCount == 1) {
            semaphore_wait(&writerSem);
        }
        verrou_unlock(&verrouReader);

        readDbProcess();

        verrou_lock(&verrouReader);
        readCount--;
        if (readCount == 0) {
            semaphore_post(&writerSem); // Le writer dans la queue va s'exécuter à ce niveau
        }
        verrou_unlock(&verrouReader);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }

    int nbrLecteurs = atoi(argv[2]);
    int nbrEcrivains = atoi(argv[1]);

    pthread_t readers[nbrLecteurs];
    pthread_t writers[nbrEcrivains];

    int readerIds[nbrLecteurs];
    int writerIds[nbrEcrivains];

    // Création des threads lecteurs
    for (int i = 0; i < nbrLecteurs; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    // Création des threads écrivains
    for (int i = 0; i < nbrEcrivains; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Attente de la fin des threads lecteurs
    for (int i = 0; i < nbrLecteurs; i++) {
        pthread_join(readers[i], NULL);
    }

    // Attente de la fin des threads écrivains
    for (int i = 0; i < nbrEcrivains; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
