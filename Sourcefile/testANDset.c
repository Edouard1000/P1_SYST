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


void verrou_lock2(int *verrou){

    __asm__ __volatile__(
        "start:                     \n"
            "movl $1, %%eax;     \n"
            "xchgl %%eax, %[verrou];     \n"
            "cmpl %%eax, %%eax;          \n"
            "jne cache;                      \n"
            "je fin;                          \n"


        "cache:                        \n"
            "cmpl $0, %[verrou];     \n"      
            "je start;                      \n"
             "jne cache;                      \n"
        "fin:                                 \n"     





            
            :
            : [verrou] "m" (*verrou)
            : "%eax", "memory"

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
