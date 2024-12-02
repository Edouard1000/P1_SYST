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
            "cmpl $0, %[verrou];     \n"  // Vérifie si verrou == 0 (test)
            "jne start;              \n"  // Si verrou pris, boucle jusqu'à ce qu'il soit libéré
            "movl $1, %%eax;         \n"  // Charge 1 dans %eax
            "xchgl %%eax, %[verrou]; \n"  // Test-and-Set : verrouille atomiquement
            "testl %%eax, %%eax;     \n"  // Vérifie si verrou a été pris avec succès
            "jnz start;              \n"  // Si échoue (déjà pris), retente
            :
            : [verrou] "m" (*verrou)       // Entrée : pointeur sur le verrou
            : "%eax", "memory"             // Clobbers : registre %eax et mémoire
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
