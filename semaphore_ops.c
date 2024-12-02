#include "struct_memory.h"
#include "semaphore.h"

// P 연산 (세마포어 값을 1로 감소)
void P(int semid) {
    struct sembuf sem_op = {0, -1, 0};
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop P failed");
        exit(1);
    }
}

// V 연산 (세마포어 값을 1로 증가)
void V(int semid) {
    struct sembuf sem_op = {0, 1, 0};
    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop V failed");
        exit(1);
    }
}
