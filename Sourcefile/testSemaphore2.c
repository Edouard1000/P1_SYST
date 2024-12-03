#include "headers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int verrou;
int nbrThread;
long global;

void process(void){
    for (size_t i = 0; i < 10000; i++){
        /* Simulation, ne fait r */
    }
    
} 

void *testDESVerrou(void *arg){
    int id = *((int*) arg); 
    int nbrCycle = 32768/nbrThread;

    for (size_t i = 0; i < nbrCycle; i++){
        

        
        semaphore_wait2(&compteur, &verrou);        
        process();
        semaphore_post(&compteur);

        
    }
    
}

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("erreur \n");
        return 1;
    }
    
    verrou=0;
    compteur=1;
    nbrThread = atoi(argv[1]);
    pthread_t thread[nbrThread];
    int ids[nbrThread];

    for (size_t i = 0; i < nbrThread; i++){
        ids[i]=i+1;
        pthread_create(&(thread[i]), NULL, &testDESVerrou, (void*)&ids[i]);
    }

    for (size_t i = 0; i < nbrThread; i++){
        pthread_join(thread[i],NULL);
    }

    
    return 0;
    
    



}
