#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NB_ECRITURES 640
#define NB_LECTURES 2540

pthread_mutex_t mutex;
sem_t db; // Sémaphore pour l'accès à la base de données
sem_t priority; // Priorité pour les écrivains
int readcount = 0; // Nombre de lecteurs actifs
int total_writes = 0;
int total_reads = 0;

void *writer(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        if (total_writes >= NB_ECRITURES) {
            pthread_mutex_unlock(&mutex);
            break; // Stop si le nombre total d'écritures est atteint
        }
        total_writes++;
        pthread_mutex_unlock(&mutex);

        sem_wait(&priority); // Empêche de nouveaux lecteurs d'entrer
        sem_wait(&db); // Accès exclusif à la base de données

        // Section critique : écriture simulée
        for (int i = 0; i < 10000; i++);
       

        sem_post(&db); // Libère l'accès à la base de données
        sem_post(&priority); // Permet aux lecteurs d'entrer à nouveau
    }
    return NULL;
}

void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        if (total_reads >= NB_LECTURES) {
            pthread_mutex_unlock(&mutex);
            break; // Stop si le nombre total de lectures est atteint
        }
        total_reads++;
        pthread_mutex_unlock(&mutex);

        sem_wait(&priority); // Donne la priorité aux écrivains
        pthread_mutex_lock(&mutex);

        readcount++;
        if (readcount == 1) {
            sem_wait(&db); // Premier lecteur bloque l'accès des écrivains
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&priority); // Permet aux écrivains d'attendre si nécessaire

        // Section critique : lecture simulée
        for (int i = 0; i < 10000; i++);
       

        pthread_mutex_lock(&mutex);

        readcount--;
        if (readcount == 0) {
            sem_post(&db); // Dernier lecteur libère l'accès aux écrivains
        }

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
     
        return EXIT_FAILURE;
    }

    int nb_writers = atoi(argv[1]);
    int nb_readers = atoi(argv[2]);

    pthread_t writers[nb_writers];
    pthread_t readers[nb_readers];

    int writer_ids[nb_writers];
    int reader_ids[nb_readers];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&db, 0, 1);
    sem_init(&priority, 0, 1);

    for (int i = 0; i < nb_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < nb_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < nb_writers; i++) {
        pthread_join(writers[i], NULL);
    }

    for (int i = 0; i < nb_readers; i++) {
        pthread_join(readers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&db);
    sem_destroy(&priority);

    return EXIT_SUCCESS;
}
