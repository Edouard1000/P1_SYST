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
    
/*
void semaphore_wait(int *compteur, int verrou) {

    verrou_lock(&verrou);
    __asm__ __volatile__(
        // Acquisition du verrou
        "lock_acquire:              \n"
        "movl $0, %%eax;            \n"  
        "xchgl %%eax, %[compteur];    \n"  // mon mutex "maison"
        "cmpl $0, %%eax;           \n"
        "je wait_loop;                  \n"
        "jl release_and_wait;                  \n"


        // Début de la section critique protégée par le verrou
        "wait_loop:                 \n"  // Boucle d'attente active
        //"movl %[compteur], %%edx;   \n"  // Charger la valeur du compteur dans %eax
        "cmpl $1, %[compteur];        \n"  // Vérifier si le compteur > 0
        "jg wait_loop;       \n"  // Si compteur == 0, libérer le verrou et attendre
        "jle release_and_wait;      \n"  // Décrémenter le compteur (non atomique car protégé par verrou)



        // Libérer le verrou et attendre si le compteur est 0
        "release_and_wait:          \n"
        "subl $1, %[compteur];        \n"  // Libérer le verrou
        "jmp done;          \n"  // Recommence la boucle d'acquisition du verrou

        "done:                      \n"
        :
        : [compteur] "m" (*compteur) // Variables compteur et verrou
        : "%eax", "memory", "%edx"                                  // Registres utilisés et mémoire modifiée
    );

    verrou_unlock(&verrou);
}



void semaphore_post(int *compteur) {
    verrou_lock2(&verr);
    __asm__ __volatile__(
        "addl $1, %[compteur]; \n"  
        :
        : [compteur] "m" (*compteur)
        : "memory"
    );
    verrou_unlock(&verr);
}

//D'apres le chat cette version de seMmwait est mieu: on verra
 
void semaphore_wait(int *compteur) {
    verrou_lock2(&verr);  // Acquérir le verrou avant de manipuler le compteur

    __asm__ __volatile__(
        "wait_loop:                 \n"
        "    movl %[compteur], %%eax; \n"  // Charger la valeur du compteur dans eax
        "    cmpl $0, %%eax;          \n"  // Comparer avec 0
        "    jg continue_waiting;     \n"  // Si le compteur > 0, continuer
        "    jmp wait_loop;           \n"  // Si le compteur == 0, revenir à la boucle d'attente

        "continue_waiting:           \n"
        "    subl $1, %[compteur];    \n"  // Décrémenter le compteur atomiquement
        :
        : [compteur] "m" (*compteur)
        : "%eax", "memory"
    );

    verrou_unlock(&verr);  // Libérer le verrou
}
 
*/

