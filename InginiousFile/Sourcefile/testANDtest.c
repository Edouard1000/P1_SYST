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

void *testDESVerrou2(void *arg){
    int id = *((int*) arg); 
    int nbrCycle = 32768/nbrThread;

    for (size_t i = 0; i < nbrCycle; i++){
        

        //printf("je suis le thread %d, jattend le verrou \n", id);
        verrou_lock2(&verrou);
        
        //printf("je suis le thread %d, j'ai acqui le verrou \n", id);
        
        process();
        verrou_unlock(&verrou);

        //printf("je suis le thread %d, je libere le verrou \n", id);
    }
    
}

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("erreur \n");
        return 1;
    }
    
    verrou=0;
    nbrThread = atoi(argv[1]);
    pthread_t thread[nbrThread];
    int ids[nbrThread];

    for (size_t i = 0; i < nbrThread; i++){
        ids[i]=i+1;
        pthread_create(&(thread[i]), NULL, &testDESVerrou2, (void*)&ids[i]);
    }

    for (size_t i = 0; i < nbrThread; i++){
        pthread_join(thread[i],NULL);
    }

    
    return 0;
    
    



}
