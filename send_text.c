// send_text.c
#include "message_struct.h"

int main() {
    int msgid;
    struct message msg;

    // 메시지 큐 생성 또는 연결
    msgid = msgget(QUEUE_KEY, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("채팅 시작 (종료하려면 'exit' 입력):\n");

    while (1) {
        printf("송신: ");
        fgets(msg.text, MSG_SIZE, stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0';  // 줄바꿈 제거

        // 종료 조건
        if (strcmp(msg.text, "exit") == 0) {
            break;
        }

        msg.type = 1;  // 메시지 유형 설정

        // 메시지 전송
        if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }

    
    }

    return 0;
}
