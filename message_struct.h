#ifndef MESSAGE_STRUCT_H
#define MESSAGE_STRUCT_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 100
#define QUEUE_KEY 1234  // 메시지 큐 키

// 메시지 구조체
struct message {
    long type;              // 메시지 유형
    char text[MSG_SIZE];    // 메시지 내용
};

#endif
