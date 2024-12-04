#ifndef HEADERS_H
#define HEADERS_H

void verrou_lock(int *verrou);
void verrou_lock2(int *verrou);

void verrou_unlock(int *verrou);

void semaphore_wait(int *compteur);
void semaphore_post(int *compteur);

void semaphore_wait2(int *compteur);
void semaphore_post2(int *compteur);









#endif