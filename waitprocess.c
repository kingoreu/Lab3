/* waitprocess.c */
/* wait example */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int status, exit_status;

    /* 자식 프로세스를 생성 */
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);  // fork 실패 시 종료
    }

    if (pid == 0) {
        // 자식 프로세스 코드
        printf("Child process: sleeping for 4 seconds...\n");
        sleep(4);  /* 수행을 4초 동안 중단 */
        exit(5);  /* 자식 프로세스 종료 시 5를 반환 */
    } else {
        // 부모 프로세스 코드
        printf("Parent process: waiting for child to terminate...\n");

        /* 자식 프로세스의 종료를 기다림 */
        if ((pid = wait(&status)) == -1) {
            perror("wait failed");
            exit(2);  // wait 실패 시 종료
        }

        /* 자식 프로세스가 정상적으로 종료되었는지 확인 */
        if (WIFEXITED(status)) {
            exit_status = WEXITSTATUS(status);
            printf("Child process (PID: %d) terminated with exit status: %d\n", pid, exit_status);
        } else {
            printf("Child process did not terminate normally.\n");
        }
    }

    exit(0);  // 부모 프로세스 종료
}

