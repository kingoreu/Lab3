#include "struct_memory.h"
#include "semaphore.h"

int main() {
    int shm_id, sem_id;
    struct shared_memory *shm_ptr;
    FILE *destination_file;
    size_t bytes_written;

    // 공유 메모리와 세마포어 연결
    shm_id = shmget(SHM_KEY, sizeof(struct shared_memory), 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }
    shm_ptr = (struct shared_memory *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    sem_id = semget(SEM_KEY, 1, 0666);
    if (sem_id == -1) {
        perror("semget failed");
        exit(1);
    }

    // 대상 파일 열기
    destination_file = fopen("destination.txt", "w");
    if (destination_file == NULL) {
        perror("Failed to open destination file");
        exit(1);
    }

    while (1) {
        P(sem_id);  // 부모가 데이터를 공유 메모리에 쓸 때까지 대기

        bytes_written = fwrite(shm_ptr->buffer, 1, shm_ptr->length, destination_file);
        if (bytes_written == 0) {
            break;
        }

        V(sem_id);  // 부모가 데이터를 쓸 수 있도록 세마포어 해제

        if (shm_ptr->length < BUFFER_SIZE) {
            break;
        }
    }

    fclose(destination_file);
    return 0;
}
