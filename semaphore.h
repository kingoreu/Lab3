#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/sem.h>

void semaphore(int sem_id);  // 세마포어 초기화 함수
void P(int sem_id);         // P 연산 (wait)
void V(int sem_id);         // V 연산 (signal)

#endif
