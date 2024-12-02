#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHM_KEY 1234    // 공유 메모리 키
#define SEM_KEY 5678    // 세마포어 키
#define BUFFER_SIZE 1024 // 버퍼 크기

// 공유 메모리 구조체
struct shared_memory {
    char buffer[BUFFER_SIZE]; // 파일 데이터를 저장할 버퍼
    size_t length;            // 데이터의 길이
};

#endif
