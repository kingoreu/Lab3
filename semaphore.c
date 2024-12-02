#include "semaphore.h"
#include "struct_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

void semaphore(int sem_id) {
    // 세마포어 초기화 코드
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } sem_union;

    sem_union.val = 1;  // 세마포어 값 초기화 (1로 설정)
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) {
        perror("semctl failed");
        exit(1);
    }
}
