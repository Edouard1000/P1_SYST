#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NBR_ECRITURES 640
#define NBR_LECTURES 2540

//Initialisation des variables
int countEcritures=0;            //Compte le nombre de Ecritures totale courant 
int countLectures=0;               //Compte le nombre de Lectures totale courant 
int writeCount=0;                  //S'assure de stoper/relancer un thread qui souhaite lire la BD dès qu'un thread d'ecriture est prete/terminée
int readCount=0;                   //S'assure de stoper/relancer un thread qui souhaite ecrire sur la BD dès qu'un thread de lecture est prete/terminée

//Declaration des mutex et semaphores
pthread_mutex_t mutexCount;
pthread_mutex_t mutexCount2;

pthread_mutex_t mutexReader;
pthread_mutex_t mutexWriter;


sem_t writerSem;
sem_t readerSem;



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


void* writer(void* arg){

    int id = *((int*)arg);  // Identifiant de l'écrivain
 
    while (true){

        //Verifions si thread courant doit necessairement écrire
        pthread_mutex_lock(&mutexCount);
        if (countEcritures>NBR_ECRITURES){
            pthread_mutex_unlock(&mutexCount);
            return NULL;
        }
        countEcritures++;                  // sil traverse la condition cela signifie qu'il y'a encore des ecritures à faire
        pthread_mutex_unlock(&mutexCount);

        pthread_mutex_lock(&mutexWriter);
        writeCount++;

        if(writeCount==1){
            sem_wait(&readerSem);
        }

        pthread_mutex_unlock(&mutexWriter);

        sem_wait(&writerSem);
       

        writeDbProcess();
        sem_post(&writerSem);
        
        pthread_mutex_lock(&mutexWriter);
        writeCount--;

        if (writeCount==0){
            sem_post(&readerSem);
        }
        pthread_mutex_unlock(&mutexWriter);
        
        
    }

    return NULL;
    

}

void* reader(void* arg){

    int id = *((int*)arg);  // Identifiant du lecteur

    while (true){
        //Verifions si le thread courant doit necessairement lire
        pthread_mutex_lock(&mutexCount);
        if (countLectures>NBR_LECTURES){
            pthread_mutex_unlock(&mutexCount);
            return NULL;
        }

       

        countLectures++;                  // sil traverse la condition cela signifie qu'il y'a encore des lectures à faire
        pthread_mutex_unlock(&mutexCount);
        
       
        pthread_mutex_lock(&mutexReader); 
        readCount++;

        if (readCount==1){
            sem_wait(&writerSem);
        }
        pthread_mutex_unlock(&mutexReader);
 
        readDbProcess();
        pthread_mutex_lock(&mutexReader);
        readCount--;
        if(readCount==0)
            sem_post(&writerSem);                 // je pense que c'est le writer dans le quue qui va s'execute à ce niveau et le reader en attente ne va s'execute que s'il ya plus de lecture et cr ap que le thread courant ait unlock dbmutex;
        pthread_mutex_unlock(&mutexReader);

        

        //printf("j'ai libere le mutexReader \n");
    }
    return NULL;
    

}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        //fprintf(stderr, "Usage: %s <nombre_de_lecteurs> <nombre_d'écrivains>\n", argv[0]);
        return 1;
    }

    int nbrLecteurs = atoi(argv[2]);
    int nbrEcrivains = atoi(argv[1]);

    pthread_t readers[nbrLecteurs];
    pthread_t writers[nbrEcrivains];

    int readerIds[nbrLecteurs];
    int writerIds[nbrEcrivains];

    // Initialisation des semaphores et mutex
    pthread_mutex_init(&mutexCount, NULL);
   //pthread_mutex_init(&mutexCount2, NULL);
    pthread_mutex_init(&mutexReader, NULL);
    pthread_mutex_init(&mutexWriter, NULL);
    sem_init(&writerSem, 0, 1);
    sem_init(&readerSem, 0, 1);

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



    // Destruction des mutex et semaphores
    sem_destroy(&writerSem);
    sem_destroy(&readerSem);
    pthread_mutex_destroy(&mutexCount);
    //pthread_mutex_destroy(&mutexCount2);

    pthread_mutex_destroy(&mutexReader);
    pthread_mutex_destroy(&mutexWriter);

    //printf("operation terminée avec succès :) \n");

    return 0;
}
