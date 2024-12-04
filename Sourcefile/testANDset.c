#include "headers.h"

int verr=0;
int verr2=0;

int test_and_set(int* verrou){
    int oldValue;
    __asm__ __volatile__(
        "xchgl %0, %1;     \n"
        : "=r"(oldValue), "+m"(*verrou)
        : "0"(1)
        : "memory"

    );
    return oldValue;
}

void verrou_lock(int *lock){
    while (test_and_set(lock)){
        
    }
    

}


void verrou_lock2(int *verrou){
    do{
        while (*verrou == 1){
            /* boucle sans appeller l'op atomique en attendant que le verou soit libre*/
        }
        
    } while (test_and_set(verrou)==1);
    

}

void verrou_unlock(int *verrou) {
    *verrou=0;
}


//Semaphore 1 en untilisant test and set

void semaphore_wait(int *compteur) {

    while (*compteur==0){
        
    }
    verrou_lock(&verr);
    (*compteur)--;
    verrou_unlock(&verr);

} 

void semaphore_post(int *compteur) {
    verrou_lock(&verr);
    (*compteur)++;
    verrou_unlock(&verr);
    return;


}

//Semaphore 2 en untilisant test and test

void semaphore_wait2(int *compteur) {

    while (*compteur==0){
        
    }
    verrou_lock2(&verr);
    (*compteur)--;
    verrou_unlock(&verr);

} 

void semaphore_post2(int *compteur) {
    verrou_lock2(&verr);
    (*compteur)++;
    verrou_unlock(&verr);
    return;


}