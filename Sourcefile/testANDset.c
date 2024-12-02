#include "headers.h"

void verrou_lock(int *verrou){

    __asm__ __volatile__(
        "enter:                     \n"
            "movl $1, %%eax;     \n"
            "xchgl %%eax, %[verrou];     \n"
            "testl %%eax, %%eax;          \n"
            "jnz enter;                      \n"
            
            :
            : [verrou] "m" (*verrou)
            : "%eax", "memory"

    );

}


void verrou_lock2(int *verrou) {
    __asm__ __volatile__(
        "start:                     \n"
            "movl $1, %%eax;         \n"  // Charge 1 dans %eax
            "xchgl %%eax, %[verrou]; \n"  // Échange atomique entre %eax et verrou
            "testl %%eax, %%eax;     \n"  // Test si verrou == 0
            "jne cache;              \n"  // Si verrou pris, passe en lecture passive
        "cache:                     \n"
            "cmpl $0, %[verrou];     \n"  // Vérifie si verrou == 0
            "jne cache;              \n"  // Si verrou toujours pris, boucle
            "jmp start;              \n"  // Sinon, retente de l'acquérir
            :
            : [verrou] "m" (*verrou)       // Entrée : verrou (en mémoire)
            : "%eax", "memory"             // Clobbers : %eax et mémoire
    );
}

void verrou_unlock(int *verrou) {
    __asm__ __volatile__ (
        "    movl $0, %[verrou];    \n"    
        :                               
        : [verrou] "m" (*verrou)         
        : "memory"                       
    );
}
