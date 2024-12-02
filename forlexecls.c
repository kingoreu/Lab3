/* forlexecls.c */
/* fork 와 execl을 함께 사용 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        // fork 실패
        perror("fork failed");
        exit(1);  // 오류 코드 1로 종료
    }

    if (pid == 0) {
        // 자식 프로세스
        printf("Child process: executing 'ls -l'...\n");
        execl("/bin/ls", "ls", "-l", (char *)0);
        // execl이 실패하면 perror 출력 후 종료
        perror("execl failed");
        exit(2);  // 오류 코드 2로 종료
    } else {
        // 부모 프로세스
        printf("Parent process: waiting for child process to complete...\n");
        if (wait(NULL) == -1) {
            perror("wait failed");
            exit(3);  // 오류 코드 3으로 종료
        }
        printf("Parent process: 'ls -l' completed.\n");
    }

    return 0;  // 정상 종료
}

