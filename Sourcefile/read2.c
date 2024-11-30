#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>


int reader_count = 0; // Nombre de lecteurs actifs
int total_reads = 0;  // Total de lectures effectuées
int total_writes = 0; // Total d'écritures effectuées
int max_reads, max_writes; // Limites pour les lectures et écritures

// Mutex et sémaphores
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Protéger reader_count
sem_t resource;                                   // Gérer l'accès exclusif à la ressource
sem_t queue;                                      // File d'attente équitable pour lecteurs/rédacteurs

void readDbProcess(void){
    for (size_t i = 0; i < 10000; i++){
        /* ceci est une simulation*/
    }
    
}

void writeDbProcess(void){
    for (size_t i = 0; i < 10000; i++){
        /* ceci est une simulation*/
    }
    
}

void* reader(void* arg) {
    int id = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (total_reads >= max_reads) { // Vérifie si toutes les lectures ont été effectuées
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        // Attente dans la file d'attente pour garantir l'équité
        sem_wait(&queue);

        pthread_mutex_lock(&mutex);
        if (reader_count == 0) {
            sem_wait(&resource); // Premier lecteur bloque l'accès exclusif
        }
        reader_count++;
        pthread_mutex_unlock(&mutex);

        // Signale que la file d'attente peut avancer
        sem_post(&queue);

        // Lecture dans la zone critique
        pthread_mutex_lock(&mutex);
        if (total_reads < max_reads) {
            readDbProcess();

            total_reads++;
        }
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&resource); 
        }
        pthread_mutex_unlock(&mutex);

        
    }

    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    while (1) {
        pthread_mutex_lock(&mutex);
        if (total_writes >= max_writes) { // Vérifie si toutes les écritures ont été effectuées
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        // Attente dans la file d'attente pour garantir l'équité
        sem_wait(&queue);

        // Accès exclusif à la ressource partagée
        sem_wait(&resource);

        // Signale que la file d'attente peut avancer
        sem_post(&queue);

        // Écriture dans la zone critique
        pthread_mutex_lock(&mutex);
        if (total_writes < max_writes) {
            writeDbProcess();
            total_writes++;
        }
        pthread_mutex_unlock(&mutex);

        sem_post(&resource); // Libère l'accès exclusif

    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_readers> <num_writers>\n", argv[0]);
        return 1;
    }

    int num_readers = atoi(argv[1]);
    int num_writers = atoi(argv[2]);

    if (num_readers <= 0 || num_writers <= 0) {
        fprintf(stderr, "Both the number of readers and writers must be positive integers.\n");
        return 1;
    }

    // Limites pour les lectures et écritures
    max_reads = 2540;
    max_writes = 640;

    pthread_t readers[num_readers];
    pthread_t writers[num_writers];
    

    int readerIds[nbrLecteurs];
    int writerIds[nbrEcrivains];

    // Initialisation des sémaphores
    sem_init(&resource, 0, 1); // Ressource partagée disponible
    sem_init(&queue, 0, 1);    // File d'attente initialisée avec une unité

    // Création des threads lecteurs
    for (int i = 0; i < num_readers; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    // Création des threads rédacteurs
    for (int i = 0; i < num_writers; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Attente de la terminaison des threads
    for (int i = 0; i < num_readers; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < num_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destruction des sémaphores
    sem_destroy(&resource);
    sem_destroy(&queue);

    printf("All reads and writes have been completed.\n");

    return 0;
}
