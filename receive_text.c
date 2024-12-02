// receive_text.c
#include "message_struct.h"

int main() {
    int msgid;
    struct message msg;

    // 메시지 큐 연결
    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("채팅 수신 대기 중 (종료하려면 Ctrl+C):\n");

    while (1) {
        // 메시지 수신
        if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }

        printf("수신: %s\n", msg.text);
    }

    return 0;
}
