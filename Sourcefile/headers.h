#ifndef HEADERS_H
#define HEADERS_H

void verrou_lock(int *verrou);
void verrou_lock2(int *verrou);
void semaphore_wait(int *compteur, int *verrou);
void semaphore_wait2(int *compteur, int *verrou);
void semaphore_post(int *compteur);
void verrou_unlock(int *verrou);







#endif