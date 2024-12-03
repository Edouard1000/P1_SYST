#include "headers.h"

void semaphore_wait(int *compteur, int *verrou) {
    __asm__ __volatile__(
        // Acquisition du verrou
        "lock_acquire:              \n"
        "movl $1, %%eax;            \n"  
        "xchgl %%eax, %[verrou];    \n"  // mon mutex "maison"
        "testl %%eax, %%eax;        \n"  
        "jnz lock_acquire;          \n"  

        // Début de la section critique protégée par le verrou
        "wait_loop:                 \n"  // Boucle d'attente active
        "movl %[compteur], %%eax;   \n"  // Charger la valeur du compteur dans %eax
        "testl %%eax, %%eax;        \n"  // Vérifier si le compteur > 0
        "jz release_and_wait;       \n"  // Si compteur == 0, libérer le verrou et attendre
        "subl $1, %[compteur];      \n"  // Décrémenter le compteur (non atomique car protégé par verrou)

        // Sortie normale
        "movl $0, %[verrou];        \n"  // Libérer le verrou
        "jmp done;                  \n"  // Fin de la fonction

        // Libérer le verrou et attendre si le compteur est 0
        "release_and_wait:          \n"
        "movl $0, %[verrou];        \n"  // Libérer le verrou
        "jmp lock_acquire;          \n"  // Recommence la boucle d'acquisition du verrou

        "done:                      \n"
        :
        : [compteur] "m" (*compteur), [verrou] "m" (*verrou) // Variables compteur et verrou
        : "%eax", "memory"                                  // Registres utilisés et mémoire modifiée
    );
}

void semaphore_wait2(int *compteur, int *verrou) {
    __asm__ __volatile__(
        "lock_acquire_2:              \n"
        "cmpl $0, %[verrou];          \n"
        "jne lock_acquire_2;          \n"
        "movl $1, %%eax;              \n"
        "xchgl %%eax, %[verrou];      \n"
        "testl %%eax, %%eax;          \n"
        "jnz lock_acquire_2;          \n"  

        "wait_loop_2:                 \n"
        "movl %[compteur], %%eax;     \n"
        "testl %%eax, %%eax;          \n"
        "jz release_and_wait_2;       \n"
        "subl $1, %[compteur];        \n"

        "movl $0, %[verrou];          \n"
        "jmp done_2;                  \n"

        "release_and_wait_2:          \n"
        "movl $0, %[verrou];          \n"
        "jmp lock_acquire_2;          \n"

        "done_2:                      \n"
        :
        : [compteur] "m" (*compteur), [verrou] "m" (*verrou)
        : "%eax", "memory"
    );
}


void semaphore_post(int *compteur) {
    __asm__ __volatile__(
        "lock addl $1, %[compteur]; \n"  
        :
        : [compteur] "m" (*compteur)
        : "memory"
    );
}

