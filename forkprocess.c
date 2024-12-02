/* forkprocess.c */
/* fork example with PID output */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid; /* 부모에서 프로세스 식별번호 저장 */

    printf("Calling fork\n");

    pid = fork(); /* 새로운 프로세스 생성 */

    if (pid == 0) {
        // 자식 프로세스
        printf("I'm the child process, my PID is %d, my parent's PID is %d\n", getpid(), getppid());
    }
    else if (pid > 0) {
        // 부모 프로세스
        printf("I'm the parent process, my PID is %d, my child's PID is %d\n", getpid(), pid);
    }
    else {
        // fork 실패
        printf("fork failed\n");
    }

    fflush(stdout);  // 출력 버퍼를 플러시하여 즉시 출력

    return 0;
}

