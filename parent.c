#include "struct_memory.h"
#include "semaphore.h"

int main() {
    int shm_id, sem_id;
    struct shared_memory *shm_ptr;
    FILE *source_file;
    size_t bytes_read;

    // 공유 메모리와 세마포어 생성
    shm_id = shmget(SHM_KEY, sizeof(struct shared_memory), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }
    shm_ptr = (struct shared_memory *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    sem_id = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget failed");
        exit(1);
    }

    semaphore(sem_id); // 세마포어 초기화

    // 파일 열기
    source_file = fopen("source.txt", "r");
    if (source_file == NULL) {
        perror("Failed to open source file");
        exit(1);
    }

    while (1) {
        // 파일을 한 번에 BUFFER_SIZE 만큼 읽기
        P(sem_id);  // 자식이 공유 메모리 접근하기 전에 부모가 접근
        bytes_read = fread(shm_ptr->buffer, 1, BUFFER_SIZE, source_file);
        if (bytes_read == 0) {
            V(sem_id);  // 자식이 끝낼 수 있도록 세마포어 해제
            break;
        }
        shm_ptr->length = bytes_read;
        V(sem_id);  // 자식에게 공유 메모리 접근 권한 주기

        if (bytes_read < BUFFER_SIZE) {
            break;
        }
    }

    fclose(source_file);
    return 0;
}
